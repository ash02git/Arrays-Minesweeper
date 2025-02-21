#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	namespace Cell
	{
		
		CellController::CellController(sf::Vector2i position)
		{
			cell_model = new CellModel(position);
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

		void CellController::openCell()
		{
			if (cell_model->getCellState() != CellState::FLAGGED)
			{
				cell_model->setCellState(CellState::OPEN);
				Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
			}
		}

		void CellController::flagCell()
		{
			switch (cell_model->getCellState())
			{
				case CellState::FLAGGED:
					cell_model->setCellState(CellState::HIDDEN);
					break;
				case CellState::HIDDEN:
					cell_model->setCellState(CellState::FLAGGED);
					break;
			}
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::FLAG);
		}
		
		void CellController::destroy()
		{
			delete(cell_view);
			delete(cell_model);
		}
	}
}