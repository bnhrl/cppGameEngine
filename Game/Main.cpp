#include "ArcadeGame/ArcadeGame.h"
#include "PlatformerGame/PlatformerGame.h"

int main() {
	std::unique_ptr<Game> game = std::make_unique<ArcadeGame>();
	return game->Run();
}