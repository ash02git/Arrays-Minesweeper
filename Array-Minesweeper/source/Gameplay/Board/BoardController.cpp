#include "../../header/Gameplay/Board/BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		void BoardController::createBoard()
		{
			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					board[i][j] = new Cell::CellController(sf::Vector2i(i,j));
				}
			}
		}
		void BoardController::deleteBoard()
		{
			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					delete(board[i][j]);
				}
			}
		}
		void BoardController::destroy()
		{
			delete(board_view);
		}
		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					board[i][j]->initialize(cell_width, cell_height);
				}
			}
		}
		BoardController::BoardController()
		{
			board_view = new BoardView(this);
			createBoard();
		}
		BoardController::~BoardController()
		{
			deleteBoard();
			destroy();
		}
		void BoardController::initialize()
		{
			board_view->initialize();
			//cell_controller->initialize();
			initializeCells();
		}
		void BoardController::update()
		{
			board_view->update();

			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					board[i][j]->update();
				}
			}
		}
		void BoardController::render()
		{
			board_view->render();

			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					board[i][j]->render();
				}
			}
		}
		void BoardController::resetBoard()
		{
			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					board[i][j]->reset();
				}
			}
		}
		void BoardController::reset()
		{
			resetBoard();
		}
	}
}