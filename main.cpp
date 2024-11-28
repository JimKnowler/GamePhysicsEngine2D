#include <iostream>

#include "GamePhysicsEngine2D.h"

int main(int ArgC, const char* ArgV[]) 
{
    std::cout << "main() - Enter" << std::endl;

    FConfig Config = {
        .AppName = "GamePhysicsEngine2D",
        .WindowWidth = 1280,
        .WindowHeight = 720
    };

    FGamePhysicsEngine2D App;
    App.Init(Config);
    const int ExitCode = App.Run();

    std::cout << "main() - ExitCode[" << ExitCode << "]" << std::endl;
    return ExitCode;
}
