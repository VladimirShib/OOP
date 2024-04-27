#pragma once

#include "MyIterator.h"
#include <compare>
#include <cstddef>
#include <iostream>
#include <string>

class MyString
{
public:
	using iterator = MyIterator<false>;
	using const_iterator = MyIterator<true>;

	MyString() noexcept;
	MyString(const char* pString);
	MyString(const char* pString, std::size_t length);
	MyString(const std::string& stlString);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	~MyString();

	std::size_t GetLength() const;
	std::size_t GetCapacity() const;
	const char* GetStringData() const;
	MyString SubString(std::size_t start, std::size_t length = SIZE_MAX) const;
	void Clear() noexcept;

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

	std::reverse_iterator<iterator> rbegin() noexcept;
	std::reverse_iterator<iterator> rend() noexcept;
	std::reverse_iterator<const_iterator> rbegin() const noexcept;
	std::reverse_iterator<const_iterator> rend() const noexcept;

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString operator+(const MyString& other) const;
	MyString operator+(const std::string& stlString) const;
	friend MyString operator+(const std::string& stlString, const MyString& myString);
	MyString operator+(const char* cString) const;
	friend MyString operator+(const char* cString, const MyString& myString);
	MyString& operator+=(const MyString& other);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	std::strong_ordering operator<=>(const MyString& other) const;
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);

private:
	explicit MyString(const char* pString, std::size_t length, std::size_t capacity);
	void DeleteData();

	std::size_t m_size;
	std::size_t m_capacity;
	char* m_data;
};