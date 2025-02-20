#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/Config.h"
#include <iostream>
using namespace std;

namespace Gameplay
{
	namespace Board
	{
		void BoardView::initializeBackgroundImage()
		{
			sf::RenderWindow* game_window = Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
			std::cout << "Background texture path = " << Global::Config::background_texture_path.toAnsiString() << std::endl;
			//std::cout << "Background texture path is " << bgm_texture_path << std::endl;
			std::cout << "Background size x = " << game_window->getSize().x << std::endl;
			std::cout << "Background size y = " << game_window->getSize().y << std::endl;
			std::cout << "Background alpha value = " << background_alpha << std::endl;

			background_image->initialize(Global::Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
			background_image->setImageAlpha(background_alpha);
		}
		void BoardView::initializeBoardImage()
		{
			board_image->initialize(Global::Config::board_texture_path, board_width, board_height, sf::Vector2f(0, 0));
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