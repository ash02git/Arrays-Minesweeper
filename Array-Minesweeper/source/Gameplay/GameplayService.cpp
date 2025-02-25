
#include "../../header/Gameplay/GameplayService.h"
#include <iostream>
namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = nullptr;
	}
	GameplayService::~GameplayService()
	{
		//you could also have a destroy function that does the next line 
		delete(gameplay_controller);
	}
	void GameplayService::initialize()
	{
		gameplay_controller = new GameplayController();
		gameplay_controller->initialize();
	}
	void GameplayService::update()
	{
		gameplay_controller->update();
	}
	void GameplayService::render()
	{
		gameplay_controller->render();
	}
	void GameplayService::startGame()
	{
		gameplay_controller->reset();
	}
	float GameplayService::getRemainingTime()
	{
		return gameplay_controller->getRemainingTime();
	}
	int GameplayService::getMinesCount()
	{
		return gameplay_controller->getMinesCount();
	}
	void GameplayService::endGame(GameResult game_result)
	{
		std::cout << "Has come inside endGame() of GameplayService" << std::endl;
		gameplay_controller->endGame(game_result);
	}
}