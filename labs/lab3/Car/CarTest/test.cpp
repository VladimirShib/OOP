#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../car.h"
#include "../remoteControl.h"
#include <string>
#include <sstream>

SCENARIO("Trying to change gears and speed with engine off")
{
	GIVEN("A car with engine off")
	{
		CCar car;

		CHECK(!car.IsTurnedOn());
		CHECK(car.GetGear() == 0);
		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);

		WHEN("Setting the gear to -1")
		{
			car.SetGear(-1);

			THEN("The gear won't change")
			{
				CHECK(car.GetGear() == 0);
			}
		}

		WHEN("Setting the gear to 1")
		{
			car.SetGear(1);

			THEN("The gear won't change")
			{
				CHECK(car.GetGear() == 0);
			}
		}

		WHEN("Setting the speed to 10")
		{
			car.SetSpeed(10);

			THEN("The speed won't change")
			{
				CHECK(car.GetSpeed() == 0);
			}
			AND_THEN("The car remains still")
			{
				CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);
			}
		}
	}
}

SCENARIO("Testing the neutral gear")
{
	GIVEN("A car with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		CHECK(car.IsTurnedOn());

		WHEN("Trying to move")
		{
			car.SetSpeed(10);

			THEN("The car won't move")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);
			}
		}
	}

	GIVEN("A car that moves backward in neutral gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);

		CHECK(car.GetGear() == 0);
		CHECK(car.GetSpeed() == 10);
		CHECK(car.GetDirection() == CCar::Direction::BACKWARD);

		WHEN("Trying to increase the speed in neutral gear")
		{
			car.SetSpeed(15);

			THEN("The speed remains unchanged")
			{
				CHECK(car.GetSpeed() == 10);
				CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
			}
		}

		WHEN("Trying to decrease the speed in neutral gear")
		{
			car.SetSpeed(5);

			THEN("The car slows down")
			{
				CHECK(car.GetSpeed() == 5);
				CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
			}
		}
	}

	GIVEN("A car that moves forward in neutral gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		car.SetGear(0);

		CHECK(car.GetGear() == 0);
		CHECK(car.GetSpeed() == 10);
		CHECK(car.GetDirection() == CCar::Direction::FORWARD);

		WHEN("Trying to increase the speed in neutral gear")
		{
			car.SetSpeed(15);

			THEN("The speed remains unchanged")
			{
				CHECK(car.GetSpeed() == 10);
				CHECK(car.GetDirection() == CCar::Direction::FORWARD);
			}
		}

		WHEN("Trying to decrease the speed in neutral gear")
		{
			car.SetSpeed(5);

			THEN("The car slows down")
			{
				CHECK(car.GetSpeed() == 5);
				CHECK(car.GetDirection() == CCar::Direction::FORWARD);
			}
		}
	}
}

