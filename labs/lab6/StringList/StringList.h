#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

class StringList
{
	struct Node
	{
		Node(const std::string& data_, Node* prev_, Node* next_)
			: data(data_)
			, prev(prev_)
			, next(next_)
			, sentinel(false)
		{
		}

		Node(Node* prev_, Node* next_)
			: prev(prev_)
			, next(next_)
			, sentinel(true)
		{
		}

		std::string data;
		Node* prev;
		Node* next;
		bool sentinel;
	};

public:
	template <bool IsConst>
	class ListIterator
	{
		friend StringList;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Node;
		using difference_type = std::ptrdiff_t;
		using StrRef = std::conditional_t<IsConst, const std::string&, std::string&>;
		using StrPtr = std::conditional_t<IsConst, const std::string*, std::string*>;

		ListIterator();
		ListIterator(Node* ptr);

		StrRef operator*() const;
		StrPtr operator->() const;
		ListIterator& operator++();
		ListIterator operator++(int);
		ListIterator& operator--();
		ListIterator operator--(int);
		bool operator==(const ListIterator& other) const;

	private:
		Node* m_ptr;
	};

	template <bool IsConst>
	class ListReverseIterator
	{
		friend StringList;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Node;
		using difference_type = std::ptrdiff_t;
		using StrRef = std::conditional_t<IsConst, const std::string&, std::string&>;
		using StrPtr = std::conditional_t<IsConst, const std::string*, std::string*>;

		ListReverseIterator();
		ListReverseIterator(Node* ptr);
		StrRef operator*() const;
		StrPtr operator->() const;
		ListReverseIterator& operator++();
		ListReverseIterator operator++(int);
		ListReverseIterator& operator--();
		ListReverseIterator operator--(int);
		bool operator==(const ListReverseIterator& other) const;

	private:
		Node* m_ptr;
	};

	using iterator = ListIterator<false>;
	using const_iterator = ListIterator<true>;
	using reverse_iterator = ListReverseIterator<false>;
	using const_reverse_iterator = ListReverseIterator<true>;

	StringList();
	StringList(std::initializer_list<std::string> initList);
	StringList(const StringList& other);
	StringList(StringList&& other);
	~StringList() noexcept;

	std::string& Front();
	const std::string& Front() const;
	std::string& Back();
	const std::string& Back() const;
	void PushFront(const std::string& str);
	void PushBack(const std::string& str);
	void PopFront();
	void PopBack();

	std::size_t Size() const noexcept;
	bool Empty() const noexcept;
	void Clear() noexcept;
	iterator Insert(iterator pos, const std::string& value);
	iterator Erase(iterator pos);

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator rend() const noexcept;

	StringList& operator=(const StringList& other);
	StringList& operator=(StringList&& other) noexcept;

private:
	void SwapLists(StringList& other) noexcept;

private:
	std::size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};

template <bool IsConst>
StringList::ListIterator<IsConst>::ListIterator()
	: m_ptr(nullptr)
{
}

template <bool IsConst>
StringList::ListIterator<IsConst>::ListIterator(Node* ptr)
	: m_ptr(ptr)
{
}

template <bool IsConst>
StringList::ListIterator<IsConst>::StrRef StringList::ListIterator<IsConst>::operator*() const
{
	if (!m_ptr || m_ptr->sentinel)
	{
		throw std::out_of_range("Dereferencing of nullptr");
	}

	return StrRef(m_ptr->data);
}

template <bool IsConst>
StringList::ListIterator<IsConst>::StrPtr StringList::ListIterator<IsConst>::operator->() const
{
	if (!m_ptr || m_ptr->sentinel)
	{
		throw std::out_of_range("Dereferencing of nullptr");
	}

	return &m_ptr->data;
}

template <bool IsConst>
StringList::ListIterator<IsConst>& StringList::ListIterator<IsConst>::operator++()
{
	if (m_ptr)
	{
		m_ptr = m_ptr->next;
	}

	return *this;
}

template <bool IsConst>
StringList::ListIterator<IsConst> StringList::ListIterator<IsConst>::operator++(int)
{
	auto temp = *this;
	++(*this);

	return temp;
}

template <bool IsConst>
StringList::ListIterator<IsConst>& StringList::ListIterator<IsConst>::operator--()
{
	if (m_ptr)
	{
		m_ptr = m_ptr->prev;
	}

	return *this;
}

template <bool IsConst>
StringList::ListIterator<IsConst> StringList::ListIterator<IsConst>::operator--(int)
{
	auto temp = *this;
	--(*this);

	return temp;
}

template <bool IsConst>
bool StringList::ListIterator<IsConst>::operator==(const ListIterator& other) const
{
	return m_ptr == other.m_ptr;
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>::ListReverseIterator()
	: m_ptr(nullptr)
{
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>::ListReverseIterator(Node* ptr)
	: m_ptr(ptr)
{
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>::StrRef StringList::ListReverseIterator<IsConst>::operator*() const
{
	if (!m_ptr || m_ptr->sentinel)
	{
		throw std::out_of_range("Dereferencing of nullptr");
	}

	return StrRef(m_ptr->data);
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>::StrPtr StringList::ListReverseIterator<IsConst>::operator->() const
{
	if (!m_ptr || m_ptr->sentinel)
	{
		throw std::out_of_range("Dereferencing of nullptr");
	}

	return &m_ptr->data;
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>& StringList::ListReverseIterator<IsConst>::operator++()
{
	if (m_ptr)
	{
		m_ptr = m_ptr->prev;
	}

	return *this;
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst> StringList::ListReverseIterator<IsConst>::operator++(int)
{
	auto temp = *this;
	++(*this);

	return temp;
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst>& StringList::ListReverseIterator<IsConst>::operator--()
{
	if (m_ptr)
	{
		m_ptr = m_ptr->next;
	}

	return *this;
}

template <bool IsConst>
StringList::ListReverseIterator<IsConst> StringList::ListReverseIterator<IsConst>::operator--(int)
{
	auto temp = *this;
	--(*this);

	return temp;
}

template <bool IsConst>
bool StringList::ListReverseIterator<IsConst>::operator==(const ListReverseIterator& other) const
{
	return m_ptr == other.m_ptr;
}