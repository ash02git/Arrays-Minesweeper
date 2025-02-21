#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	namespace Cell
	{
		enum class CellState
		{
			HIDDEN,
			OPEN,
			FLAGGED
		};

		enum class CellValue
		{
			EMPTY,
			ONE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			SEVEN,
			EIGHT,
			MINE
		};

		class CellModel
		{
		private:
			CellState cell_state;
			CellValue cell_value;

			sf::Vector2i position;

			int cell_index;

		public:
			CellModel(int index);
			~CellModel();

			void setCellState(CellState state);
			void setCellValue(CellValue value);

			CellState getCellState();
			CellValue getCellValue();

			void setPosition(sf::Vector2i new_position);
			sf::Vector2i getPosition();

			int getCellIndex();

			void reset();//to set them to default valeues
		};
	}
}