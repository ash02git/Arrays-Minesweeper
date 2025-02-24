
#include "../../header/Gameplay/Board/BoardService.h"
namespace Gameplay
{
	namespace Board
	{
		void BoardService::destroy()
		{
			delete(board_controller);
		}
		BoardService::BoardService()
		{
			board_controller = nullptr;
		}
		BoardService::~BoardService()
		{
			destroy();
		}
		void BoardService::initialize()
		{
			board_controller = new Board::BoardController();
			board_controller->initialize();
		}
		void BoardService::update()
		{
			board_controller->update();
		}
		void BoardService::render()
		{
			board_controller->render();
		}
		void BoardService::resetBoard()
		{
			board_controller->reset();
		}
		int BoardService::getMinesCount()
		{
			return board_controller->getMinesCount();
		}
		void BoardService::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
			board_controller->processCellInput(cell_controller, button_type);
		}
		BoardState BoardService::getBoardState()
		{
			return board_controller->getBoardState();
		}
		void BoardService::showBoard()
		{
			board_controller->showBoard();
		}
		void BoardService::setBoardState(BoardState board_state)
		{
			board_controller->setBoardState(board_state);
		}
		void BoardService::flagAllMines()
		{
			board_controller->flagAllMines();
		}
	}
}