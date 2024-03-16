#include "car.h"

void CCar::TurnOnEngine()
{
	m_isOn = true;
}

bool CCar::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}

	m_isOn = false;
	return true;
}

bool CCar::SetSpeed(const int speed)
{
	if (!m_isOn || IsSpeedOutOfRange(speed, m_gear))
	{
		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		return false;
	}

	m_speed = speed;
	SetDirection();

	return true;
}

bool CCar::SetGear(const int gear)
{
	if (!m_isOn || gear < -1 || gear > 5)
	{
		return false;
	}
	if (gear == -1 && m_direction != Direction::STANDING_STILL)
	{
		return false;
	}
	if (m_direction == Direction::BACKWARD && gear != 0)
	{
		return false;
	}
	if (IsSpeedOutOfRange(m_speed, gear))
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}

void CCar::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = Direction::STANDING_STILL;
	}
	else if (m_gear == -1)
	{
		m_direction = Direction::BACKWARD;
	}
	else if (m_gear > 0)
	{
		m_direction = Direction::FORWARD;
	}
}

bool CCar::IsSpeedOutOfRange(const int speed, const int gear)
{
	auto it = m_speedRange.find(gear);
	return speed < it->second.min || speed > it->second.max;
}