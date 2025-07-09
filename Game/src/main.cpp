#include "Game.h"

#ifdef _DEBUG
#include <filesystem>
#endif // _DEBUG

int main(int argc, char** argv)
{
#ifdef _DEBUG
    std::filesystem::current_path(SOURCE_DIR);
#endif // _DEBUG

    Game game;
    game.Run();

    return 0;
}