SCENARIO("Testing the reverse gear")
{
	GIVEN("A car with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Setting the reverse gear")
		{
			car.SetGear(-1);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == -1);

				AND_WHEN("Setting the speed")
				{
					car.SetSpeed(10);

					THEN("The car starts moving backward")
					{
						CHECK(car.GetSpeed() == 10);
						CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
					}

					AND_WHEN("Increasing speed to the limit")
					{
						car.SetSpeed(20);

						THEN("The car starts moving faster in the same direction")
						{
							CHECK(car.GetSpeed() == 20);
							CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
						}
					}

					WHEN("Decreasing speed")
					{
						car.SetSpeed(5);

						THEN("The car starts moving slower in the same direction")
						{
							CHECK(car.GetSpeed() == 5);
							CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
						}
					}

					WHEN("Increasing speed more than is possible for this gear")
					{
						car.SetSpeed(21);

						THEN("The speed remains unchanged")
						{
							CHECK(car.GetSpeed() == 10);
							CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
						}
					}

					WHEN("Setting the gear to neutral")
					{
						car.SetGear(0);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 0);
						}
						AND_THEN("The car continues to move backward")
						{
							CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
						}

						AND_WHEN("Trying to set the gear back to reverse")
						{
							car.SetGear(-1);

							THEN("The gear remains neutral")
							{
								CHECK(car.GetGear() == 0);
							}
							AND_THEN("The car still moves backward")
							{
								CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("Testing the first gear")
{
	GIVEN("A car with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Setting the first gear")
		{
			car.SetGear(1);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 1);

				AND_WHEN("Setting the speed")
				{
					car.SetSpeed(10);

					THEN("The car starts moving forward")
					{
						CHECK(car.GetSpeed() == 10);
						CHECK(car.GetDirection() == CCar::Direction::FORWARD);
					}

					AND_WHEN("Increasing speed to the limit")
					{
						car.SetSpeed(30);

						THEN("The car starts moving faster in the same direction")
						{
							CHECK(car.GetSpeed() == 30);
							CHECK(car.GetDirection() == CCar::Direction::FORWARD);
						}
					}

					WHEN("Decreasing speed")
					{
						car.SetSpeed(5);

						THEN("The car starts moving slower in the same direction")
						{
							CHECK(car.GetSpeed() == 5);
							CHECK(car.GetDirection() == CCar::Direction::FORWARD);
						}
					}

					WHEN("Increasing speed more than is possible for this gear")
					{
						car.SetSpeed(31);

						THEN("The speed remains unchanged")
						{
							CHECK(car.GetSpeed() == 10);
							CHECK(car.GetDirection() == CCar::Direction::FORWARD);
						}
					}

					WHEN("Setting the gear to neutral")
					{
						car.SetGear(0);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 0);
						}
						AND_THEN("The car continues to move forward")
						{
							CHECK(car.GetDirection() == CCar::Direction::FORWARD);
						}

						AND_WHEN("Trying to set the gear back to first")
						{
							car.SetGear(1);

							THEN("The gear changes back to first")
							{
								CHECK(car.GetGear() == 1);
							}
							AND_THEN("The car still moves forward")
							{
								CHECK(car.GetDirection() == CCar::Direction::FORWARD);
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("Changing gears from reverse to forward and vice versa")
{
	GIVEN("A car that moves backward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);

		CHECK(car.GetGear() == -1);
		CHECK(car.GetSpeed() == 10);
		CHECK(car.GetDirection() == CCar::Direction::BACKWARD);

		WHEN("Trying to set the first gear")
		{
			car.SetGear(1);

			THEN("The gear and direction remain unchanged")
			{
				CHECK(car.GetGear() == -1);
				CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
			}
		}

		WHEN("Trying to set the neutral gear")
		{
			car.SetGear(0);

			AND_WHEN("Trying to set the first gear")
			{
				car.SetGear(1);

				THEN("The gear is neutral, car moves backward with the same speed")
				{
					CHECK(car.GetGear() == 0);
					CHECK(car.GetSpeed() == 10);
					CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
				}
			}
		}

		WHEN("Stopping the car")
		{
			car.SetSpeed(0);

			THEN("The car stops, the gear doesn't change")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetGear() == -1);
				CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);
			}

			AND_WHEN("Trying to set the first gear")
			{
				car.SetGear(1);

				THEN("The gear changes")
				{
					CHECK(car.GetGear() == 1);
				}
			}
		}
	}

	GIVEN("A car that moves forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);

		CHECK(car.GetGear() == 1);
		CHECK(car.GetSpeed() == 10);
		CHECK(car.GetDirection() == CCar::Direction::FORWARD);

		WHEN("Trying to set the reverse gear")
		{
			car.SetGear(-1);

			THEN("The gear and direction remain unchanged")
			{
				CHECK(car.GetGear() == 1);
				CHECK(car.GetDirection() == CCar::Direction::FORWARD);
			}
		}

		WHEN("Trying to set the neutral gear")
		{
			car.SetGear(0);

			AND_WHEN("Trying to set the reverse gear")
			{
				car.SetGear(-1);

				THEN("The gear is neutral, car moves forward with the same speed")
				{
					CHECK(car.GetGear() == 0);
					CHECK(car.GetSpeed() == 10);
					CHECK(car.GetDirection() == CCar::Direction::FORWARD);
				}
			}
		}

		WHEN("Stopping the car")
		{
			car.SetSpeed(0);

			THEN("The car stops, the gear doesn't change")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetGear() == 1);
				CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);
			}

			AND_WHEN("Trying to set the reverse gear")
			{
				car.SetGear(-1);

				THEN("The gear changes")
				{
					CHECK(car.GetGear() == -1);
				}
			}
		}
	}
}

