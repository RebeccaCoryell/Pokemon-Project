// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <assert.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

#include "Map.h"
#include "Trainers.h"
#include "Pokemon.h"
// possible? already defined in trainer class
// #include "Pokemon.h" 
using namespace std;

class Game {
    private:
    Pokemon allPokemon[151]; // pokemon from the text file
    vector<Pokemon> wildPokemon;
    Trainers trainers[16];
    Map map[27][18];
    int split(string str, char delimiter, string arr[], int length);
    int splitChar(string str, char delimiter, char arr[], int length);
    int splitVector(string str, char delimiter, vector<string> vect);
    
    public:
    Game(); // default constructor
    
    // read map
    int readMap(string fileName);
    // read poketext
    int readAllPokemon(string fileName);

    // set trainer positions (randomize gyms and set the trainer positions to each gym I guess - if not occupied)
    void setTrainerPositions();
    // randomize trainer pokemon
    void setTrainerPokemon();
    // set wild pokemon positions (random and not on water, not in the same place)
    void setWildPokemonPositions();
    
    // battle with wild pokemon DAY 4
    void pokemonBattle(int index);
        // if wild will flee or fight
        int wildFlee(int speedWild, int speedPlayer, int attempts);
        // if the player will be able to flee
        int flee(int speedPlayer, int speedWild, int attempts);
        // switch active pokemon
        void switchActivePokemon();
    // battle with trainer
    void trainerBattle(int index);   
    
    // to catch the pokemon
    void catchPokemon(int index);
    
    // each turn options:
    void turn();
        // rest
        void rest();
        // Travel (but not on water or on boundary - already done)
        int travel(char move);
        // try your luck
        void tryYourLuck();
        // quit
        bool quit();
        // move pokemon
        void movePokemon();
    
    // check for surrounding pokemon - returns the index of the wild pokemon vector of the pokemon nearby - but also then you need to do the battle function??
    int checkIfPokemon();
    // check position of user for gym or center
    int checkIfGym();
    bool checkIfCenter();
    
    // find nearest Pokemon Center
    void nearestPokemonCenter(int r, int c);
    
    // pokemon center function
    int pokemonCenter();
    // switch pokemon suite
    int switchPokemonSuite();
    
    // print map? (position of user + map)
    void displayMap(int r, int c); //position 
    
    // random events: (random number function)
        // pokemon found (for free) (using the random number function - if success)
        void pokemonFound();
        // treasure
        void treasureFound();
        // pokemon death
        void pokemonDeath();
    
    // check types
    int checkNumTypes();
    
    // beginning of game function + name and starter pokemon (welcome) DAY 7
    void welcome();
    
    // if the user is winning, ask if they want to continue
    int userWinning();
    
    // end of game function + name and high score: (for both win and quit)
    void endOfGame();
        // writing to a file
};

#endif