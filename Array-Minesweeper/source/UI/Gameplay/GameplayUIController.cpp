#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Global/ServiceLocator.h"
#include <sstream>
#include <iomanip>

namespace UI
{
	namespace GameplayUI
	{
		void GameplayUIController::createTexts()
		{
			time_text = new UI::UIElement::TextView();
			mine_text = new UI::UIElement::TextView();
		}
		void GameplayUIController::initializeTimeText()
		{
			time_text->initialize("000",sf::Vector2f(time_text_left_offset, time_text_top_offset),UI::UIElement::FontType::BUBBLE_BOBBLE,font_size,text_color);
		}
		void GameplayUIController::updateTimeText()
		{
			int remaining_time = Global::ServiceLocator::getInstance()->getGameplayService()->getRemainingTime();

			std::stringstream stream;
			stream << std::setw(3) << std::setfill('0') << remaining_time;
			std::string string_remaining_time = stream.str();

			time_text->setText(string_remaining_time);
			time_text->update();
		}
		void GameplayUIController::initializeMineText()
		{
			mine_text->initialize("000", sf::Vector2f(mine_text_left_offset, mine_text_top_offset), UI::UIElement::FontType::BUBBLE_BOBBLE, font_size, text_color);
		}
		void GameplayUIController::updateMineText()
		{
			int mines_count = Global::ServiceLocator::getInstance()->getGameplayService()->getMinesCount();

			std::stringstream stream;
			stream << std::setw(3) << std::setfill('0') << mines_count;
			std::string string_mine_count = stream.str();

			mine_text->setText(string_mine_count);
			mine_text->update();
		}
		GameplayUIController::GameplayUIController()
		{
			createTexts();
		}
		GameplayUIController::~GameplayUIController()
		{
			delete(time_text);
			delete(mine_text);
		}
		void GameplayUIController::initialize()
		{
			initializeTimeText();
			initializeMineText();
		}
		void GameplayUIController::update()
		{
			updateTimeText();
			updateMineText();
		}
		void GameplayUIController::render()
		{
			time_text->render();
			mine_text->render();
		}
		void GameplayUIController::show()
		{
			time_text->show();
			mine_text->show();
		}
	}
}