SCENARIO("Testing the second gear")
{
	GIVEN("A car standing still with engine on")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);

		WHEN("Setting the second gear from neutral")
		{
			car.SetGear(2);

			THEN("The gear remains unchanged")
			{
				CHECK(car.GetGear() == 0);
				CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);
			}
		}
	}

	GIVEN("A car moving forward in the first gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);

		CHECK(car.GetDirection() == CCar::Direction::FORWARD);

		WHEN("Setting the second gear from the first at not enough speed")
		{
			car.SetSpeed(19);
			car.SetGear(2);

			THEN("The gear remains unchanged")
			{
				CHECK(car.GetGear() == 1);
			}
		}

		WHEN("Setting the second gear from the first at minimum required speed")
		{
			car.SetSpeed(20);
			car.SetGear(2);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 2);
			}

			AND_WHEN("Increasing speed to the limit")
			{
				car.SetSpeed(50);

				THEN("The speed increases")
				{
					CHECK(car.GetSpeed() == 50);
				}

				AND_WHEN("Setting the gear to neutral")
				{
					car.SetGear(0);

					THEN("The gear changes")
					{
						CHECK(car.GetGear() == 0);
					}

					AND_WHEN("Setting the gear back to second")
					{
						car.SetGear(2);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 2);
						}
					}
				}
			}

			WHEN("Increasing speed more than is possible for this gear")
			{
				car.SetSpeed(51);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 20);
				}
			}

			WHEN("Decreasing speed more than is possible for this gear")
			{
				car.SetSpeed(19);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 20);
				}
			}

			WHEN("Setting the gear back to first")
			{
				car.SetGear(1);

				THEN("The gear changes")
				{
					CHECK(car.GetGear() == 1);
				}
			}
		}
	}
}

SCENARIO("Testing the third gear")
{
	GIVEN("A car standing still with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Setting the third gear from neutral")
		{
			car.SetGear(3);

			THEN("The gear remains unchanged")
			{
				CHECK(car.GetGear() == 0);
			}
		}
	}

	GIVEN("A car moving forward in the first gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);

		WHEN("Setting the third gear from the first")
		{
			car.SetSpeed(30);
			car.SetGear(3);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 3);
			}
		}
	}

	GIVEN("A car moving forward in the second gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);

		WHEN("Setting the third gear from the second at minimum required speed")
		{
			car.SetSpeed(30);
			car.SetGear(3);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 3);
			}

			AND_WHEN("Increasing speed to the limit")
			{
				car.SetSpeed(60);

				THEN("The speed increases")
				{
					CHECK(car.GetSpeed() == 60);
				}

				AND_WHEN("Setting the gear to neutral")
				{
					car.SetGear(0);

					THEN("The gear changes")
					{
						CHECK(car.GetGear() == 0);
					}

					AND_WHEN("Setting the gear back to third")
					{
						car.SetGear(3);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 3);
						}
					}
				}
			}

			WHEN("Increasing speed more than is possible for this gear")
			{
				car.SetSpeed(61);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 30);
				}
			}

			WHEN("Decreasing speed more than is possible for this gear")
			{
				car.SetSpeed(29);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 30);
				}
			}
		}
	}
}

