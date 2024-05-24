#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T>
class MyList
{
	struct Node
	{
		Node(const T& data_, Node* prev_, Node* next_)
			: data(data_)
			, prev(prev_)
			, next(next_)
			, sentinel(false)
		{
		}

		Node(Node* prev_, Node* next_)
			: data(std::nullopt)
			, prev(prev_)
			, next(next_)
			, sentinel(true)
		{
		}

		std::optional<T> data;
		Node* prev;
		Node* next;
		bool sentinel;
	};

public:
	template <bool IsConst>
	class ListIterator
	{
		friend class MyList<T>;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Node;
		using difference_type = std::ptrdiff_t;
		using RefValue = std::conditional_t<IsConst, const T&, T&>;
		using PtrValue = std::conditional_t<IsConst, const T*, T*>;

		ListIterator()
			: m_ptr(nullptr)
		{
		}

		ListIterator(Node* ptr)
			: m_ptr(ptr)
		{
		}

		RefValue operator*() const
		{
			if (!m_ptr || m_ptr->sentinel)
			{
				throw std::out_of_range("Dereferencing of nullptr");
			}

			return RefValue(m_ptr->data);
		}

		PtrValue operator->() const
		{
			if (!m_ptr || m_ptr->sentinel)
			{
				throw std::out_of_range("Dereferencing of nullptr");
			}

			return &m_ptr->data;
		}

		ListIterator& operator++()
		{
			if (m_ptr)
			{
				m_ptr = m_ptr->next;
			}

			return *this;
		}

		ListIterator operator++(int)
		{
			auto temp = *this;
			++(*this);

			return temp;
		}

		ListIterator& operator--()
		{
			if (m_ptr)
			{
				m_ptr = m_ptr->prev;
			}

			return *this;
		}

		ListIterator operator--(int)
		{
			auto temp = *this;
			--(*this);

			return temp;
		}

		bool operator==(const ListIterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

	private:
		Node* m_ptr;
	};

	template <bool IsConst>
	class ListReverseIterator
	{
		friend class MyList<T>;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Node;
		using difference_type = std::ptrdiff_t;
		using RefValue = std::conditional_t<IsConst, const T&, T&>;
		using PtrValue = std::conditional_t<IsConst, const T*, T*>;

		ListReverseIterator()
			: m_ptr(nullptr)
		{
		}

		ListReverseIterator(Node* ptr)
			: m_ptr(ptr)
		{
		}

		RefValue operator*() const
		{
			if (!m_ptr || m_ptr->sentinel)
			{
				throw std::out_of_range("Dereferencing of nullptr");
			}

			return RefValue(m_ptr->data);
		}

		PtrValue operator->() const
		{
			if (!m_ptr || m_ptr->sentinel)
			{
				throw std::out_of_range("Dereferencing of nullptr");
			}

			return &m_ptr->data;
		}

		ListReverseIterator& operator++()
		{
			if (m_ptr)
			{
				m_ptr = m_ptr->prev;
			}

			return *this;
		}

		ListReverseIterator operator++(int)
		{
			auto temp = *this;
			++(*this);

			return temp;
		}

		ListReverseIterator& operator--()
		{
			if (m_ptr)
			{
				m_ptr = m_ptr->next;
			}

			return *this;
		}

		ListReverseIterator operator--(int)
		{
			auto temp = *this;
			--(*this);

			return temp;
		}

		bool operator==(const ListReverseIterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

	private:
		Node* m_ptr;
	};

	using iterator = ListIterator<false>;
	using const_iterator = ListIterator<true>;
	using reverse_iterator = ListReverseIterator<false>;
	using const_reverse_iterator = ListReverseIterator<true>;

	MyList()
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

	MyList(std::initializer_list<T> initList)
		: MyList()
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

	MyList(const MyList& other)
		: MyList()
	{
		if (other.m_size != 0)
		{
			MyList temp;
			for (const auto& el : other)
			{
				temp.PushBack(el);
			}

			SwapLists(temp);
		}
	}

	MyList(MyList&& other)
		: MyList()
	{
		SwapLists(other);
	}

	~MyList() noexcept
	{
		Clear();
		delete m_firstNode;
		delete m_lastNode;
	}

	T& Front()
	{
		assert(!Empty());
		if (Empty())
		{
			throw std::out_of_range("No elements in container");
		}

		return m_firstNode->next->data.value();
	}

	const T& Front() const
	{
		assert(!Empty());
		if (Empty())
		{
			throw std::out_of_range("No elements in container");
		}

		return m_firstNode->next->data.value();
	}

	T& Back()
	{
		assert(!Empty());
		if (Empty())
		{
			throw std::out_of_range("No elements in container");
		}

		return m_lastNode->prev->data.value();
	}

	const T& Back() const
	{
		assert(!Empty());
		if (Empty())
		{
			throw std::out_of_range("No elements in container");
		}

		return m_lastNode->prev->data.value();
	}

	void PushFront(const T& value)
	{
		Node* newNode = new Node(value, m_firstNode, m_firstNode->next);
		m_firstNode->next->prev = newNode;
		m_firstNode->next = newNode;

		++m_size;
	}

	void PushBack(const T& value)
	{
		Node* newNode = new Node(value, m_lastNode->prev, m_lastNode);
		m_lastNode->prev->next = newNode;
		m_lastNode->prev = newNode;

		++m_size;
	}

	void PopFront()
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

	void PopBack()
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

	std::size_t Size() const noexcept
	{
		return m_size;
	}

	bool Empty() const noexcept
	{
		return m_size == 0;
	}

	void Clear() noexcept
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

	iterator Insert(iterator pos, const T& value)
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

	iterator Erase(iterator pos)
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

	iterator begin() noexcept
	{
		return m_firstNode->next;
	}

	iterator end() noexcept
	{
		return m_lastNode;
	}

	const_iterator begin() const noexcept
	{
		return m_firstNode->next;
	}
	const_iterator end() const noexcept
	{
		return m_lastNode;
	}

	reverse_iterator rbegin() noexcept
	{
		return m_lastNode->prev;
	}

	reverse_iterator rend() noexcept
	{
		return m_firstNode;
	}

	const_reverse_iterator rbegin() const noexcept
	{
		return m_lastNode->prev;
	}

	const_reverse_iterator rend() const noexcept
	{
		return m_firstNode;
	}

	MyList<T>& operator=(const MyList<T>& other)
	{
		if (this != &other)
		{
			if (other.Empty())
			{
				Clear();
			}
			else
			{
				MyList temp = other;
				SwapLists(temp);
			}
		}

		return *this;
	}

	MyList<T>& operator=(MyList<T>&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			SwapLists(other);
		}

		return *this;
	}

private:
	void SwapLists(MyList& other) noexcept
	{
		std::swap(m_size, other.m_size);
		std::swap(m_firstNode, other.m_firstNode);
		std::swap(m_lastNode, other.m_lastNode);
	}

private:
	std::size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};