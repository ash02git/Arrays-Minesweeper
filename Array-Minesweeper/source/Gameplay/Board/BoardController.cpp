#include "../../header/Gameplay/Board/BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		void BoardController::createBoard()
		{
			for(int i =0;i<number_of_columns;i++)
				cell_controller[i] = new Cell::CellController(i);
		}
		void BoardController::deleteBoard()
		{
			for (int i = 0;i < number_of_columns;i++)
				delete(cell_controller[i]);
		}
		void BoardController::destroy()
		{
			delete(board_view);
		}
		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int i = 0;i < number_of_columns;i++)
				cell_controller[i]->initialize(cell_width, cell_height);
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

			for (int i = 0;i < number_of_columns;i++)
				cell_controller[i]->update();
		}
		void BoardController::render()
		{
			board_view->render();

			for (int i = 0;i < number_of_columns;i++)
				cell_controller[i]->render();
		}
		void BoardController::reset()
		{
			for (int i = 0;i < number_of_columns;i++)
				cell_controller[i]->reset();
		}
	}
}