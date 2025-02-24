#pragma once
#include "../../header/Gameplay/Board/BoardService.h"

namespace Gameplay
{
	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};
	
	class GameplayController
	{
	private:
		const float max_duration = 301.0f;
		float remaining_time;

		const float game_over_time = 11.0f;

		GameResult game_result = GameResult::NONE;

		Board::BoardService* board_service;

		void updateRemainingTime();

		void gameLost();
		void gameWon();
		void beginGameOverTimer();

		void showCredits();

		bool isTimeOver();

	public:
		GameplayController();
		~GameplayController();

		void initialize();
		void update();
		void render();

		void reset();

		float getRemainingTime();

		int getMinesCount();

		void endGame(GameResult result);
	};
}