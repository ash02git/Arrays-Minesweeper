#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	GameplayController::GameplayController()
	{

	}
	GameplayController::~GameplayController()
	{
	}
	void GameplayController::initialize()
	{
	}
	void GameplayController::update()
	{
		updateRemainingTime();
	}
	void GameplayController::render()
	{
	}
	void GameplayController::reset()
	{
		remaining_time = max_duration;
		Global::ServiceLocator::getInstance()->getBoardService()->resetBoard();
	}
	float GameplayController::getRemainingTime()
	{
		return remaining_time;
	}
	int GameplayController::getMinesCount()
	{
		return Global::ServiceLocator::getInstance()->getBoardService()->getMinesCount();
	}
	void GameplayController::updateRemainingTime()
	{
		remaining_time -= Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}
}