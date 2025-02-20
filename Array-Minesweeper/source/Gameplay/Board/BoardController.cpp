#include "../../header/Gameplay/Board/BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		void BoardController::createBoard()
		{
		}
		void BoardController::deleteBoard()
		{
		}
		void BoardController::destroy()
		{
			delete(board_view);
		}
		BoardController::BoardController()
		{
			board_view = new BoardView(this);
		}
		BoardController::~BoardController()
		{
			destroy();
		}
		void BoardController::initialize()
		{
			board_view->initialize();
		}
		void BoardController::update()
		{
			board_view->update();
		}
		void BoardController::render()
		{
			board_view->render();
		}
		void BoardController::reset()
		{

		}
	}
}