// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#ifndef MAP_H
#define MAP_H

class Map {
    private:
    bool occupied;
    bool gym;
    bool pokeCenter;
    bool endOfMap;
    bool water;
    char tile;
    
    public:
    // accessors
    bool ifOccupied();
    bool ifGym();
    bool ifPokeCenter();
    bool ifEndOfMap();
    bool ifWater();
    char getTile();
    
    // mutators
    void setOccupied(bool flag);
    void setGym(bool flag);
    void setPokeCenter(bool flag);
    void setEndOfMap(bool flag);
    void setWater(bool flag);
    void setAll(bool flag);
    char setTile(char nTile);
};

#endif