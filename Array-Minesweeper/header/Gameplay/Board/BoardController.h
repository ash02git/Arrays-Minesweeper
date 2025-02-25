#pragma once
#include "BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <random>

namespace Gameplay
{
	namespace Board
	{
		enum class BoardState
		{
			FIRST_CELL,
			PLAYING,
			COMPLETED
		};
		
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

			BoardState getBoardState();
			void setBoardState(BoardState state);
			void populateBoard(sf::Vector2i cell_position);
			void populateMines(sf::Vector2i cell_position);
			void populateCells();

			void openAllCells();

			void showBoard();

			void flagAllMines();

			bool checkWinCondition();
		private:
			BoardView* board_view;
			Cell::CellController* board[number_of_rows][number_of_columns];
			BoardState board_state = BoardState::FIRST_CELL;

			int flagged_cells;

			// To generate random values.
			std::default_random_engine random_engine;

			// To give random seed to generator.
			std::random_device random_device;

			void createBoard();
			void deleteBoard();
			void destroy();

			void initializeCells();

			void resetBoard();

			void openCell(sf::Vector2i cell_position);
			void flagCell(sf::Vector2i cell_position);

			int countMinesAround(sf::Vector2i cell_position);

			bool isValidCellPosition(sf::Vector2i cell_position);

			void processCellValue(sf::Vector2i cell_position);

			void openEmptyCells(sf::Vector2i cell_position);

			void processEmptyCell(sf::Vector2i cell_position);//helper function
			void processMineCell(sf::Vector2i cell_position);

			
		};
	}
}