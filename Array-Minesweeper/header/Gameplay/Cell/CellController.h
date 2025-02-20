#pragma once
#include "../../header/Gameplay/Cell/CellModel.h"

namespace Gameplay
{
	namespace Cell
	{
		class CellView;

		class CellController
		{
		private:
			CellView* cell_view;
			CellModel* cell_model;

			void destroy();
		public:
			CellController();
			~CellController();

			void initialize();
			void update();
			void render();

			void reset();

			CellState getCellState();
			CellValue getCellValue();
			sf::Vector2i getCellPosition();
		};
	}
}