#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Board/BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		void BoardView::initializeBackgroundImage()
		{
			sf::RenderWindow* game_window = Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

			background_image->initialize(Global::Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
			background_image->setImageAlpha(background_alpha);
		}
		void BoardView::initializeBoardImage()
		{
			background_image->initialize(Global::Config::board_texture_path, board_width, board_height, sf::Vector2f(0, 0));
			board_image->setCentreAlinged();
		}
		BoardView::BoardView(BoardController* controller)
		{
			board_controller = controller;
			background_image = new UI::UIElement::ImageView();
			board_image = new UI::UIElement::ImageView();
		}
		BoardView::~BoardView()
		{
			delete(board_image);
			delete(background_image);
		}
		void BoardView::initialize()
		{
			initializeBackgroundImage();
			initializeBoardImage();
		}
		void BoardView::update()
		{
			background_image->update();
			board_image->update();
		}
		void BoardView::render()
		{
			background_image->render();
			board_image->render();
		}
	}
}