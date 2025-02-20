#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Global/Config.h"

namespace Gameplay
{
	namespace Cell
	{
		void CellView::initializeButtonImage(float width, float height)
		{
			cell_button->initialize("Cell", Global::Config::cells_texture_path, width * slice_count, height,sf::Vector2f(0,0));
		}
		void CellView::setCellTexture()
		{
			int index = static_cast<int>(cell_controller->getCellValue());

			switch (cell_controller->getCellState())
			{
			case CellState::HIDDEN:
				cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
				break;

			case CellState::OPEN:
				cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
				break;

			case CellState::FLAGGED:
				cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
				break;
			}
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
			setCellTexture();
			cell_button->render();
		}
	}
}