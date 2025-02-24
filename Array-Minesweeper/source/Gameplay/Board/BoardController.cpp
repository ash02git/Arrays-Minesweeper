#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Global/ServiceLocator.h"

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
		void BoardController::openCell(sf::Vector2i cell_position)
		{
			if (board[cell_position.x][cell_position.y]->canOpenCell())
			{
				if (board_state == BoardState::FIRST_CELL)
				{
					populateBoard(cell_position);
					board_state = BoardState::PLAYING;
				}

				board[cell_position.x][cell_position.y]->openCell();
			}
		}
		void BoardController::flagCell(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
			case::Gameplay::Cell::CellState::FLAGGED:
				Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::FLAG);
				flagged_cells--; //Used to update Gameplay UI
				break;
			case::Gameplay::Cell::CellState::HIDDEN:
				Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::FLAG);
				flagged_cells++; //Used to update Gameplay UI
				break;
			}

			board[cell_position.x][cell_position.y]->flagCell();
		}
		void BoardController::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
			switch (button_type)
			{
			case UI::UIElement::ButtonType::LEFT_MOUSE_BUTTON:
				openCell(cell_controller->getCellPosition());
				break;

			case UI::UIElement::ButtonType::RIGHT_MOUSE_BUTTON:
				flagCell(cell_controller->getCellPosition());
				break;
			}
		}
		BoardState BoardController::getBoardState()
		{
			return board_state;
		}
		void BoardController::setBoardState(BoardState state)
		{
			board_state = state;
		}
		void BoardController::populateBoard(sf::Vector2i cell_position)
		{
			//populateMines(cell_position);  //Yet to Implement
	//populateCells();  //Yet to implement
		}
		int BoardController::getMinesCount()
		{
			return number_of_mines-flagged_cells;
		}
		void BoardController::reset()
		{
			flagged_cells = 0;
			board_state = BoardState::FIRST_CELL;
			resetBoard();
		}
	}
}