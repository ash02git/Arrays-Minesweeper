#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"
#include <iostream>

namespace Gameplay
{
	GameplayController::GameplayController()
	{
		board_service = nullptr;
	}
	GameplayController::~GameplayController()
	{
	}
	void GameplayController::initialize()
	{
		board_service = Global::ServiceLocator::getInstance()->getBoardService();
	}
	void GameplayController::update()
	{
		updateRemainingTime();

		if (isTimeOver())
			endGame(GameResult::LOST);
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
	void GameplayController::endGame(GameResult result)
	{
		std::cout << "Has come inside endGame of GameplayController" << std::endl;
		switch (result)
		{
			// In case the game is won, the gameWon() method is called.
		case GameResult::WON:
			gameWon();
			break;
			// In case the game is lost, the gameLost() method is called.
		case GameResult::LOST:
			gameLost();
			break;
			// The default case is not used here as all possible game outcomes should be WON or LOST.
		default:
			// No action is needed for default case.
			break;
		}
	}
	void GameplayController::updateRemainingTime()
	{
		remaining_time -= Global::ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}
	void GameplayController::gameLost()
	{
		std::cout << "Has come inside gameLost of GameplayController" << std::endl;
		if (game_result == GameResult::NONE)
		{
			std::cout << "Has come inside the condition that game result was none, so going to start game over timeer" << std::endl;
			game_result = GameResult::LOST;
			beginGameOverTimer();
			board_service->setBoardState(Board::BoardState::COMPLETED);
			board_service->showBoard();
			std::cout << "Game lost sound to be played" << std::endl;
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::EXPLOSION);
		}
		else
		{
			showCredits();
		}
	}
	void GameplayController::gameWon()
	{
		std::cout << "Game won ....came inside gameWon() of gameplayController" << std::endl;
		game_result = GameResult::WON;
		board_service->flagAllMines();
		board_service->setBoardState(Board::BoardState::COMPLETED);
		std::cout << "Game won sound to be played" << std::endl; 
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::GAME_WON);
		beginGameOverTimer();
	}
	void GameplayController::beginGameOverTimer()
	{
		std::cout << "started game over timer" << std::endl;
		remaining_time = game_over_time;
	}
	void GameplayController::showCredits()
	{
		Main::GameService::setGameState(Main::GameState::CREDITS);
	}
	bool GameplayController::isTimeOver()
	{
		return (remaining_time <= 1);
	}
}