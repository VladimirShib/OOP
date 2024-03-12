#pragma once
#include <map>

class CCar
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		STANDING_STILL,
	};
	CCar();

	void TurnOnEngine();
	bool TurnOffEngine();
	bool SetSpeed(const int speed);
	bool SetGear(const int gear);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	void SetDirection();

private:
	struct Range
	{
		int min;
		int max;
	};

	using SpeedRange = std::map<int, Range>;

	bool m_isOn = false;
	int m_speed = 0;
	int m_gear = 0;
	Direction m_direction = Direction::STANDING_STILL;
	SpeedRange m_speedRange;
};