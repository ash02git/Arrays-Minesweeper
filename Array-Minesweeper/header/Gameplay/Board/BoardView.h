#pragma once
#include "../../header/UI/UIElement/ImageView.h"
#include <string>

namespace Gameplay
{
	namespace Board
	{
		class BoardController;

		class BoardView
		{
		private:
			BoardController* board_controller;

			UI::UIElement::ImageView* background_image;
			//const std::string bgm_texture_path;
			const float background_alpha = 85.0f;

			UI::UIElement::ImageView* board_image;
			const float board_width=866.0f;
			const float board_height=1080.0f;

			void initializeBackgroundImage();
			void initializeBoardImage();
			
		public:
			BoardView(BoardController *controller);
			~BoardView();

			void initialize();
			void update();
			void render();
		};
	}
}