#include "StringList.h"
#include <cassert>

StringList::StringList()
{
	try
	{
		m_firstNode = new Node(nullptr, nullptr);
		m_lastNode = new Node(nullptr, nullptr);

		m_firstNode->next = m_lastNode;
		m_lastNode->prev = m_firstNode;
	}
	catch (...)
	{
		delete m_firstNode;
		delete m_lastNode;

		throw;
	}
}

StringList::StringList(std::initializer_list<std::string> initList)
	: StringList()
{
	try
	{
		for (const auto& el : initList)
		{
			PushBack(el);
		}
	}
	catch (...)
	{
		Clear();
		delete m_firstNode;
		delete m_lastNode;

		throw;
	}
}

StringList::StringList(const StringList& other)
	: StringList()
{
	if (other.m_size != 0)
	{
		StringList temp;
		for (auto it = other.begin(); it != other.end(); ++it)
		{
			temp.PushBack(*it);
		}

		SwapLists(temp);
	}
}

StringList::StringList(StringList&& other)
	: StringList()
{
	SwapLists(other);
}

StringList::~StringList() noexcept
{
	Clear();
	delete m_firstNode;
	delete m_lastNode;
}

std::string& StringList::Front()
{
	assert(!Empty());
	if (Empty())
	{
		throw std::out_of_range("No elements in container");
	}

	return m_firstNode->next->data;
}

const std::string& StringList::Front() const
{
	assert(!Empty());
	if (Empty())
	{
		throw std::out_of_range("No elements in container");
	}

	return m_firstNode->next->data;
}

std::string& StringList::Back()
{
	assert(!Empty());
	if (Empty())
	{
		throw std::out_of_range("No elements in container");
	}

	return m_lastNode->prev->data;
}

const std::string& StringList::Back() const
{
	assert(!Empty());
	if (Empty())
	{
		throw std::out_of_range("No elements in container");
	}

	return m_lastNode->prev->data;
}

void StringList::PushFront(const std::string& str)
{
	Node* newNode = new Node(str, m_firstNode, m_firstNode->next);
	m_firstNode->next->prev = newNode;
	m_firstNode->next = newNode;

	++m_size;
}

void StringList::PushBack(const std::string& str)
{
	Node* newNode = new Node(str, m_lastNode->prev, m_lastNode);
	m_lastNode->prev->next = newNode;
	m_lastNode->prev = newNode;

	++m_size;
}

void StringList::PopFront()
{
	if (Empty())
	{
		return;
	}

	Node* nodeToDelete = m_firstNode->next;
	m_firstNode->next = nodeToDelete->next;
	m_firstNode->next->prev = m_firstNode;
	delete nodeToDelete;

	--m_size;
}

void StringList::PopBack()
{
	if (Empty())
	{
		return;
	}

	Node* nodeToDelete = m_lastNode->prev;
	m_lastNode->prev = nodeToDelete->prev;
	m_lastNode->prev->next = m_lastNode;
	delete nodeToDelete;

	--m_size;
}

std::size_t StringList::Size() const noexcept
{
	return m_size;
}

bool StringList::Empty() const noexcept
{
	return m_size == 0;
}

void StringList::Clear() noexcept
{
	while (m_firstNode->next != m_lastNode)
	{
		Node* temp = m_firstNode->next;
		m_firstNode->next = temp->next;
		delete temp;
	}

	m_lastNode->prev = m_firstNode;
	m_size = 0;
}

StringList::iterator StringList::Insert(iterator pos, const std::string& value)
{
	if (!pos.m_ptr || pos.m_ptr == m_firstNode)
	{
		throw std::invalid_argument("Iterator points to null");
	}

	Node* newNode = new Node(value, pos.m_ptr->prev, pos.m_ptr);
	newNode->prev->next = newNode;
	newNode->next->prev = newNode;

	++m_size;

	return newNode;
}

StringList::iterator StringList::Erase(iterator pos)
{
	if (!pos.m_ptr || pos.m_ptr == m_firstNode || pos.m_ptr == m_lastNode)
	{
		throw std::invalid_argument("Iterator points to null");
	}

	Node* nextNode = pos.m_ptr->next;
	pos.m_ptr->prev->next = nextNode;
	nextNode->prev = pos.m_ptr->prev;
	delete pos.m_ptr;

	--m_size;

	return nextNode;
}

void StringList::SwapLists(StringList& other) noexcept
{
	std::swap(m_size, other.m_size);
	std::swap(m_firstNode, other.m_firstNode);
	std::swap(m_lastNode, other.m_lastNode);
}

StringList::iterator StringList::begin() noexcept
{
	return m_firstNode->next;
}

StringList::iterator StringList::end() noexcept
{
	return m_lastNode;
}

StringList::const_iterator StringList::begin() const noexcept
{
	return m_firstNode->next;
}

StringList::const_iterator StringList::end() const noexcept
{
	return m_lastNode;
}

StringList::reverse_iterator StringList::rbegin() noexcept
{
	return m_lastNode->prev;
}

StringList::reverse_iterator StringList::rend() noexcept
{
	return m_firstNode;
}

StringList::const_reverse_iterator StringList::rbegin() const noexcept
{
	return m_lastNode->prev;
}

StringList::const_reverse_iterator StringList::rend() const noexcept
{
	return m_firstNode;
}

StringList& StringList::operator=(const StringList& other)
{
	if (this != &other)
	{
		if (other.Empty())
		{
			Clear();
		}
		else
		{
			StringList temp = other;
			SwapLists(temp);
		}
	}

	return *this;
}

StringList& StringList::operator=(StringList&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		SwapLists(other);
	}

	return *this;
}