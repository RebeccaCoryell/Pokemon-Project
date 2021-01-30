#include <iostream>
#include <cmath>
#include <iomanip>
#include <assert.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <fstream>

#include "Game.h"
using namespace std;

int main() {
    Game game;
    game.readMap("mapPoke.txt"); // read the map into the game
    game.readAllPokemon("pokemon.txt"); // read the pokemon into the all pokemon vector in the game class
    game.setTrainerPositions(); // set trainer positions
    game.setTrainerPokemon(); // set trainer pokemon
    game.welcome(); // welcome (player chooses name, pokemon and starting position)
    game.setWildPokemonPositions(); // initalize all of the wild pokemon
    game.turn(); // run the actual game until the user quits
}