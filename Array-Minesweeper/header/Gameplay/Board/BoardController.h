#pragma once
#include "BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"

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

			int getMinesCount();

			void processCellInput(Cell::CellController* controller, UI::UIElement::ButtonType button_type);
		private:
			BoardView* board_view;
			Cell::CellController* board[number_of_rows][number_of_columns];

			int flagged_cells;

			void createBoard();
			void deleteBoard();
			void destroy();

			void initializeCells();

			void resetBoard();

			void openCell(sf::Vector2i cell_position);
			void flagCell(sf::Vector2i cell_position);
		};
	}
}