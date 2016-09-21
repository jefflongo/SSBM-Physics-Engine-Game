#include "UnsquatState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "ForwardSpecialState.h"
#include "JabState.h"
#include "UpSmashState.h"
#include "DownSmashState.h"
#include "ForwardSmashState.h"
#include "UpTiltState.h"
#include "DownTiltState.h"
#include "ForwardTiltState.h"
#include "GrabState.h"
#include "JumpSquatState.h"
#include "TauntState.h"
#include "DashState.h"

void UnsquatState::init(Player& player)
{
	std::cout << "Entered unsquat state.\n";
	player.setOnScreenState("Unsquat");
}

void UnsquatState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (animFrame_ == 10)
	{
		player.setNextState(new IdleState());
	}
	// L/R presses
	if (controller->buttonPressed(controller->getControls()->L) ||
		controller->buttonPressed(controller->getControls()->R))
	{
		std::cout << "shield\n";
		return;
	}
	// B presses
	else if (controller->buttonPressed(controller->getControls()->B))
	{
		if (controller->axisPercentageLessThan(Axis::Y, -50) &&
			controller->axisPercentageLessThan(Axis::X, 50) &&
			controller->axisPercentageGreaterThan(Axis::X, -50) ||
			controller->axisPercentageLessThan(Axis::Y, -50) &&
			controller->getControlStickAngle() > 53 && controller->getControlStickAngle() < 127)
		{
			std::cout << "up b\n";
			return;
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 50) &&
			controller->axisPercentageLessThan(Axis::X, 50) &&
			controller->axisPercentageGreaterThan(Axis::X, -50) ||
			controller->axisPercentageGreaterThan(Axis::Y, 50) &&
			controller->getControlStickAngle() > 233 && controller->getControlStickAngle() < 307)
		{
			std::cout << "down b\n";
			return;
		}
		else if (controller->axisPercentageGreaterThan(Axis::X, 50))
		{
			if (controller->getControlStickAngle() >= 0 && controller->getControlStickAngle() < 54 || controller->getControlStickAngle() > 306 && controller->getControlStickAngle() < 360)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::X, -50))
		{
			if (controller->getControlStickAngle() > 126 && controller->getControlStickAngle() < 234)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
		}
		else
		{
			std::cout << "neutral b\n";
			return;
		}
	}
	// A presses
	else if (controller->buttonPressed(controller->getControls()->A))
	{
		if (controller->axisPercentageLessThan(Axis::Y, -70))
		{
			if (controller->getControlStickAngle() > 42 && controller->getControlStickAngle() < 138)
			{
				player.setNextState(new UpSmashState());
				return;
			}
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 70))
		{
			if (controller->getControlStickAngle() > 222 && controller->getControlStickAngle() < 318)
			{
				player.setNextState(new DownSmashState());
				return;
			}
		}
		else if (controller->axisPercentageGreaterThan(Axis::X, 75))
		{
			if (controller->getControlStickAngle() >= 0 && controller->getControlStickAngle() < 38 || controller->getControlStickAngle() > 322 && controller->getControlStickAngle() < 360)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::X, -75))
		{
			if (controller->getControlStickAngle() > 142 && controller->getControlStickAngle() < 218)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::Y, -20) && controller->axisPercentageGreaterThan(Axis::Y, -70))
		{
			if (controller->getControlStickAngle() > 50 && controller->getControlStickAngle() < 130)
			{
				player.setNextState(new UpTiltState());
				return;
			}
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 20) && controller->axisPercentageLessThan(Axis::Y, 70))
		{
			if (controller->getControlStickAngle() > 230 && controller->getControlStickAngle() < 310)
			{
				player.setNextState(new DownTiltState());
				return;
			}
		}
		// if none of the above cases, try these
		if (controller->axisPercentageGreaterThan(Axis::X, 20) && player.getDirection() == Player::Direction::Right ||
			controller->axisPercentageLessThan(Axis::X, -20) && player.getDirection() == Player::Direction::Left)
		{
			player.setNextState(new ForwardTiltState());
			return;
		}
		else
		{
			player.setNextState(new JabState());
			return;
		}
	}
	// X/Y presses
	else if (controller->buttonPressed(controller->getControls()->X) ||
		controller->buttonPressed(controller->getControls()->Y))
	{
		player.setNextState(new JumpSquatState());
		return;
	}
	// Z presses
	else if (controller->buttonPressed(controller->getControls()->Z))
	{
		player.setNextState(new GrabState());
		return;
	}
	// D-Pad presses
	else if (controller->buttonPressed(controller->getControls()->D_PAD_UP))
	{
		player.setNextState(new TauntState());
		return;
	}
	// Control Stick presses
	else if (controller->axisPercentageLessThan(Axis::Y, -70))
	{
		if (controller->getControlStickAngle() > 42 && controller->getControlStickAngle() < 138)
		{
			player.setNextState(new JumpSquatState());
			return;
		}
	}
	else if (controller->axisPercentageGreaterThan(Axis::X, 75))
	{
		if (controller->getControlStickAngle() >= 0 && controller->getControlStickAngle() < 38 || controller->getControlStickAngle() > 322 && controller->getControlStickAngle() < 360)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.setState(new DashState());
				return;
			}
		}
	}
	else if (controller->axisPercentageLessThan(Axis::X, -75))
	{
		if (controller->getControlStickAngle() > 142 && controller->getControlStickAngle() < 218)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.setState(new DashState());
				return;
			}
		}
	}
}

void UnsquatState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
}

void UnsquatState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("crouch_04");
	}
	animFrame_++;
}

void UnsquatState::destroy(Player& player)
{
	player.setOnScreenState("");
}