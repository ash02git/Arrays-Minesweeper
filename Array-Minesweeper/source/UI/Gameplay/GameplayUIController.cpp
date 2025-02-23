#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/Config.h"
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
		void GameplayUIController::createButton()
		{
			restart_button = new UI::UIElement::ButtonView();
		}
		void GameplayUIController::initializeButton()
		{
			restart_button->initialize("Restart", Global::Config::restart_button_texture_path, button_width, button_height, sf::Vector2f(restart_button_left_offset, restart_button_top_offset));

			registerButtonCallback();
		}
		void GameplayUIController::registerButtonCallback()
		{
			restart_button->registerCallbackFuntion(std::bind(&GameplayUIController::restartButtonCallback, this));
		}
		void GameplayUIController::restartButtonCallback()
		{
			Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
			Global::ServiceLocator::getInstance()->getGameplayService()->startGame();
		}
		GameplayUIController::GameplayUIController()
		{
			createButton();
			createTexts();
		}
		GameplayUIController::~GameplayUIController()
		{
			delete(restart_button);
			delete(time_text);
			delete(mine_text);
		}
		void GameplayUIController::initialize()
		{
			initializeButton();
			initializeTimeText();
			initializeMineText();
		}
		void GameplayUIController::update()
		{
			restart_button->update();
			updateTimeText();
			updateMineText();
		}
		void GameplayUIController::render()
		{
			restart_button->render();
			time_text->render();
			mine_text->render();
		}
		void GameplayUIController::show()
		{
			restart_button->show();
			time_text->show();
			mine_text->show();
		}
	}
}