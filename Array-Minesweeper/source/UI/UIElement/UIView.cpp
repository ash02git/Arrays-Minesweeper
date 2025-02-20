#include "../../header/UI/UIElement/UIView.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Graphics/GraphicService.h"

#include <iostream>;

namespace UI
{
	namespace UIElement
	{
		using namespace Global;
		using namespace Graphics;

		UIView::UIView() = default;

		UIView::~UIView() = default;

		void UIView::initialize()
		{
			game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

			if (game_window == nullptr)
				std::cout << "Game window is nullptr in UIView" << std::endl;
			else
				std::cout << "Game window is not nullptr in UIView" << std::endl;

			ui_state = UIState::VISIBLE;
		}

		void UIView::update() { }

		void UIView::render() { }

		void UIView::show()
		{
			ui_state = UIState::VISIBLE;
		}

		void UIView::hide()
		{
			ui_state = UIState::HIDDEN;
		}
	}
}