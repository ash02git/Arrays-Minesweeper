#pragma once
#include "BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"

namespace Gameplay
{
	namespace Board
	{
		class BoardController
		{
		public:
			static const int number_of_rows = 9;
			static const int number_of_columns = 9;
			static const int number_of_mines = 8;

			BoardController();
			~BoardController();

			void initialize();
			void update();
			void render();

			void reset();
		private:
			BoardView* board_view;
			Cell::CellController* board[number_of_rows][number_of_columns];

			void createBoard();
			void deleteBoard();
			void destroy();

			void initializeCells();

			void resetBoard();
		};
	}
}