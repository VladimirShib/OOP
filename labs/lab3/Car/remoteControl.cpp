#include "remoteControl.h"
#include "car.h"
#include <sstream>

namespace
{

constexpr int NO_ARGS = -2;

} // namespace

using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "EngineOn", std::bind(&CRemoteControl::TurnOn, this, _1) },
		  { "EngineOff", std::bind(&CRemoteControl::TurnOff, this, _1) },
		  { "SetSpeed", std::bind(&CRemoteControl::SetSpeed, this, _1) },
		  { "SetGear", std::bind(&CRemoteControl::SetGear, this, _1) },
		  { "Info", std::bind(&CRemoteControl::Info, this, _1) },
		  { "Help", std::bind(&CRemoteControl::Help, this, _1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream iss(commandLine);

	std::string action;
	iss >> action;

	int args;
	args = iss >> args ? args : NO_ARGS;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}

bool CRemoteControl::TurnOn(const int)
{
	if (m_car.IsTurnedOn())
	{
		m_output << "The car engine is already turned on.\n";
	}
	else
	{
		m_car.TurnOnEngine();
		m_output << "The car engine is turned on.\n";
	}

	return true;
}

bool CRemoteControl::TurnOff(const int)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "The car engine is already turned off.\n";
	}
	else if (m_car.TurnOffEngine())
	{
		m_output << "The car engine is turned off.\n";
	}
	else
	{
		m_output << "Can't turn off the engine at the moment.\n";
	}

	return true;
}

bool CRemoteControl::SetSpeed(const int args)
{
	if (args == NO_ARGS)
	{
		m_output << "Specify the desired speed.\n";
	}
	else if (args == m_car.GetSpeed())
	{
		m_output << "Already at this speed.\n";
	}
	else if (m_car.SetSpeed(args))
	{
		m_output << "Speed changed.\n";
	}
	else
	{
		m_output << "Can't set this speed right now.\n";
	}

	return true;
}

bool CRemoteControl::SetGear(const int args)
{
	if (args == NO_ARGS)
	{
		m_output << "Specify the desired gear.\n";
	}
	else if (args == m_car.GetGear())
	{
		m_output << "Already in this gear.\n";
	}
	else if (m_car.SetGear(args))
	{
		m_output << "Gear changed.\n";
	}
	else
	{
		m_output << "Can't set this gear right now.\n";
	}

	return true;
}

bool CRemoteControl::Info(const int) const
{
	m_output << "The car engine is turned ";
	m_car.IsTurnedOn() ? m_output << "on\n" : m_output << "off\n";

	m_output << "The car is ";
	switch (m_car.GetDirection())
	{
	case CCar::Direction::FORWARD:
		m_output << "moving forward\n";
		break;
	case CCar::Direction::BACKWARD:
		m_output << "moving backwards\n";
		break;
	case CCar::Direction::STANDING_STILL:
		m_output << "standing still\n";
		break;
	}

	m_output << "Speed: " << m_car.GetSpeed() << "\n";

	m_output << "Gear: " << m_car.GetGear() << "\n";

	return true;
}

bool CRemoteControl::Help(const int) const
{
	m_output << "EngineOn - turn on engine\n";
	m_output << "EngineOff - turn off engine\n";
	m_output << "SetSpeed <number> - set speed\n";
	m_output << "SetGear <number> - set gear\n";
	m_output << "Info - get info about car\n";

	return true;
}