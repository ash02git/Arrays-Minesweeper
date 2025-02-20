#include "header/Main/GameService.h"
#include <iostream>
int main()
{
    using namespace Main;

    GameService* game_service = new GameService();
    std::cout << "In main, made game_service, object" << std::endl;//new line
    game_service->ignite();

    while (game_service->isRunning())
    {
        game_service->update();
        game_service->render();
    }

    return 0;
}