// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#include <iostream>
#include <cmath>
#include <iomanip>
#include <assert.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon { // just edit the actual index of each pokemon, pretend it can only show up once
    private:
    int pokemonNumber;
    string pokemonName;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    int max;
    string type1; // array of types instead?
    string type2;
    int level;
    // for position:
    int pRow;
    int pColumn;
    bool fainted;
    bool dead;
    bool active;
    
    public:
    // constructors
    Pokemon();
    Pokemon(int, string, int, int, int, int, int, string, string);
    
    // accessors
    int getPokemonNumber();
    string getPokemonName();
    int getHealth();
    int getMaxHealth();
    int getAttack();
    int getDefense();
    int getSpeed();
    int getMaxStats();
    string getTypeA();
    string getTypeB();
    int getLevel();
    
    // mutators
    void setPokemonNumber(int x);
    void setPokemonName(string str);
    void setHealth(int newHealth);
    void setMaxHealth(int newMaxHealth);
    void setAttack(int newAttack);
    void setDefense(int newDefense);
    void setSpeed(int newSpeed);
    void setMaxStats(int stats);
    void setTypes(string typeA, string typeB); 
    void setLevel(int newLevel);
    
    // positions
    int getPokemonRow();
    int getPokemonColumn();
    // (assuming that the pokemon move was successful - need map)
    void setPokemonRow(int newPos);
    void setPokemonColumn(int newPos);
    
    // fainted or dead
    bool isFainted();
    bool isDead();
    bool isActive();
    void setFainted(bool flag);
    void setDead(bool flag);
    void setActive(bool flag);

    // level up
    void levelUp();
    // heal pokemon
    void healPokemon();
    
};

#endif