SCENARIO("Testing the fourth gear")
{
	GIVEN("A car standing still with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Setting the fourth gear from neutral")
		{
			car.SetGear(4);

			THEN("The gear remains unchanged")
			{
				CHECK(car.GetGear() == 0);
			}
		}
	}

	GIVEN("A car moving forward in the second gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);

		WHEN("Setting the fourth gear from the second")
		{
			car.SetSpeed(40);
			car.SetGear(4);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 4);
			}
		}
	}

	GIVEN("A car moving forward in the third gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);

		WHEN("Setting the fourth gear from the third at minimum required speed")
		{
			car.SetSpeed(40);
			car.SetGear(4);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 4);
			}

			AND_WHEN("Increasing speed to the limit")
			{
				car.SetSpeed(90);

				THEN("The speed increases")
				{
					CHECK(car.GetSpeed() == 90);
				}

				AND_WHEN("Setting the gear to neutral")
				{
					car.SetGear(0);

					THEN("The gear changes")
					{
						CHECK(car.GetGear() == 0);
					}

					AND_WHEN("Setting the gear back to fourth")
					{
						car.SetGear(4);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 4);
						}
					}
				}
			}

			WHEN("Increasing speed more than is possible for this gear")
			{
				car.SetSpeed(91);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 40);
				}
			}

			WHEN("Decreasing speed more than is possible for this gear")
			{
				car.SetSpeed(39);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 40);
				}
			}
		}
	}
}

SCENARIO("Testing the fifth gear")
{
	GIVEN("A car standing still with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Setting the fifth gear from neutral")
		{
			car.SetGear(5);

			THEN("The gear remains unchanged")
			{
				CHECK(car.GetGear() == 0);
			}
		}
	}

	GIVEN("A car moving forward in the second gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);

		WHEN("Setting fifth gear from the second")
		{
			car.SetSpeed(50);
			car.SetGear(5);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 5);
			}
		}
	}

	GIVEN("A car moving forward in the third gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);

		WHEN("Setting the fifth gear from the third")
		{
			car.SetSpeed(60);
			car.SetGear(5);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 5);
			}
		}
	}

	GIVEN("A car moving forward in the fourth gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);

		WHEN("Setting the fifth gear from the fourth at minimum required speed")
		{
			car.SetSpeed(50);
			car.SetGear(5);

			THEN("The gear changes")
			{
				CHECK(car.GetGear() == 5);
			}

			AND_WHEN("Increasing speed to the limit")
			{
				car.SetSpeed(150);

				THEN("The speed increases")
				{
					CHECK(car.GetSpeed() == 150);
				}

				AND_WHEN("Setting the gear to neutral")
				{
					car.SetGear(0);

					THEN("The gear changes")
					{
						CHECK(car.GetGear() == 0);
					}

					AND_WHEN("Setting gear back to fifth")
					{
						car.SetGear(5);

						THEN("The gear changes")
						{
							CHECK(car.GetGear() == 5);
						}
					}
				}
			}

			WHEN("Increasing speed more than is possible for this gear")
			{
				car.SetSpeed(151);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 50);
				}
			}

			WHEN("Decreasing speed more than is possible for this gear")
			{
				car.SetSpeed(49);

				THEN("The speed remains unchanged")
				{
					CHECK(car.GetSpeed() == 50);
				}
			}
		}
	}
}

