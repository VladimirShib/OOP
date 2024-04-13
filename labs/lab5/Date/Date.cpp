#include "Date.h"
#include <format>

namespace
{

constexpr unsigned int START_YEAR = 1970;
constexpr unsigned int MAX_TIMESTAMP = 2932896;
constexpr unsigned int DAYS_IN_NON_LEAP_YEAR = 365;

struct DateStruct
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

bool IsLeapYear(unsigned int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned int DaysInMonth(unsigned int month, unsigned int year)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;

	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 2:
		return IsLeapYear(year) ? 29 : 28;

	default:
		return 0;
	}
}

DateStruct TimestampToDate(unsigned int days)
{
	auto leapYearsInRange = [](unsigned int years) {
		return years / 4 - years / 100 + years / 400;
	};

	unsigned int year = START_YEAR + ((days - (leapYearsInRange(days / DAYS_IN_NON_LEAP_YEAR))) / DAYS_IN_NON_LEAP_YEAR);
	const unsigned int countLeapYears = leapYearsInRange(year) - leapYearsInRange(START_YEAR);

	days -= (year - START_YEAR) * DAYS_IN_NON_LEAP_YEAR + countLeapYears - (IsLeapYear(year) ? 1 : 0);

	unsigned int month = 1;
	for (;;)
	{
		unsigned int daysInMonth = DaysInMonth(month, year);
		if (days < daysInMonth)
		{
			break;
		}

		days -= daysInMonth;
		month++;
	}

	return { days + 1, month, year };
}

} // namespace

CDate::CDate(unsigned int day, Month month, unsigned int year)
	: m_timestamp(0)
{
	m_timestamp += (year - START_YEAR) * DAYS_IN_NON_LEAP_YEAR;
	m_timestamp += ((year - 1) / 4 - (START_YEAR - 1) / 4)
		- ((year - 1) / 100 - (START_YEAR - 1) / 100)
		+ ((year - 1) / 400 - (START_YEAR - 1) / 400);

	for (auto i = 1u; i < static_cast<unsigned int>(month); ++i)
	{
		m_timestamp += DaysInMonth(i, year);
	}

	m_timestamp += day - 1;
}

CDate::CDate(unsigned int timestamp)
	: m_timestamp(timestamp)
{
}

CDate::CDate()
	: m_timestamp(0)
{
}

unsigned int CDate::GetDay() const
{
	if (!IsValid())
	{
		return 0;
	}

	DateStruct date = TimestampToDate(m_timestamp);
	return date.day;
}

Month CDate::GetMonth() const
{
	if (!IsValid())
	{
		return Month::NO_MONTH;
	}

	DateStruct date = TimestampToDate(m_timestamp);
	return static_cast<Month>(date.month);
}

unsigned int CDate::GetYear() const
{
	if (!IsValid())
	{
		return 0;
	}

	DateStruct date = TimestampToDate(m_timestamp);
	return date.year;
}

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		return WeekDay::NO_WEEK_DAY;
	}

	return static_cast<WeekDay>((m_timestamp + 4) % 7); // january 1, 1970 is thursday
}

bool CDate::IsValid() const
{
	return m_timestamp <= MAX_TIMESTAMP;
}

unsigned int CDate::GetTimestamp() const
{
	return m_timestamp;
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		++m_timestamp;
	}

	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	if (IsValid())
	{
		++m_timestamp;
	}

	return temp;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		--m_timestamp;
	}

	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	if (IsValid())
	{
		--m_timestamp;
	}

	return temp;
}

CDate CDate::operator+(int days) const
{
	if (IsValid() && m_timestamp <= MAX_TIMESTAMP - days)
	{
		return CDate(m_timestamp + days);
	}

	return *this;
}

CDate CDate::operator-(int days) const
{
	if (IsValid() && m_timestamp >= static_cast<unsigned int>(days))
	{
		return CDate(m_timestamp - days);
	}

	return *this;
}

int CDate::operator-(const CDate& date) const
{
	return m_timestamp - date.GetTimestamp();
}

CDate& CDate::operator+=(int days)
{
	if (IsValid())
	{
		m_timestamp += days;
	}

	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (IsValid())
	{
		m_timestamp -= days;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		return os << "INVALID";
	}

	DateStruct dateSt = ::TimestampToDate(date.m_timestamp);
	return os << std::format("{:02d}.{:02d}.{}", dateSt.day, dateSt.month, dateSt.year);
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	DateStruct dateSt{};
	char delimiter = '.';

	if (is >> dateSt.day >> delimiter && delimiter == '.'
		&& is >> dateSt.month >> delimiter && delimiter == '.'
		&& is >> dateSt.year)
	{
		date = CDate(dateSt.day, static_cast<Month>(dateSt.month), dateSt.year);
	}
	else
	{
		is.setstate(std::ios::badbit);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const WeekDay weekday)
{
	switch (weekday)
	{
	case WeekDay::SUNDAY:
		return os << "Sunday";
	case WeekDay::MONDAY:
		return os << "Monday";
	case WeekDay::TUESDAY:
		return os << "Tuesday";
	case WeekDay::WEDNESDAY:
		return os << "Wednesday";
	case WeekDay::THURSDAY:
		return os << "Thursday";
	case WeekDay::FRIDAY:
		return os << "Friday";
	case WeekDay::SATURDAY:
		return os << "Saturday";
	default:
		return os << "No week day";
	}
}

std::ostream& operator<<(std::ostream& os, const Month month)
{
	switch (month)
	{
	case Month::JANUARY:
		return os << "January";
	case Month::FEBRUARY:
		return os << "February";
	case Month::MARCH:
		return os << "March";
	case Month::APRIL:
		return os << "April";
	case Month::MAY:
		return os << "May";
	case Month::JUNE:
		return os << "June";
	case Month::JULY:
		return os << "July";
	case Month::AUGUST:
		return os << "August";
	case Month::SEPTEMBER:
		return os << "September";
	case Month::OCTOBER:
		return os << "October";
	case Month::NOVEMBER:
		return os << "November";
	case Month::DECEMBER:
		return os << "December";
	default:
		return os << "No month";
	}
}

CDate operator+(int days, const CDate& date)
{
	return date + days;
}