// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#ifndef TRAINERS_H
#define TRAINERS_H

#include "Pokemon.h"

class Trainers {
    private:
    string username;
    int points;
    int pokeballs;
    int badges;
    int numTypes;
    vector<Pokemon> partyPokemon; // would this be right? pokemon vector of party
    vector<Pokemon> pokedexPokemon; // would this be right?
    // for position:
        // gym position of each trainer 
    int tRow;
    int tColumn;
    bool defeated;
    
    public:
    
    int getPoints();
    void setPoints(int value);
    void addPoints(int value);
    
    string getUsername();
    void setUsername(string name);
    
    // getters
    int getPokeballs();
    int getBadges();
    int getNumTypes();
    int getTrainerRow();
    int getTrainerColumn();
    bool ifDefeated();
    
    // setters
    void setPokeballs(int value);
    void setBadges(int value);
    void setNumTypes(int value);
    void setTrainerRow(int newPos);
    void setTrainerColumn(int newPos);
    void setDefeated(bool flag);
    
    vector<Pokemon> getPartyPokemon();
    vector<Pokemon> getPokedexPokemon();
    void setPartyPokemon(vector<Pokemon> pok);
    void setPokedexPokemon(vector<Pokemon> pok);
    
    bool checkIfWinning(); // (return true for if winning, false if not yet) (to see if the user is currently winning with badges or types)
    
    // move user based on direction given
    int moveUser(char direction);
};

#endif