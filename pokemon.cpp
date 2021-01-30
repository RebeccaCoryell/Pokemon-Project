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

#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon() { // default constructor 
    pokemonNumber = 0; // sets everything to 0 or empty
    pokemonName = "";
    health = 0;
    maxHealth = 0;
    attack = 0;
    defense = 0;
    speed = 0;
    max = 0;
    type1 = "";
    type2 = "";
    level = 0;
    fainted = false;
    dead = false;
    active = false;
}

Pokemon::Pokemon(int pNumber, string pName, int pHealth, int pAttack, int pDefense, int pSpeed, int pMax, string typeA, string typeB) { // parameterized constructor
    pokemonNumber = pNumber;
    pokemonName = pName;
    health = pHealth;
    maxHealth = pHealth;
    attack = pAttack;
    defense = pDefense;
    speed = pSpeed;
    max = pMax;
    type1 = typeA;
    type2 = typeB;
    level = 1;
    fainted = false;
    dead = false;
    active = false;
}

// accessors:
int Pokemon::getPokemonNumber() {
    return pokemonNumber;
}

string Pokemon::getPokemonName() {
    return pokemonName;
}

int Pokemon::getHealth() {
    return health;
}

int Pokemon::getMaxHealth() {
    return maxHealth;
}

int Pokemon::getAttack() {
    return attack;
}

int Pokemon::getDefense() {
    return defense;
}

int Pokemon::getSpeed() {
    return speed;
}

int Pokemon::getMaxStats() {
    return max;
}

string Pokemon::getTypeA() {
    return type1;
}

string Pokemon::getTypeB() {
    return type2;
}

int Pokemon::getLevel() {
    return level;
}

// mutators:
void Pokemon::setPokemonNumber(int x) {
    pokemonNumber = x;
}

void Pokemon::setPokemonName(string str) {
    pokemonName = str;
}
void Pokemon::setHealth(int newHealth) {
    if(newHealth <= 0) { // so that the health will never be negative
        health = 0;
    }
    else {
        health = newHealth;
    }
}

void Pokemon::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
}

void Pokemon::setDefense(int newDefense) {
    defense = newDefense;
}

void Pokemon::setAttack(int newAttack) {
    attack = newAttack;
}

void Pokemon::setSpeed(int newSpeed) {
    speed = newSpeed;
}

void Pokemon::setMaxStats(int newMax) {
    max = newMax;
}

void Pokemon::setTypes(string typeA, string typeB) {
    type1 = typeA;
    type2 = typeB;
}

void Pokemon::setLevel(int newLevel) {
    level = newLevel;
}

// pokemon positions:
int Pokemon::getPokemonRow() {
    return pRow;
}

int Pokemon::getPokemonColumn() {
    return pColumn;
}

void Pokemon::setPokemonRow(int newPos) {
    pRow = newPos;
}

void Pokemon::setPokemonColumn(int newPos) {
    pColumn = newPos;
}

// pokemon bool values:
bool Pokemon::isFainted() {
    return fainted;
}

bool Pokemon::isDead() {
    return dead;
}

bool Pokemon::isActive() {
    return active;
}

void Pokemon::setFainted(bool flag) {
    fainted = flag;
}

void Pokemon::setDead(bool flag) {
    dead = flag;
}

void Pokemon::setActive(bool flag) {
    active = flag;
}

/** levelUp() - levels up each pokemon
 *  1. If health, attack, defense, or speed are below the given max, increase each by 2%.
 *  2. If any stats are above the max, or would be above the max when 2 were added, the value becomes the max, but no higher.
 *  3. Increment the level variable by one.
*/

void Pokemon::levelUp() {
    // levels up a given pokemon based on stats
    level += 1;
    int healthInc = round(maxHealth*0.02); // how much the health should increase, rounded up
    int attackInc = round(attack*0.02); // how much the attack should increase, rounded up
    int defenseInc = round(defense*0.02); // how much the defense should increase, rounded up
    int speedInc = round(speed*0.02); // how much the speed should increase, rounded up
    // health increase:
    if(health == maxHealth) {
        maxHealth += healthInc; // increase the health
        health = maxHealth;
    }
    else {
        maxHealth += healthInc; // increase the health
    }
    // attack increase:
    if(attack + attackInc <= max) { // if increasing the attack is still less than the max stat
        attack += attackInc; // increase the attack
    }
    else if (attack < max) { // else if the attack is still smaller than the max stats (meaning that increasing by 2% goes over, but still not at max)
        attack = max; // attack becomes max stats
    }
    // defense increase:
    if(defense + defenseInc <= max) { // if increasing the defense is still less than the max stat
        defense += defenseInc; // increase the defense
    }
    else if (defense < max) { // else if the defense is still smaller than the max stats (meaning that increasing by 2% goes over, but still not at max)
        defense = max; // defense becomes max stats
    }
    // speed increase:
    speed += speedInc; // increase the speed
}

/** healPokemon() - heals the pokemon when at a pokemon center
 *  1. Set the current health of the pokemon to the max health given by that pokemon. 
*/

void Pokemon::healPokemon() {
    health = maxHealth; // health becomes maxHealth given by pokemon
}