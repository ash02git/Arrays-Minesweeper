#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/Config.h"
#include <iostream>

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
		BoardController::BoardController() : random_engine(random_device())
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
				processCellValue(cell_position);
				board[cell_position.x][cell_position.y]->openCell();

				/*
				if (checkWinCondition())
				{
					Global::ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::WON);
				}
				*/
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

			//check win condition
		}



		int BoardController::countMinesAround(sf::Vector2i cell_position)
		{
			int mines_around = 0;

			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					//If its the current cell, or cell position is not valid, then the loop will skip once
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b))) continue;

					if (board[a + cell_position.x][b + cell_position.y]->getCellValue() == Cell::CellValue::MINE) mines_around++;
				}
			}

			return mines_around;
		}
		bool BoardController::isValidCellPosition(sf::Vector2i cell_position)
		{
			return (cell_position.x >= 0 && cell_position.y >= 0 && cell_position.x < number_of_columns && cell_position.y < number_of_rows);
		}
		void BoardController::processCellValue(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellValue())
			{
			case::Gameplay::Cell::CellValue::EMPTY:
				processEmptyCell(cell_position); 
				break;
			case::Gameplay::Cell::CellValue::MINE:
				processMineCell(cell_position); //Yet to implement
				break;
			default:
				Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
				break;
			}
		}
		void BoardController::openEmptyCells(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
				// If the cell is already OPEN, no further action is required, and we return from the function.
			case::Gameplay::Cell::CellState::OPEN:
				return;

				// If the cell is FLAGGED, decrement the flagged_cells count as the flag will be removed.
			case::Gameplay::Cell::CellState::FLAGGED:
				flagged_cells--;
				// No break statement here, so the default case will execute next

			// Default case handles the scenario where the cell is neither OPEN nor FLAGGED, which implies it is HIDDEN.
			default:
				// Opens the cell at the current position.
				board[cell_position.x][cell_position.y]->openCell();
			}

			// Iterate over all neighbouring cells.
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					// Skip the iteration if it's the current cell or if the new cell position is not valid.
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(a + cell_position.x, b + cell_position.y)))
						continue;

					// Calculate the position of the neighbouring cell.
					sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);
					//.........
					openCell(next_cell_position);
				}
			}
		}
		void BoardController::processEmptyCell(sf::Vector2i cell_position)
		{
			openEmptyCells(cell_position);
		}
		void BoardController::processMineCell(sf::Vector2i cell_position)
		{
			std::cout << "Has clicked on a mine" << std::endl;
			std::cout << "Has come inside processMineCell of BoardController" << std::endl;
			std::cout << "playin explosion inside processMineCell()" << std::endl;
			std::cout << "service locator instance : "<<Global::ServiceLocator::getInstance() << std::endl;

			std::cout << "Sound service instance : " <<Global::ServiceLocator::getInstance()->getSoundService() << std::endl;

			std::cout << "Explosion sound path : " << (Global::Config::explosion_sound_path).toAnsiString() << std::endl;

			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::EXPLOSION);
			Global::ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::LOST);
		}
		void BoardController::flagAllMines()
		{
			for (int row = 0; row < number_of_rows; ++row)
			{
				for (int col = 0; col < number_of_columns; ++col)
				{
					if (board[row][col]->getCellValue() == Cell::CellValue::MINE && board[row][col]->getCellState() != Cell::CellState::FLAGGED)
						flagCell(sf::Vector2i(row, col));
				}
			}
		}
		bool BoardController::checkWinCondition()
		{
			for (int i = 0;i < number_of_rows;i++)
			{
				for (int j = 0;j < number_of_columns;j++)
				{
					if (board[i][j]->getCellState() != Cell::CellState::OPEN && board[i][j]->getCellValue()==Cell::CellValue::MINE)//tricky
					{
						std::cout << "In checkWinCondition, it has returned false" << std::endl;
						return false;
					}
				}
			}
			std::cout << "In checkWinCondition,boardController, it has returned true" << std::endl;
			return true;
		}
		void BoardController::showBoard()
		{
			std::cout << "Has come inside BoardController show board" << std::endl;
			switch (Global::ServiceLocator::getInstance()->getBoardService()->getBoardState())
			{
			case Gameplay::Board::BoardState::FIRST_CELL:
				populateBoard(sf::Vector2i(0, 0));
				openAllCells();
				break;
			case Gameplay::Board::BoardState::PLAYING:
				openAllCells();
				break;
			case Gameplay::Board::BoardState::COMPLETED:
				openAllCells();
				break;
			default:
				break;
			}
		}
		void BoardController::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
			if (board_state == BoardState::COMPLETED)// to remove getting input once the game is completed
				return;
			
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
			populateMines(cell_position);  
			populateCells();
		}
		void BoardController::populateMines(sf::Vector2i cell_position)
		{
			// Co-ordinate distribution i.e. selecting random position for mines.
			std::uniform_int_distribution<int> x_distribution(0, number_of_columns - 1); //Subtracted -1 because index in an array ranges from 0 to size-1
			std::uniform_int_distribution<int> y_distribution(0, number_of_rows - 1);

			// Generate mines.
			for (int a = 0; a < number_of_mines; a++)
			{
				int i = static_cast<int>(x_distribution(random_engine));
				int j = static_cast<int>(y_distribution(random_engine));

				if (board[i][j]->getCellValue() == Cell::CellValue::MINE || (cell_position.x == i && cell_position.y == j)) 
					a--; //a-- runs a loop 1 extra time
				else 
					board[i][j]->setCellValue(Cell::CellValue::MINE);
			}
		}
		void BoardController::populateCells()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_columns; b++)
				{
					if (board[a][b]->getCellValue() != Cell::CellValue::MINE)
					{
						Cell::CellValue value = static_cast<Cell::CellValue>(countMinesAround(sf::Vector2i(a, b)));
						board[a][b]->setCellValue(value);
					}
				}
			}
		}
		void BoardController::openAllCells()
		{
			for (int a = 0; a < number_of_rows; ++a)
			{
				for (int b = 0; b < number_of_columns; ++b)
				{
					board[a][b]->openCell();
				}
			}
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