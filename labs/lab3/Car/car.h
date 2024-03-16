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
	bool IsSpeedOutOfRange(const int speed, const int gear);

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
	inline static const SpeedRange m_speedRange {
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150} },
	};
};