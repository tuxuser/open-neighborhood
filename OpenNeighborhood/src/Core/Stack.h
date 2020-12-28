#pragma once

/**
* This class is only intended to be used with pointer types
*/

template<typename T>
class Stack
{
public:
	Stack() {}

	~Stack()
	{
		for (T element : m_Elements)
			delete element;
	}

	void Push(T element)
	{
		m_Elements.emplace(m_Elements.begin() + m_ElementInsertIndex, element);
		m_ElementInsertIndex++;
	}

	void Pop(T element)
	{
		auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
		if (it != m_Elements.end())
		{
			m_Elements.erase(it);
			m_ElementInsertIndex--;
		}
	}

	typename std::vector<T>::iterator begin() { return m_Elements.begin(); }
	typename std::vector<T>::iterator end() { return m_Elements.end(); }
private:
	std::vector<T> m_Elements;
	unsigned int m_ElementInsertIndex = 0;
};
