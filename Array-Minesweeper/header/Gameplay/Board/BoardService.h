#pragma once
#include "BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		class BoardService
		{
		private:
			Board::BoardController* board_controller;

			void destroy();

		public:
			BoardService();
			~BoardService();

			void initialize();
			void update();
			void render();

			void resetBoard();

			int getMinesCount();
		};
	}
}