SCENARIO("Turning the engine off")
{
	GIVEN("A car with engine on")
	{
		CCar car;
		car.TurnOnEngine();

		CHECK(car.IsTurnedOn());

		WHEN("The car moves forward in the first gear")
		{
			car.SetGear(1);
			car.SetSpeed(30);

			CHECK(car.GetSpeed() == 30);
			CHECK(car.GetDirection() == CCar::Direction::FORWARD);

			AND_WHEN("Trying to turn the engine off")
			{
				car.TurnOffEngine();

				THEN("The engine is still on")
				{
					CHECK(car.IsTurnedOn());
				}
			}

			WHEN("The car moves forward in neutral gear")
			{
				car.SetGear(0);

				CHECK(car.GetDirection() == CCar::Direction::FORWARD);

				AND_WHEN("Trying to turn the engine off")
				{
					car.TurnOffEngine();

					THEN("The engine is still on")
					{
						CHECK(car.IsTurnedOn());
					}
				}
			}
		}

		WHEN("The car moves backward in reverse gear")
		{
			car.SetGear(-1);
			car.SetSpeed(20);

			CHECK(car.GetSpeed() == 20);
			CHECK(car.GetDirection() == CCar::Direction::BACKWARD);

			AND_WHEN("Trying to turn the engine off")
			{
				car.TurnOffEngine();

				THEN("The engine is still on")
				{
					CHECK(car.IsTurnedOn());
				}
			}

			WHEN("The car moves backward in neutral gear")
			{
				car.SetGear(0);

				CHECK(car.GetDirection() == CCar::Direction::BACKWARD);

				AND_WHEN("Trying to turn the engine off")
				{
					car.TurnOffEngine();

					THEN("The engine is still on")
					{
						CHECK(car.IsTurnedOn());
					}
				}
			}
		}

		WHEN("The car is standing still not in neutral gear")
		{
			car.SetGear(1);
			CHECK(car.GetGear() == 1);
			CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);

			AND_WHEN("Trying to turn the engine off")
			{
				car.TurnOffEngine();

				THEN("The engine is still on")
				{
					CHECK(car.IsTurnedOn());
				}
			}
		}

		WHEN("The car is standing still in neutral gear")
		{
			CHECK(car.GetGear() == 0);
			CHECK(car.GetDirection() == CCar::Direction::STANDING_STILL);

			AND_WHEN("Trying to turn the engine off")
			{
				car.TurnOffEngine();

				THEN("The engine turns off")
				{
					CHECK(!car.IsTurnedOn());
				}
			}
		}
	}
}

SCENARIO("Testing remote control")
{
	GIVEN("A car and a remote control")
	{
		std::istringstream iss;
		std::ostringstream oss;

		CCar car;
		CRemoteControl remoteControl(car, iss, oss);

		CHECK(!car.IsTurnedOn());

		WHEN("Turning the car engine on")
		{
			std::string command = "EngineOn";
			iss.str(command);
			remoteControl.HandleCommand();
			iss.clear();

			THEN("The car engine should be on")
			{
				CHECK(car.IsTurnedOn());
			}

			AND_WHEN("Turning the car engine off")
			{
				command = "EngineOff";
				iss.str(command);
				remoteControl.HandleCommand();

				THEN("The car engine should be off")
				{
					CHECK(!car.IsTurnedOn());
				}
			}

			WHEN("Setting the reverse gear")
			{
				command = "SetGear -1";
				iss.str(command);
				remoteControl.HandleCommand();
				iss.clear();

				THEN("The reverse gear is set")
				{
					CHECK(car.GetGear() == -1);
				}

				AND_WHEN("Setting the speed")
				{
					command = "SetSpeed 20";
					iss.str(command);
					remoteControl.HandleCommand();

					THEN("The car starts moving backward")
					{
						CHECK(car.GetSpeed() == 20);
						CHECK(car.GetDirection() == CCar::Direction::BACKWARD);
					}
				}
			}

			WHEN("Setting the first gear")
			{
				command = "SetGear 1";
				iss.str(command);
				remoteControl.HandleCommand();
				iss.clear();

				THEN("The first gear is set")
				{
					CHECK(car.GetGear() == 1);
				}

				AND_WHEN("Setting the speed")
				{
					command = "SetSpeed 30";
					iss.str(command);
					remoteControl.HandleCommand();

					THEN("The car starts moving forward")
					{
						CHECK(car.GetSpeed() == 30);
						CHECK(car.GetDirection() == CCar::Direction::FORWARD);
					}
				}
			}
		}
	}
}