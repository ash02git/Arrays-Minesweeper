#include "../../header/Gameplay/Cell/CellModel.h"

namespace Gameplay
{
	namespace Cell
	{
		CellModel::CellModel(sf::Vector2i position)
		{
			this->position = position;
		}
		CellModel::~CellModel() = default;
		
		void CellModel::setCellState(CellState state)
		{
			cell_state = state;
		}
		void CellModel::setCellValue(CellValue value)
		{
			cell_value = value;
		}
		CellState CellModel::getCellState()
		{
			return cell_state;
		}
		CellValue CellModel::getCellValue()
		{
			return cell_value;
		}
		void CellModel::setPosition(sf::Vector2i new_position)
		{
			position = new_position;
		}
		sf::Vector2i CellModel::getPosition()
		{
			return position;
		}
		
		void CellModel::reset()
		{
			cell_state = CellState::HIDDEN;
			cell_value = CellValue::EMPTY;
		}
	}
}