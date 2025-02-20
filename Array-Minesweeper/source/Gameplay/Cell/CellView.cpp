#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Global/Config.h"

namespace Gameplay
{
	namespace Cell
	{
		void CellView::initializeButtonImage(float width, float height)
		{
			sf::Vector2f cell_screen_position = getCellScreenPosition();

			cell_button->initialize("Cell", Global::Config::cells_texture_path, width * slice_count, height, cell_screen_position);
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
		sf::Vector2f CellView::getCellScreenPosition()
		{
			return sf::Vector2f(cell_left_offset, cell_top_offset);
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
		void CellView::initialize(float width, float height)
		{
			initializeButtonImage(width, height);
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