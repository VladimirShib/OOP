#pragma once

#include <iostream>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
	NO_MONTH
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	NO_WEEK_DAY
};

class CDate
{
public:
	CDate(unsigned int day, Month month, unsigned int year);
	explicit CDate(unsigned int timestamp);
	CDate();

	unsigned int GetDay() const;
	Month GetMonth() const;
	unsigned int GetYear() const;
	WeekDay GetWeekDay() const;
	bool IsValid() const;
	unsigned int GetTimestamp() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);
	CDate operator+(int days) const;
	CDate operator-(int days) const;
	int operator-(const CDate& date) const;
	CDate& operator+=(int days);
	CDate& operator-=(int days);
	friend std::ostream& operator<<(std::ostream& os, const CDate& date);
	friend std::istream& operator>>(std::istream& is, CDate& date);
	auto operator<=>(CDate const& date) const = default;

private:
	unsigned int m_timestamp;
};

std::ostream& operator<<(std::ostream& os, const WeekDay weekday);
std::ostream& operator<<(std::ostream& os, const Month month);
CDate operator+(int days, const CDate& date);