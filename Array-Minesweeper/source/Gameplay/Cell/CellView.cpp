#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Global/Config.h"

namespace Gameplay
{
	namespace Cell
	{
		void CellView::initializeButtonImage(float width, float height)
		{
			cell_button->initialize("Cell", Global::Config::cells_texture_path, width, height,sf::Vector2f(0,0));
		}
		CellView::CellView(CellController* controller)
		{
			cell_button = new UI::UIElement::ButtonView();
			cell_controller = controller;
		}
		CellView::~CellView()
		{
			delete(cell_button);
		}
		void CellView::initialize()
		{
			initializeButtonImage(tile_size * 3, tile_size * 3);
		}
		void CellView::update()
		{
			cell_button->update();
		}
		void CellView::render()
		{
			cell_button->render();
		}
	}
}