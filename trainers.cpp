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
#include "Trainers.h"
using namespace std;

int Trainers::getPoints() {
    return points;
}

void Trainers::setPoints(int value) {
    points = value;
}

void Trainers::addPoints(int value) {
    points += value;
}

string Trainers::getUsername() {
    return username;
}

void Trainers::setUsername(string name) {
    username = name;
}

int Trainers::getPokeballs() {
    return pokeballs;
}

void Trainers::setPokeballs(int value) {
    pokeballs = value;
}

int Trainers::getBadges() {
    return badges;
}

void Trainers::setBadges(int value) {
    badges = value;
}

int Trainers::getNumTypes() {
    return numTypes;
}

void Trainers::setNumTypes(int value) {
    numTypes = value;
}

int Trainers::getTrainerRow() {
    return tRow;
}

void Trainers::setTrainerRow(int newPos) {
    tRow = newPos;
}

int Trainers::getTrainerColumn() {
    return tColumn;
}

void Trainers::setTrainerColumn(int newPos) {
    tColumn = newPos;
}

bool Trainers::ifDefeated() {
    return defeated;
}

void Trainers::setDefeated(bool flag) {
    defeated = flag;
}

vector<Pokemon> Trainers::getPartyPokemon() {
    return partyPokemon;
}

vector<Pokemon> Trainers::getPokedexPokemon() {
    return pokedexPokemon;
}

void Trainers::setPartyPokemon(vector<Pokemon> pok) {
    partyPokemon = pok;
}

void Trainers::setPokedexPokemon(vector<Pokemon> pok) {
    pokedexPokemon = pok;
}

/** checkIfWinning() - checks the flags and the number of types/badges has been met
 *  1. If the number of types is 8, or the number of badges is 6: return true
 *  2. If neither the types or the badges have been met, the player is not winning yet: return false.
*/
bool Trainers::checkIfWinning() {
    if(badges >= 6) { // if number of badges by the trainer is greater than 6, they win
        return true;
    }
    else if(numTypes >= 2) { // if number of types is greater than or equal to 8, they win
        return true;
    }
    else { // otherwise they aren't winning
        return false;
    }
}

/** moveUser(int changeR, int changeC) - moves the user and updates the positions based on the change in rows or the change in columns
 * If the user presses d, move to the right 1.
 * If the user presses a, move to the left 1.
 * If the user presses w, move up 1.
 * If the user presses s, move down 1. 
 * If the move results in the user moving off the map: output "End of map. Please try a different direction." and don't move the user.
 * If none of the above keys were pressed: output "Please select w,a,s,d when moving directions."
 * Function returns 0 if the move was successful, and -1 if not.
*/

int Trainers::moveUser(char direction) {
    switch(direction) {
        case 's' : 
            if(tRow + 1 < 26) { // if the move is valid
                tRow += 1;
                return 0;
            }
            else { // if the movement would cause the user to go out of bounds
                cout << "End of map. Please try a different direction." << endl;
                return -1;
            }
            break;
        case 'a' : 
            if(tColumn - 1 > 0) {
                tColumn -= 1;
                return 0;
            }
            else { // if the movement would cause the user to go out of bounds
                cout << "End of map. Please try a different direction." << endl;
                return -1;
            }
            break;
        case 'w' : 
            if(tRow - 1 > 0) {
                tRow -= 1;
                return 0;
            }
            else { // if the movement would cause the user to go out of bounds
                cout << "End of map. Please try a different direction." << endl;
                return -1;
            }
            break;
        case 'd' : 
            if(tColumn + 1 < 17) {
                tColumn += 1;
                return 0;
            }
            else { // if the movement would cause the user to go out of bounds
                cout << "End of map. Please try a different direction." << endl;
                return -1;
            }
            break;
        default : 
            cout << "Please select 'w', 'a', 's' or 'd' when moving directions. " << endl;
            return -1;
            break;
    }
        
}