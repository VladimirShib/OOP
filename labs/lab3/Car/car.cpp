#include "car.h"

CCar::CCar()
{
	m_speedRange[-1] = { 0, 20 };
	m_speedRange[0] = { 0, 150 };
	m_speedRange[1] = { 0, 30 };
	m_speedRange[2] = { 20, 50 };
	m_speedRange[3] = { 30, 60 };
	m_speedRange[4] = { 40, 90 };
	m_speedRange[5] = { 50, 150 };
}

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
	if (!m_isOn || speed < m_speedRange[m_gear].min || speed > m_speedRange[m_gear].max)
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
	if (m_speed < m_speedRange[gear].min || m_speed > m_speedRange[gear].max)
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