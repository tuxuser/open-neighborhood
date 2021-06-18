/* Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Source: https://github.com/googlearchive/compute-user-accounts/blob/master/nssplugin/libnss_google.cc
 * Modified by tuxuser @ 2021 - Simulating xbdm host
 */

#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdexcept>

#include "XBDM.h"
#include "gtest/gtest.h"

#define XBDM_X360_PORT 730
#define TARGET_HOST "127.0.0.1"
const char* connect_resp = "201- connected\r\n";

typedef std::pair<const std::string&, const std::string&> RequestResponse;

class XbdmHostConnectionMock : public ::testing::Test {
 protected:
  XbdmHostConnectionMock() {
    is_listening_ = false;
    stop_listening_ = false;
    pthread_mutex_init(&mutex_, NULL);
    pthread_cond_init(&listening_cond_, NULL);
    pthread_cond_init(&stop_cond_, NULL);
  }

  ~XbdmHostConnectionMock() {
    pthread_mutex_destroy(&mutex_);
    pthread_cond_destroy(&listening_cond_);
    pthread_cond_destroy(&stop_cond_);
  }

  static void* ServerThreadMain(void* data) {
    const RequestResponse& rr = *static_cast<RequestResponse*>(data);
    int socket_fd;
    OpenServerSocket(&socket_fd);
    VerifyRequestAndSendResponse(socket_fd, rr);
    CloseServerSocket(socket_fd);
    return NULL;
  }

  static void* NoAcceptServerThreadMain(void*) {
    int socket_fd;
    OpenServerSocket(&socket_fd);
    listen(socket_fd, 5);
    SignalListening();
    WaitForShutdown();
    CloseServerSocket(socket_fd);
    return NULL;
  }

  static void* NoResponseServerThreadMain(void*) {
    int socket_fd;
    OpenServerSocket(&socket_fd);
    listen(socket_fd, 5);
    SignalListening();
    int fd = accept(socket_fd, NULL, NULL);
    WaitForShutdown();
    close(fd);
    CloseServerSocket(socket_fd);
    return NULL;
  }

  static void* PartialResponseServerThreadMain(void*) {
    int socket_fd;
    OpenServerSocket(&socket_fd);
    listen(socket_fd, 5);
    SignalListening();
    int fd = accept(socket_fd, NULL, NULL);
    const char* message = "201";
    write(fd, message, strlen(message));
    WaitForShutdown();
    close(fd);
    CloseServerSocket(socket_fd);
    return NULL;
  }

  static void* ConnectResponseAndShutdownServerThreadMain(void*) {
    int socket_fd;
    OpenServerSocket(&socket_fd);
    listen(socket_fd, 5);
    SignalListening();
    int fd = accept(socket_fd, NULL, NULL);
    
    write(fd, connect_resp, strlen(connect_resp));
    WaitForShutdown();
    close(fd);
    CloseServerSocket(socket_fd);
    return NULL;
  }

  static void WaitForServerToListen() {
    pthread_mutex_lock(&mutex_);
    while (!is_listening_) {
      pthread_cond_wait(&listening_cond_, &mutex_);
    }
    pthread_mutex_unlock(&mutex_);
  }

  static void ShutdownServer() {
    pthread_mutex_lock(&mutex_);
    stop_listening_ = true;
    pthread_cond_broadcast(&stop_cond_);
    pthread_mutex_unlock(&mutex_);
  }

 private:
  static void OpenServerSocket(int* socket_fd) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl( INADDR_LOOPBACK );
    address.sin_port = htons( XBDM_X360_PORT );
    *socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ASSERT_GE(*socket_fd, 0) << strerror(errno);
    int yes = 1;
    int ret = setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes,
                         sizeof(yes));
    ASSERT_EQ(0, ret) << strerror(errno);
    ret = bind(*socket_fd, reinterpret_cast<sockaddr*>(&address),
                   sizeof(address));
    ASSERT_EQ(0, ret) << strerror(errno);
  }

  static void SignalListening() {
    pthread_mutex_lock(&mutex_);
    is_listening_ = true;
    pthread_cond_broadcast(&listening_cond_);
    pthread_mutex_unlock(&mutex_);
  }

  static void VerifyRequestAndSendResponse(int socket_fd,
                                           const RequestResponse& rr) {
    listen(socket_fd, 5);
    SignalListening();
    int fd = accept(socket_fd, NULL, NULL);
    ASSERT_GE(fd, 0) << strerror(errno);
    write(fd, connect_resp, strlen(connect_resp));

    char request_buffer[1024];
    read(fd, request_buffer, sizeof(request_buffer));
    EXPECT_EQ(rr.first, request_buffer);

    // Send 16 bytes at a time to simulate packets.
    for (size_t i = 0; i < rr.second.size(); i += 16) {
        std::string chunk = rr.second.substr(i, 16);
        write(fd, chunk.c_str(), chunk.size());
    }

    WaitForShutdown();
    close(fd);
  }

  static void WaitForShutdown() {
    pthread_mutex_lock(&mutex_);
    while (!stop_listening_) {
      pthread_cond_wait(&stop_cond_, &mutex_);
    }
    pthread_mutex_unlock(&mutex_);
  }

  static void CloseServerSocket(int socket_fd) {
    close(socket_fd);
  }

  static bool is_listening_;
  static bool stop_listening_;
  static pthread_mutex_t mutex_;
  static pthread_cond_t listening_cond_;
  static pthread_cond_t stop_cond_;
};

bool XbdmHostConnectionMock::is_listening_;
bool XbdmHostConnectionMock::stop_listening_;
pthread_mutex_t XbdmHostConnectionMock::mutex_;
pthread_cond_t XbdmHostConnectionMock::listening_cond_;
pthread_cond_t XbdmHostConnectionMock::stop_cond_;

TEST_F(XbdmHostConnectionMock, ConnectToSocketShutdownAfter) {
  pthread_t thread;
  pthread_create(&thread, NULL, ConnectResponseAndShutdownServerThreadMain, NULL);
  auto console = new XBDM::Console(TARGET_HOST);
  auto connectSuccess = console->OpenConnection();
  ASSERT_EQ(connectSuccess, true);
  ShutdownServer();
}

TEST_F(XbdmHostConnectionMock, ConnectFailure) {
  pthread_t thread;
  pthread_create(&thread, NULL, NoAcceptServerThreadMain, NULL);
  auto console = new XBDM::Console(TARGET_HOST);
  auto connectSuccess = console->OpenConnection();
  ASSERT_NE(connectSuccess, true);
  ShutdownServer();
}

TEST_F(XbdmHostConnectionMock, ConnectGetConsoleName) {
  std::string command = "dbgname\r\n";
  std::string response = "200- TestXDK\r\n";
  RequestResponse rr(command, response);
  pthread_t thread;
  pthread_create(&thread, NULL, ServerThreadMain, &rr);
  WaitForServerToListen();
  auto console = new XBDM::Console(TARGET_HOST);
  auto connectSuccess = console->OpenConnection();
  auto consoleName = console->GetName();
  ASSERT_EQ(connectSuccess, true);
  ASSERT_STREQ(consoleName.c_str(), "TestXDK\r\n");
  ShutdownServer();
}