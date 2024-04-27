#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

template <bool IsConst>
class MyIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = typename std::conditional<IsConst, const value_type*, value_type*>::type;
	using reference = typename std::conditional<IsConst, const value_type&, value_type&>::type;

	MyIterator(pointer ptr);

	reference operator*() const;
	MyIterator& operator++();
	MyIterator operator++(int);
	MyIterator& operator--();
	MyIterator operator--(int);
	MyIterator operator+(difference_type diff) const;
	MyIterator operator-(difference_type diff) const;
	difference_type operator-(const MyIterator other) const;
	MyIterator& operator+=(difference_type diff);
	MyIterator& operator-=(difference_type diff);
	reference operator[](difference_type diff) const;
	auto operator<=>(const MyIterator& it) const = default;

private:
	pointer m_ptr;
};

template <bool IsConst>
MyIterator<IsConst>::MyIterator(pointer ptr)
	: m_ptr(ptr)
{
}

template <bool IsConst>
MyIterator<IsConst>::reference MyIterator<IsConst>::operator*() const
{
	return *m_ptr;
}

template <bool IsConst>
MyIterator<IsConst>& MyIterator<IsConst>::operator++()
{
	++m_ptr;

	return *this;
}

template <bool IsConst>
MyIterator<IsConst> MyIterator<IsConst>::operator++(int)
{
	MyIterator temp = *this;
	++m_ptr;

	return temp;
}

template <bool IsConst>
MyIterator<IsConst>& MyIterator<IsConst>::operator--()
{
	--m_ptr;

	return *this;
}

template <bool IsConst>
MyIterator<IsConst> MyIterator<IsConst>::operator--(int)
{
	MyIterator temp = *this;
	--m_ptr;

	return temp;
}

template <bool IsConst>
MyIterator<IsConst> MyIterator<IsConst>::operator+(MyIterator::difference_type diff) const
{
	return m_ptr + diff;
}

template <bool IsConst>
MyIterator<IsConst> operator+(typename MyIterator<IsConst>::difference_type diff, const MyIterator<IsConst> it)
{
	return it + diff;
}

template <bool IsConst>
MyIterator<IsConst> MyIterator<IsConst>::operator-(MyIterator<IsConst>::difference_type diff) const
{
	return m_ptr - diff;
}

template <bool IsConst>
MyIterator<IsConst>::difference_type MyIterator<IsConst>::operator-(const MyIterator other) const
{
	return m_ptr - other.m_ptr;
}

template <bool IsConst>
MyIterator<IsConst>& MyIterator<IsConst>::operator+=(MyIterator::difference_type diff)
{
	m_ptr += diff;

	return *this;
}

template <bool IsConst>
MyIterator<IsConst>& MyIterator<IsConst>::operator-=(MyIterator::difference_type diff)
{
	m_ptr -= diff;

	return *this;
}

template <bool IsConst>
MyIterator<IsConst>::reference MyIterator<IsConst>::operator[](MyIterator::difference_type diff) const
{
	return *(m_ptr + diff);
}