#include "MyString.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <stdexcept>

namespace
{

static char NULL_TERMINATOR[1] = { '\0' };
static char* NULL_POINTER = NULL_TERMINATOR;

} // namespace

MyString::MyString() noexcept
	: m_size(0)
	, m_capacity(m_size)
	, m_data(NULL_POINTER)
{
}

MyString::MyString(const char* pString)
	: MyString(pString, std::strlen(pString))
{
}

MyString::MyString(const char* pString, std::size_t length)
	: m_size(length)
	, m_capacity(length)
	, m_data(new char[m_capacity + 1])
{
	std::copy(pString, pString + length, m_data);
	m_data[m_size] = NULL_TERMINATOR[0];
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

MyString::MyString(const MyString& other)
	: MyString(other.GetStringData(), other.GetLength(), other.GetCapacity())
{
}

MyString::MyString(MyString&& other) noexcept
	: MyString()
{
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_data, other.m_data);
}

MyString::MyString(const char* pString, std::size_t length, std::size_t capacity)
	: m_size(length)
	, m_capacity(capacity)
	, m_data(new char[m_capacity + 1])
{
	std::copy(pString, pString + length, m_data);
	m_data[m_size] = NULL_TERMINATOR[0];
}

MyString::~MyString()
{
	DeleteData();
}

std::size_t MyString::GetLength() const
{
	return m_size;
}

std::size_t MyString::GetCapacity() const
{
	return m_capacity;
}

const char* MyString::GetStringData() const
{
	return m_data;
}

MyString MyString::SubString(std::size_t start, std::size_t length) const
{
	assert(start <= m_size);
	if (start > m_size)
	{
		throw std::out_of_range("start position out of range");
	}
	if (length > m_size - start)
	{
		length = m_size - start;
	}

	return MyString(m_data + start, length);
}

void MyString::Clear() noexcept
{
	if (m_size > 0)
	{
		m_size = 0;
		m_data[m_size] = NULL_TERMINATOR[0];
	}
}

MyString::iterator MyString::begin() noexcept
{
	return m_data;
}

MyString::iterator MyString::end() noexcept
{
	return m_data + m_size;
}

MyString::const_iterator MyString::begin() const noexcept
{
	return m_data;
}

MyString::const_iterator MyString::end() const noexcept
{
	return m_data + m_size;
}

std::reverse_iterator<MyString::iterator> MyString::rbegin() noexcept
{
	return std::make_reverse_iterator(end());
}

std::reverse_iterator<MyString::iterator> MyString::rend() noexcept
{
	return std::make_reverse_iterator(begin());
}

std::reverse_iterator<MyString::const_iterator> MyString::rbegin() const noexcept
{
	return std::make_reverse_iterator(end());
}

std::reverse_iterator<MyString::const_iterator> MyString::rend() const noexcept
{
	return std::make_reverse_iterator(begin());
}

void MyString::DeleteData()
{
	if (m_data != NULL_POINTER)
	{
		delete[] m_data;
	}
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		if (other.m_size > m_capacity)
		{
			m_capacity = other.m_size;
			char* temp = new char[m_capacity + 1];
			DeleteData();
			m_data = temp;
		}

		m_size = other.m_size;
		std::copy(other.begin(), other.end(), begin());
		m_data[m_size] = NULL_TERMINATOR[0];
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		m_size = 0;
		m_capacity = 0;
		DeleteData();
		m_data = NULL_POINTER;

		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}

	return *this;
}

MyString MyString::operator+(const MyString& other) const
{
	MyString newStr(m_data, m_size, (m_size + other.m_size) * 2);
	std::copy(other.begin(), other.end(), newStr.end());
	newStr.m_size += other.m_size;
	newStr.m_data[newStr.m_size] = NULL_TERMINATOR[0];

	return newStr;
}

MyString MyString::operator+(const std::string& stlString) const
{
	return *this + MyString(stlString);
}

MyString operator+(const std::string& stlString, const MyString& myString)
{
	return MyString(stlString) + myString;
}

MyString MyString::operator+(const char* cString) const
{
	return *this + MyString(cString);
}

MyString operator+(const char* cString, const MyString& myString)
{
	return MyString(cString) + myString;
}

MyString& MyString::operator+=(const MyString& other)
{
	if (m_capacity >= m_size + other.m_size)
	{
		std::copy(other.begin(), other.end(), end());
		m_size += other.m_size;
		m_data[m_size] = NULL_TERMINATOR[0];
	}
	else
	{
		*this = *this + other;
	}

	return *this;
}

char& MyString::operator[](size_t index)
{
	assert(index < m_size);
	if (index >= m_size)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_data[index];
}

const char& MyString::operator[](size_t index) const
{
	assert(index < m_size);
	if (index >= m_size)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_data[index];
}

bool MyString::operator==(const MyString& other) const
{
	return std::equal(begin(), end(), other.begin(), other.end());
}

bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}

std::strong_ordering MyString::operator<=>(const MyString& other) const
{
	return std::lexicographical_compare_three_way(begin(), end(), other.begin(), other.end());
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	for (std::size_t index = 0; index < str.m_size; ++index)
	{
		os << str[index];
	}

	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	std::string stlStr;
	std::getline(is, stlStr);
	str = MyString(stlStr);

	return is;
}