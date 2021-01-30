// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#include <iomanip>
#include "Map.h"
using namespace std;

// accessors:
bool Map::ifOccupied() {
    return occupied;
}

bool Map::ifGym() {
    return gym;
}

bool Map::ifPokeCenter() {
    return pokeCenter;
}

bool Map::ifEndOfMap() {
    return endOfMap;
}

bool Map::ifWater() {
    return water;
}

char Map::getTile() {
    return tile;
}

// mutators:
void Map::setOccupied(bool flag) {
    occupied = flag;
}

void Map::setGym(bool flag) {
    gym = flag;
}

void Map::setPokeCenter(bool flag) {
    pokeCenter = flag;
}

void Map::setEndOfMap(bool flag) {
    endOfMap = flag;
}

void Map::setWater(bool flag) {
    water = flag;
}

void Map::setAll(bool flag) {
    occupied = flag;
    gym = flag;
    pokeCenter = flag;
    endOfMap = flag;
    water = flag;
}

char Map::setTile(char nTile) {
    tile = nTile;
}
