#include "../../header/Main/GameService.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Event/EventService.h"
#include "../../header/UI/UIService.h"

#include <iostream>

namespace Main
{
	using namespace Global;
	using namespace Event;
	using namespace UI;

	GameState GameService::current_state = GameState::BOOT;

	GameService::GameService()
	{
		service_locator = nullptr;
		game_window = nullptr;
	}

	GameService::~GameService()
	{
		destroy();
	}

	void GameService::ignite()
	{
		std::cout << "Ignite function of game service called" << std::endl;
		service_locator = ServiceLocator::getInstance();
		initialize();
		showSplashScreen();
	}

	void GameService::initialize()
	{
		service_locator->initialize();
		game_window = service_locator->getGraphicService()->getGameWindow();//new line

		if (game_window == nullptr)
			std::cout << "GAME WINDOW IS NULL inside GamerService, initialize()" << std::endl;
		else
			std::cout << "GAME WINDOW IS  NOT NULL inside GamerService, initialize()" << std::endl;

		//initializeVariables();//commented for now
	}

	/*
	void GameService::initializeVariables()
	{
		game_window = service_locator->getGraphicService()->getGameWindow();
	}
	*/

	void GameService::showSplashScreen()
	{
		setGameState(GameState::SPLASH_SCREEN);
		ServiceLocator::getInstance()->getUIService()->showScreen();
	}

	bool GameService::isRunning() { return service_locator->getGraphicService()->isGameWindowOpen(); }

	void GameService::setGameState(GameState new_state)
	{
		current_state = new_state;
	}

	GameState GameService::getGameState()
	{
		return current_state;
	}

	// Main Game Loop.
	void GameService::update()
	{
		// Process Events.
		service_locator->getEventService()->processEvents();

		// Update Game Logic.
		service_locator->update();
	}

	void GameService::render()
	{
		game_window->clear();
		service_locator->render();
		game_window->display();
	}

	void GameService::destroy()
	{
		service_locator->deleteServiceLocator();
	}
}