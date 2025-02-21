#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellView.h"

namespace Gameplay
{
	namespace Cell
	{
		
		CellController::CellController(int cell_index)
		{
			cell_model = new CellModel(cell_index);
			cell_view = new CellView(this);
		}
		CellController::~CellController()
		{
			destroy();
		}
		void CellController::initialize(float width, float height)
		{
			cell_view->initialize(width,height);
		}
		void CellController::update()
		{
			cell_view->update();
		}
		void CellController::render()
		{
			cell_view->render();
		}
		void CellController::reset()
		{
			cell_model->reset();
		}
		CellState CellController::getCellState()
		{
			return cell_model->getCellState();
		}
		CellValue CellController::getCellValue()
		{
			return cell_model->getCellValue();
		}
		sf::Vector2i CellController::getCellPosition()
		{
			return cell_model->getPosition();
		}
		int CellController::getCellIndex()
		{
			return cell_model->getCellIndex();
		}
		void CellController::destroy()
		{
			delete(cell_view);
			delete(cell_model);
		}
	}
}