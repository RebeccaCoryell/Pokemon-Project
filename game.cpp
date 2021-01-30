// CS1300 Fall 2019
// Author: Rebecca Coryell
// Recitation: 202 – Joewie Koh
// Project 3

#include <iomanip>
#include <fstream> 
#include <algorithm>
#include "Game.h"
using namespace std;

int Game::split(string str, char delimiter, string arr[], int length) { // split function
    int pieces = 0;
    int counter = 0;
    string subarr; // temp variable for the individual words
    if (str.length() == 0) { // if the string is empty, return 0
        return 0;
    } 
    else {
        str = str + delimiter; // add delimiter at the end of the string so it recognizes the last word
        for(int i=0; i<str.length(); i++) { // go through each character of the string
            if (str[i] != delimiter) { // if the character at that point is not the delimiter:
                subarr = subarr + str.substr(i,1); // add that character to the temp string
            }
            else { // if the character at that point is the delimiter:
                if (pieces >= length) { // if the pieces are greater or equal to the length, the array can't hold any more words
                    return -1; // stop running because there are too many pieces, return 1
                }
                else if (subarr.length() == 0) { // if the length of the current word stored in the temp variable (such as when there is 2 delimiters in a row)
                    subarr = subarr; // continue going, don't separate it because there is no word
                }
                else { // else the word is done and is valid
                    arr[counter] = subarr; // put word into array
                    counter++; // increase the counter (for the position of the array)
                    pieces++; // increase the number of pieces
                    subarr.clear(); // temp variable reset
                }
                
            }
        }
    }
}

int Game::splitChar(string str, char delimiter, char arr[], int length) { // split function for characters instead of strings (map)
    int pieces = 0;
    int counter = 0;
    if (str.length() == 0) { // if the string is empty, return 0
        return 0;
    } 
    else {
        str = str + delimiter; // add delimiter at the end of the string so it recognizes the last word
        for(int i=0; i<str.length(); i++) { // go through each character of the string
            if (str[i] != delimiter) { // if the character at that point is not the delimiter:
                arr[counter] = str[i]; // put word into array
                counter++; // increase the counter (for the position of the array)
                pieces++; // increase the number of pieces
            }
        }
    }
}

int Game::splitVector(string str, char delimiter, vector<string> vect) { // split function
    string subarr; // temp variable for the individual words
    str = str + delimiter; // add delimiter at the end of the string so it recognizes the last word
    for(int i=0; i<str.length(); i++) { // go through each character of the string
        if (str[i] != delimiter) { // if the character at that point is not the delimiter:
            subarr = subarr + str.substr(i,1); // add that character to the temp string
        }
        else { // if the character at that point is the delimiter:
            if (subarr.length() == 0) { // if the length of the current word stored in the temp variable (such as when there is 2 delimiters in a row)
                subarr = subarr; // continue going, don't separate it because there is no word
            }
            else { // else the word is done and is valid
                vect.push_back(subarr);
                subarr.clear(); // temp variable reset
            }
                
        }
    }
}

Game::Game() {
    // set everything to 0, or empty
    // read the filename and the map name to start the function, but not necessary
}

/** readMap(string fileName) - read the map from the file and loads it into the map object
 *  1. Open the file.
 *  2. Read the file line by line, use the split function to split the tiles.
 *  3. Load each tile into the map array as a character. (making the first and last row and first and last column a b for boundary)
 *      a. If the tile is water, set the bool for that position as a water tile.
 *      b. If the tile is a pokecenter, set the bool for that position as a pokecenter tile.
 *      c. If the tile is gym, set the bool for that position as a gym tile.
 *      d. If the tile is end of map, set the bool for that position as an end of map tile.
*/

int Game::readMap(string fileName) {
    ifstream inFile; // open file
    inFile.open(fileName);
    string line = "";
    int i=1; // start i at 1 (not 0 because boundary is at 0)
    if(inFile.fail()) {
        return -1;
    }
    else if(!inFile.fail()) { // horizontal boundaries
        for(int x=0; x<18; x++) { // for the end of the map: setting up the borders
            map[0][x].setTile('_'); // top row
            map[0][x].setAll(false);
            map[0][x].setEndOfMap(true);
            map[26][x].setTile('_'); // bottom row
            map[26][x].setAll(false);
            map[26][x].setEndOfMap(true);
            
        }
        for(int y=0; y<27; y++) { // vertical boundaries for the map
            map[y][0].setTile('|'); // left side
            map[y][0].setAll(false);
            map[y][0].setEndOfMap(true);
            map[y][17].setTile('|'); // right side
            map[y][17].setAll(false);
            map[y][17].setEndOfMap(true);
        }
        map[0][0].setTile('.'); // making the corners dots to look nice
        map[0][17].setTile('.');
        map[26][0].setTile('.');
        map[26][17].setTile('.');
        while(getline(inFile, line)) { // reading from the actual map text
            if(line != "" && i != 26) { // ignoring the borders
                char tempMap[16];
                splitChar(line, ',', tempMap, 16);
                for(int j=1; j<17; j++) { // ignoring the borders
                    if(tempMap[j-1] == 'w') { // if water
                        map[i][j].setTile('~'); // set that tile to water
                        map[i][j].setAll(false);
                        map[i][j].setWater(true); // set it as just a water tile
                    }
                    if(tempMap[j-1] == 'G') { // if gym
                        map[i][j].setTile('G'); // set that position to gym
                        map[i][j].setAll(false);
                        map[i][j].setGym(true); // set it as just a gym tile
                    }
                    if(tempMap[j-1] == 'C') { // if poke center
                        map[i][j].setTile('C'); // set that position to C tile
                        map[i][j].setAll(false);
                        map[i][j].setPokeCenter(true); // set it to a Pokecenter 
                        map[i][j].setOccupied(true); // make it occupied so a pokemon won't spawn there
                    }
                    if(tempMap[j-1] == 'p') { // if it is land
                        map[i][j].setTile('*'); // set that position as land
                        map[i][j].setAll(false); // make everything false (not anything right now)
                    }
                }
            }
            i++;
        }
    }
}

/** readAllPokemon(string fileName) - read the pokemon from the file and loads it into the map object
 *  1. Open the file.
 *  2. Read the file line by line, use the split function to split the pokemon values.
 *  3. Load each pokemon into the pokemon allPokemon array.
*/

int Game::readAllPokemon(string fileName) {
    ifstream inFile; // open file
    inFile.open(fileName);
    string line = "";
    int lineNum = 1; // start line at 1 (first line)
    int i = 0;
    if(inFile.fail()) {
        return -1;
    }
    else if(!inFile.fail()) {
        while(getline(inFile, line)) {
            if(line != "" && lineNum != 1) { // ignore the first line and empty lines
                string tempPoke[9];
                split(line, ',', tempPoke, 9);
                // set all the stats according to the pokemon file:
                allPokemon[i].setPokemonNumber(stoi(tempPoke[0]));
                allPokemon[i].setPokemonName(tempPoke[1]);
                allPokemon[i].setHealth(stoi(tempPoke[2]));
                allPokemon[i].setMaxHealth(stoi(tempPoke[2]));
                allPokemon[i].setAttack(stoi(tempPoke[3]));
                allPokemon[i].setDefense(stoi(tempPoke[4]));
                allPokemon[i].setSpeed(stoi(tempPoke[5]));
                allPokemon[i].setMaxStats(stoi(tempPoke[6]));
                allPokemon[i].setTypes(tempPoke[7], tempPoke[8]);
                line = "";
                i++;
            }
            lineNum++;
        }
        return 1; // if success, return 1.
    }
}

/** displayMap(int r, int c) 
 * EDGES CASES: 
     * In the top right and left corners
     * In the bottom right and left corners
     * Too close to the left, right, top or bottom
 *  1. Go through each position of the map array, starting up 3 and left 3 from the given position. Go 7 tiles in each direction.
 *  2. Display each position of the map, going line by line.
 *  3. Replace the position of the trainer given by an @ sign. 
 *  4. For edge cases, display starting at the edges, and go 7 out or 7 down, so that it has a block to display in each position. 
 *      a. FOR EXAMPLE: if the user is too close to the top right corner, display the map starting at 0,0 and going through until 7,7.
*/

void Game::displayMap(int r, int c) { //position 
    if (c < 3) { // column is too close to edge (left)
        if (r < 3) { // top corner
            for(int i=0; i<7; i++) { // just display the top left corner, with the position of the trainer not in the center
                for(int j=0; j<7; j++) { // go through each position (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // position of trainer given is replace by an @
                    }
                    else {
                        cout << map[i][j].getTile() << "  ";  // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
        else if (r > 23) { // bottom corner
            for(int i=20; i<27; i++) { // just display the bottom left corner, with the position of the trainer not in the center
                for(int j=0; j<7; j++) { // go through each position (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // position of trainer given is repalced by an @
                    }
                    else {
                        cout << map[i][j].getTile() << "  "; // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
        else { // just too close to left
            for(int i=r-3; i<r+4; i++) { // display up until the left edge
                for(int j=0; j<7; j++) { // go through each position (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // position of trainer given is replaced by an @
                    }
                    else {
                        cout << map[i][j].getTile() << "  "; // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
    }
    else if (c > 14) { // column is too close to edge (right)
        if (r < 3) { // top corner
            for(int i=0; i<7; i++) { // just display the top right corner, with the trainer not in the center
                for(int j=11; j<18; j++) { // go through each position (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // replace the position of the trainer given with an @
                    }
                    else {
                        cout << map[i][j].getTile() << "  "; // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
        else if (r > 23) { // bottom corner
            for(int i=20; i<27; i++) { // just display the bottom right corner, with the trainer not in the center
                for(int j=11; j<18; j++) { // go through each posiiton (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // replace the position of the trainer given with an @
                    }
                    else {
                        cout << map[i][j].getTile() << "  "; // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
        else { // just too close to right
            for(int i=r-3; i<r+4; i++) { // display up until the right edge
                for(int j=11; j<18; j++) { // go through each position (in the 7x7 area)
                    if(i == r && j == c) {
                        cout << "@  "; // replace the position of the trainer given with an @
                    }
                    else { 
                        cout << map[i][j].getTile() << "  "; // display the tile at that position
                    }
                }
                cout << endl;
            }
        }
    }
    else if (r < 3) { // row is just too close to top
        for(int i=0; i<7; i++) { // display up until the top edge
            for(int j=c-3; j<c+4; j++) { // go through each position (in the 7x7 area)
                if(i == r && j == c) { 
                    cout << "@  "; // replace the position of the trainer given with an @
                }
                else {
                    cout << map[i][j].getTile() << "  "; // display the tile at that position
                }
            }
            cout << endl;
        }
    }
    else if (r > 23) { // row is just too close to bottom
        for(int i=20; i<27; i++) { // display up until the bottom edge
            for(int j=c-3; j<c+4; j++) { // go through each position (in the 7x7 area)
                if(i == r && j == c) { 
                    cout << "@  "; // replace the position of the trainer given with an @
                }
                else {
                    cout << map[i][j].getTile() << "  "; // display the tile at that position
                }
            }
            cout << endl;
        }
    }
    else { // the position is in the middle of the board (not near the edges)
        for(int i=r-3; i<r+4; i++) { // go through each position of 7x7 area, starting in the top corner
            for(int j=c-3; j<c+4; j++) {
                if(i == r && j == c) {
                    cout << "@  "; // replace the given position of the trainer with an @
                }
                else {
                    cout << map[i][j].getTile() << "  "; // display the tile at that position
                }
            }
            cout << endl;
        }
    }
}

/** setTrainerPositions() - randomizes the positions of the trainers to the 6 gyms located on the map
 *  1. Go through each trainer in the trainer array. 
 *  2. Generate a random number between 1 and 15.
 *  3. Based on that number, if the gym is not already taken, assign that trainer to that gym, and mark it occupied. 
 *  3. If the gym is already taken, generate a new random number. Keep going until each trainer has a gym. 
*/

void Game::setTrainerPositions() {
    trainers[0].setUsername("Blanche");
    trainers[1].setUsername("Candela");
    trainers[2].setUsername("Spark");
    trainers[3].setUsername("Cynthia");
    trainers[4].setUsername("Gloria");
    trainers[5].setUsername("Leaf");
    trainers[6].setUsername("Misty");
    trainers[7].setUsername("Evergreen");
    trainers[8].setUsername("Summit");
    trainers[9].setUsername("Willow");
    trainers[10].setUsername("Terrace");
    trainers[11].setUsername("Carp");
    trainers[12].setUsername("Ignis");
    trainers[13].setUsername("Ash");
    trainers[14].setUsername("Brock");
    srand(time(nullptr));
    int choice;
    for(int i=0; i<15; i++) { // go through each trainer
        bool set = false;
        while(set == false) { // while the trainer does not yet have a gym set
            choice = rand()%15 + 1; // generate a random number between 1 and 15
            switch(choice) { // based on that number, assign a gym to that trainer (if not already taken)
                case 1 : // first gym (row: 2 column: 8)
                    if(map[2][8].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(2); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(8);
                        map[2][8].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully set
                    }
                    break;
                case 2 : // second gym (row: 2 column: 15)
                    if(map[2][15].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(2); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(15);
                        map[2][15].setOccupied(true); // set the gym to be occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 3 : // third gym (row: 4 column: 3)
                    if(map[4][2].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(4); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(3);
                        map[4][3].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 4 : // fourth gym (row: 5 column: 12)
                    if(map[5][12].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(5); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(12);
                        map[5][12].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 5 : // fifth gym (row: 8 column: 16)
                    if(map[8][16].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(8); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(16);
                        map[8][16].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 6 : // sixth gym (row: 9 column: 2)
                    if(map[9][2].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(9); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(2);
                        map[9][2].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 7 : // seventh gym (row: 11 column: 9)
                    if(map[11][9].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(11); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(9); 
                        map[11][9].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 8 : // eighth gym (row: 12 column: 12)
                    if(map[12][12].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(12); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(12);
                        map[12][12].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 9 : // ninth gym (row: 13 column: 16)
                    if(map[13][16].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(13); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(16);
                        map[13][16].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 10 : // tenth gym (row: 14 column: 3)
                    if(map[14][3].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(14); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(3);
                        map[14][3].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 11 : // eleventh gym (row: 18 column: 2)
                    if(map[18][2].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(18); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(2);
                        map[18][2].setOccupied(true); // set the gym to occupied 
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 12 : // twelfth gym (row: 20 column: 9)
                    if(map[20][9].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(20); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(9);
                        map[20][9].setOccupied(true); // set the gym to occupied 
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 13 : // thirteenth gym (row: 22 colum: 14)
                    if(map[22][14].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(22); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(14);
                        map[22][14].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 14 : // fourteenth gym (row: 23 column: 7)
                    if(map[23][7].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(23); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(7);
                        map[23][7].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
                case 15 : // fifteenth gym (row: 24 column: 2)
                    if(map[24][2].ifOccupied() == false) { // if the gym is available
                        trainers[i].setTrainerRow(24); // set that gym as the trainer's new position
                        trainers[i].setTrainerColumn(2);
                        map[24][2].setOccupied(true); // set the gym to occupied
                        set = true; // the trainer position has been successfully updated
                    }
                    break;
            }
            
        }
        // undo all of the occupied positions after the trainer's have been intialized (because occupied is for pokemon)
        map[2][8].setOccupied(false);
        map[2][15].setOccupied(false);
        map[4][3].setOccupied(false);
        map[5][12].setOccupied(false);
        map[8][16].setOccupied(false);
        map[9][2].setOccupied(false);
        map[11][9].setOccupied(false);
        map[12][12].setOccupied(false);
        map[13][16].setOccupied(false);
        map[14][3].setOccupied(false);
        map[18][2].setOccupied(false);
        map[20][9].setOccupied(false);
        map[23][7].setOccupied(false);
        map[24][2].setOccupied(false);
    }
}

/** setTrainerPokemon() - randomizes which trainers get what pokemon, as well as the levels of those pokemon (between 1 and 3)
 *  1. For all 15 trainers, generate a random number that will determine how many pokemon are in their pokemon party.
 *  2. For each pokemon in that trainer's party, generate a random number to determine what pokemon will be added. 
 *  3. Using a temporary vector for the pokemon party, push that pokemon into the vector. 
 *  4. Mark that pokemon as having been used for this trainer (in order to not have any duplicate pokemon in a trainer's party).
 *  5. Set the temporary vector of pokemon as that trainer's pokemon party.
*/

void Game::setTrainerPokemon() {
    srand(time(nullptr));
    int index;
    for(int i=0; i<15; i++) {
        int numPokemon = rand()%6 + 1; // generates a random number between 1 and 6 for the number of pokemon
        bool used[151]; // to check if a pokemon has been used already or not for that trainer (0 means not used, 1 means used)
        vector<Pokemon> tempParty; // pokemon party to be created for that trainer
        for(int j=0; j<numPokemon+1; j++) { // for each pokemon
            index = rand()%151; // generate a random index for what pokemon will be chosen
            if(used[index] == 0) { // if that pokemon has not already been chosen:
                tempParty.push_back(allPokemon[index]); // add that pokemon to the temporary vector
                used[index] = 1; // mark that pokemon as used
                trainers[i].setPartyPokemon(tempParty); // set the temporary vector as that trainer's pokemon party
            }
        }
    }
}

/** setWildPokemonPositions() - randomizes the locations of all 20 wild pokemon, so that no pokemon are on the same tile
 *  1. For all 20 of the wild pokemon, generate a random number for the index of what that pokemon will be (from the pokedex).
 *  2. Add that pokemon to the wild pokemon vector.
 *  3. Generate 2 more random numbers, for the rows and columns, to determine the starting position of that pokemon.
 *  4. If that position is occupied, a gym, poke center, or the starting location of the user, generate the random numbers again until the pokemon has a position set.
*/

void Game::setWildPokemonPositions() {
    int userRow = trainers[15].getTrainerRow();
    int userColumn = trainers[15].getTrainerColumn();
    srand(time(nullptr));
    int used[151];
    for(int i=0; i<20; i++) { // for all 20 wild pokemon
        int index = rand()%151; // random index of the pokemon to be added to the wild Pokemon
        if(used[index] != 1) {
            Pokemon pok = allPokemon[index];
            wildPokemon.push_back(pok); // add that pokemon to the wild pokemon vector
            used[index] = 1;
            bool set = false;
            while(set == false) { // while the pokemon's location has not been set:
                int column = rand()%16 + 1; // random number between 1 and 16 (for columns)
                int row = rand()%25 +1; // random number between 1 and 25 (for rows)
                if(map[row][column].ifOccupied() == false && map[row][column].ifWater() == false && row != userRow && column != userColumn) { // if the location is not already occupied by another pokemon, and is a land tile
                    wildPokemon[i].setPokemonRow(row); // set that to be the pokemon's position
                    wildPokemon[i].setPokemonColumn(column);
                    map[row][column].setOccupied(true); // set that tile to occupied
                    set = true; // the pokemon position has been updated
                }
            }
        }
        else {
            i = i-1;
        }
    }
}

/** pokemonBattle() - asks the user what they want to do when they have entered an encounter with a wild pokemon (and then runs those functions).
 *  1. If user wants to flee, run the flee function.
 *  2. If pokemon wants to flee, run the flee function.
 *  3. if user wants to switch active pokemon, run the switch function.
 *  4. If user wants to fight, run the fight function.
*/

void Game::pokemonBattle(int index) {
    srand(time(nullptr));
    int userAttack;
    int userDamage;
    int userDefense;
    int userBlock;
    int currentUserHealth;
    int wildAttack;
    int wildDamage;
    int wildDefense;
    int wildBlock;
    int currentWildHealth;
    int deadCounter = 0;
    int userAttempts = 1;
    int wildAttempts = 1;
    bool userPokemonDead = false;
    bool allUserPokemonDead = false;
    bool wildPokemonDead = false;
    Pokemon tempPok;
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    
    cout << "You ran into a wild Pokemon!" << endl;
    cout << "Name: " << wildPokemon[index].getPokemonName() << ", HP: " << wildPokemon[index].getHealth() << "/" << wildPokemon[index].getMaxHealth() << ", A: " << wildPokemon[index].getAttack() << ", D: " << wildPokemon[index].getDefense() << ", S: " << wildPokemon[index].getSpeed() << ", M: " << wildPokemon[index].getMaxStats() << endl;
    cout << endl;
    cout << "Your ACTIVE Pokemon is: " << endl;
    cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
    
    int currentPokeballs = trainers[15].getPokeballs(); // get the number of pokeballs the user has
    if(currentPokeballs == 0) { // if the user has no pokeballs (they can't catch the pokemon)
        cout << "Oh no! You have no Pokeballs left! " << wildPokemon[index].getPokemonName() << " has been released back into the wild!" << endl;
    }
    else { // else they do have a pokeball remaining
        char battleChoice;
        bool validChoice = false;
        while(wildPokemonDead == false && allUserPokemonDead == false && validChoice == false) { // while the user has made a valid choice, the wild pokemon isn't dead and all of the pokemon in the user's party aren't dead
            cout << endl;
            cout << "What do you want to do? (Pick 1, 2, or 3)" << endl; // display the menu for the user
            cout << "1. Fight" << endl;
            cout << "2. Switch Active Pokemon" << endl;
            cout << "3. Run" << endl;
            string stringBattleChoice;
            cin >> stringBattleChoice;
            battleChoice = stringBattleChoice[0];
            switch(battleChoice) { // get the choice (1,2,3) from the user
                case '1' : {
                    // run the battle phase function
                    if(wildPokemon[index].getSpeed() > userParty[0].getSpeed()) { // if the wild pokemon is faster, it attacks first
                        // first attack phase
                        cout << wildPokemon[index].getPokemonName() << " attacks first." << endl;
                        wildAttack = wildPokemon[index].getAttack();
                        userDefense = userParty[0].getDefense();
                        wildDamage = rand()%(wildAttack) + 1; // generate a number between 1 and the attack of the wild pokemon 
                        userBlock = rand()%(userDefense) + 1; // generate a number between 1 and the defense of the active pokemon
                        if(wildDamage > userBlock) { // if the attack is greater than the block, the attack happens
                            cout << wildPokemon[index].getPokemonName() << " deals " << wildDamage << " damage." << endl;
                            currentUserHealth = userParty[0].getHealth();
                            userParty[0].setHealth(currentUserHealth - wildDamage); // update the pokemon's health
                            cout << endl; // display stats of pokemon again
                            cout << "Wild Pokemon: " << endl;
                            cout << "Name: " << wildPokemon[index].getPokemonName() << ", HP: " << wildPokemon[index].getHealth() << "/" << wildPokemon[index].getMaxHealth() << ", A: " << wildPokemon[index].getAttack() << ", D: " << wildPokemon[index].getDefense() << ", S: " << wildPokemon[index].getSpeed() << ", M: " << wildPokemon[index].getMaxStats() << endl;
                            cout << endl;
                            cout << "Your ACTIVE Pokemon: " << endl;
                            cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            cout << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            if(userParty[0].getHealth() == 0) { // if the user's pokemon has died
                                userParty[0].setFainted(true); // set it to fainted
                                trainers[15].setPartyPokemon(userParty); // update the party
                                userPokemonDead = true; // user pokemon has died
                            } 
                            else if(wildPokemon[index].getHealth() == 0) { // if the wild pokemon has died
                                wildPokemonDead = true; 
                            }
                        }
                        else if(wildDamage <= userBlock) { // if the block is greater than the attack, the attack misses
                            cout << wildPokemon[index].getPokemonName() << "'s attack misses!" << endl;
                            cout << endl;
                        }
                        // second attack phase
                        if(userPokemonDead == false && wildPokemonDead == false) { // if both pokemon are still alive after the first attack phase, the second attack phase occurs
                            cout << userParty[0].getPokemonName() << " attacks next." << endl; // the user pokemon attacks next
                            userAttack = userParty[0].getAttack();
                            wildDefense = wildPokemon[index].getDefense();
                            userDamage = rand()%(userAttack) + 1; // generate a number between 1 and the user's attack
                            wildBlock = rand()%(wildDefense) + 1; // generate a number between 1 and the wild's defense
                            if(userDamage > wildBlock) { // if the attack is greater than the defense
                                cout << userParty[0].getPokemonName() << " deals " << userDamage << " damage." << endl; // damage is dealt
                                currentWildHealth = wildPokemon[index].getHealth();
                                wildPokemon[index].setHealth(currentWildHealth - userDamage); // update the wild pokemon's health
                                cout << endl; // display the stats of the pokemon again
                                cout << "Your ACTIVE Pokemon: " << endl;
                                cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                                cout << endl;
                                cout << "Wild Pokemon: " << endl;
                                cout << "Name: " << wildPokemon[index].getPokemonName() << ", HP: " << wildPokemon[index].getHealth() << "/" << wildPokemon[index].getMaxHealth() << ", A: " << wildPokemon[index].getAttack() << ", D: " << wildPokemon[index].getDefense() << ", S: " << wildPokemon[index].getSpeed() << ", M: " << wildPokemon[index].getMaxStats() << endl;
                                cout << endl;
                                trainers[15].setPartyPokemon(userParty); // update the user's party
                                if(userParty[0].getHealth() == 0) { // if the user's pokemon died after the second attack phase
                                    userParty[0].setFainted(true); // set to fainted
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    userPokemonDead = true; // user's pokemon has died
                                } 
                                else if(wildPokemon[index].getHealth() == 0) { // if the wild pokemon died
                                    wildPokemonDead = true; 
                                }
                            }
                            else { // if the attack wasn't greater than the defense, the attack misses and nothing happens
                                cout << userParty[0].getPokemonName() << "'s attack misses.!" << endl;
                                cout << endl;
                            }
                        }
                    }
                    else if(wildPokemon[index].getSpeed() <= userParty[0].getSpeed()) { // if the user's pokemon is faster than the wild pokemon
                        // first attack phase 
                        cout << userParty[0].getPokemonName() << " attacks first." << endl; // the user attacks first
                        userAttack = userParty[0].getAttack();
                        wildDefense = wildPokemon[index].getDefense();
                        userDamage = rand()%(userAttack) + 1; // generate a number between 1 and the user's attack
                        wildBlock = rand()%(wildDefense) + 1; // generate a number between 1 and the wild's defense
                        if(userDamage > wildBlock) { // if the attack is greater than the block, damage occurs
                            cout << userParty[0].getPokemonName() << " deals " << userDamage << " damage." << endl;
                            currentWildHealth = wildPokemon[index].getHealth();
                            wildPokemon[index].setHealth(currentWildHealth - userDamage); // update the wild pokemon's health
                            cout << endl; // display the stats of the pokemon again
                            cout << "Your ACTIVE Pokemon: " << endl;
                            cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            cout << endl;
                            cout << "Wild Pokemon: " << endl;
                            cout << "Name: " << wildPokemon[index].getPokemonName() << ", HP: " << wildPokemon[index].getHealth() << "/" << wildPokemon[index].getMaxHealth() << ", A: " << wildPokemon[index].getAttack() << ", D: " << wildPokemon[index].getDefense() << ", S: " << wildPokemon[index].getSpeed() << ", M: " << wildPokemon[index].getMaxStats() << endl;
                            cout << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            if(userParty[0].getHealth() == 0) { // if the user's pokemon died during the first attac phase
                                userParty[0].setFainted(true); // set the pokemon as fainted
                                trainers[15].setPartyPokemon(userParty); // update the user's party
                                userPokemonDead = true; // user pokemon has died
                            } 
                            else if(wildPokemon[index].getHealth() == 0) { // if the wild pokemon died during the first attack phase
                                wildPokemonDead = true; // the wild pokmeon has died
                            }
                        }
                        else { // if the attack wasn't greater than the defense, the attack misses
                            cout << userParty[0].getPokemonName() << "'s attack misses!" << endl;
                            cout << endl;
                        }
                        // second attack phase
                        if(userPokemonDead == false && wildPokemonDead == false) { // if neither pokemon died during the first attack phase
                            cout << wildPokemon[index].getPokemonName() << " attacks next." << endl; // the wild pokemon attacks
                            wildAttack = wildPokemon[index].getAttack();
                            userDefense = userParty[0].getDefense();
                            wildDamage = rand()%(wildAttack) +1; // generate a number between 1 and the wild attack
                            userBlock = rand()%(userDefense)+1; // generate a number between 1 and the user defense
                            if(wildDamage > userBlock) { // if the attack is greater than the defense
                                cout << wildPokemon[index].getPokemonName() << " deals " << wildDamage << " damage." << endl; // damage occurs
                                currentUserHealth = userParty[0].getHealth();
                                userParty[0].setHealth(currentUserHealth - wildDamage); // update the user's health
                                cout << endl; // display the stats
                                cout << "Wild Pokemon: " << endl;
                                cout << "Name: " << wildPokemon[index].getPokemonName() << ", HP: " << wildPokemon[index].getHealth() << "/" << wildPokemon[index].getMaxHealth() << ", A: " << wildPokemon[index].getAttack() << ", D: " << wildPokemon[index].getDefense() << ", S: " << wildPokemon[index].getSpeed() << ", M: " << wildPokemon[index].getMaxStats() << endl;
                                cout << endl;
                                cout << "Your ACTIVE Pokemon: " << endl;
                                cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                                cout << endl;
                                trainers[15].setPartyPokemon(userParty); // update the user's party
                                if(userParty[0].getHealth() == 0) { // if the user's pokemon died
                                    userParty[0].setFainted(true); // set fainted to true
                                    trainers[15].setPartyPokemon(userParty); // update the user party
                                    userPokemonDead = true; // user pokemon has died
                                }
                                else if(wildPokemon[index].getHealth() == 0) { // if the wild pokemon has died
                                    wildPokemonDead = true; 
                                }
                            }
                            else if(wildDamage <= userBlock) { // if the attack wasn't greater than the damage, the attack misses
                                cout << wildPokemon[index].getPokemonName() << "'s attack misses!" << endl;
                                cout << endl;
                            }
                        }
                    }
                    int ifFlee = Game::wildFlee(wildPokemon[index].getSpeed(), userParty[0].getSpeed(), wildAttempts); // see if the wild pokemon wants to flee
                    if(ifFlee == 1) { // if the pokemon has fleed successfully
                        bool set = false;
                        while(set == false) { // update the pokemon's new randomized location
                            int wildRow = rand()%16 +1;
                            int wildColumn = rand()%25 +1;
                            if(map[wildRow][wildColumn].ifOccupied() == false && map[wildRow][wildColumn].getTile() == '*') {
                                wildPokemon[index].setPokemonRow(wildRow);
                                wildPokemon[index].setPokemonColumn(wildColumn);
                                set = true;
                            }
                        }
                    }
                    else if(ifFlee == 0) { // if the pokemon wants to flee but failed, increase the number of attempts
                        cout << wildPokemon[index].getPokemonName() << " tried to flee but failed!" << endl;
                        wildAttempts++;
                    }
                    
                    // if your pokemon dies : 
                    if(userPokemonDead == true) {
                        wildPokemon[index].levelUp(); // level up the wild pokemon
                        for(int x=0; x<userParty.size(); x++) { // go through the user's arty
                            if(userParty[x].isFainted() == true) { 
                                deadCounter++; // if the pokemon has fainted, increase the dead counter
                            }
                        }
                        if(deadCounter == userParty.size()) { // if all of the pokemon in the user's party are fainted, they lose the battle
                            cout << "All of your Pokemon have fainted! You will be teleported to the nearest Pokemon Center!" << endl;
                            int r = trainers[15].getTrainerRow();
                            int c = trainers[15].getTrainerColumn();
                            Game::nearestPokemonCenter(r, c); // transport to nearest pokemon center
                            validChoice = true; // the user has made a valid choice
                            allUserPokemonDead = true; // and all of the user's pokemon are dead (ends the battle loop)
                        }
                        else { // they still have pokemon alive in their party
                            cout << "Your Active Pokemon has fainted!" << endl;
                            tempPok = userParty[0]; // move their active party to the end
                            userParty.erase(userParty.begin() + 0);
                            userParty.push_back(tempPok);
                            trainers[15].setPartyPokemon(userParty); // update the party
                            Game::switchActivePokemon(); // switch active pokemon (not showing the fainted pokemon)
                            userPokemonDead = false; // user pokemon is no longer dead
                            // validChoice = false
                        }
                    }
                    // if wild pokemon dies:
                    if(wildPokemonDead == true) {
                        catchPokemon(index); // catch the pokemon
                        userParty[0].levelUp(); // level up the user's active pokemon
                        trainers[15].setPartyPokemon(userParty);
                        validChoice = true; // the user has made a valid choice
                    }
                    break;
                }
                case '2' : { // the user wants to switch active pokemon
                    Game::switchActivePokemon();
                    validChoice = false; // it is a valid choice, but it basically just needs to run until the user chooses 1 or 3
                    break;
                }
                case '3' : { // the user wants to flee
                    int ifUserFlee = Game::flee(userParty[0].getSpeed(), wildPokemon[index].getSpeed(), userAttempts); // see if they will flee
                    if(ifUserFlee == 1) { // if the flee is successfull
                        cout << userParty[0].getPokemonName() << "'s flee was successful!" << endl;
                        int r = trainers[15].getTrainerRow();
                        int c = trainers[15].getTrainerColumn();
                        Game::nearestPokemonCenter(r, c); // teleport to nearest pokemon center
                        validChoice = true; // the user has made a valid choice
                    }
                    else if (ifUserFlee == 0) { // the flee was unsuccessful
                        cout << userParty[0].getPokemonName() << "'s flee was unsuccessful!" << endl;
                        userAttempts++; // increase the number of attempts
                        validChoice = false; // the user has not made a valid choice that will end the battle
                    }
                    break;
                }
                default : { // the user did not choose either 1,2,3
                    cout << "Please choose a valid option (1, 2, or 3)" << endl;
                    validChoice = false;
                    break;
                }
            }
        }
    }
}

/** fleeOrFight() - determines if the wild pokemon or user will flee or fight
 *  1. Generate a random number to determine if the wild pokemon wants to flee or not.
 *  2. If they don't want to flee, they fight. (return 2)
 *  3. If they do want to flee, run the calculation to find the value of F.
 *  4. If F is greater than 255, the user flees successfully. (return 1)
 *  5. Otherwise, generate a random number between 0 and 255, if that number is less than the F calculated, the user flee successfully. (return 1)
 *  6. Else, the user has to stay and fight. (return 0)
*/

int Game::wildFlee(int speedWild, int speedPlayer, int attempts) { // based on the speed of each and the number of attempts by the wild pokemon:
    srand(time(nullptr));
    int flee = rand()%100 +1; // to determine if the pokemon wants to flee or not
    if(flee <= 40) { // meaning the pokemon want's to flee
        int A = speedWild;
        int B = (speedPlayer/4)%256;
        int C = attempts;
        int F = ((A*32)/B) + (30*C);
        if(F > 255) { // if F is greater than 255, the flee was successful and the wild pokemon flees
            return 1; 
        }
        else {
            // random number generated between 0 and 255
            int chance = rand()%256;
            if(F > chance) { // if the chance is less than F, the flee was successful
                return 1;
            }
            else {
                return 0; // otherwise the flee wasn't successful
            }
        }
    }
    else { // meaning the pokemon wants to fight
        return 2;
    }
}

/** flee() - what happens when the the flee was successful
 *  1. Runs the calculation to find the value of F.
 *  2. If F is greater than 255, the user flees successfully. (return 1)
 *  3. Otherwise, generate a random number between 0 and 255, if that number is less than the F calculated, the user flee successfully.(return 1)
 *  4. Else, the user has to stay and fight. (return 0)
*/

int Game::flee(int speedPlayer, int speedWild, int attempts) { // based on the speed of each pokemon and the number of attempts:
    int A = speedPlayer;
    int B = (speedWild/4)%256;
    int C = attempts;
    int F = ((A*32)/B) + (30*C);
    if(F > 255) { // if F is greater than 255, the flee was successful
        return 1;
    }
    else {
        // random number generated between 0 and 255
        srand(time(nullptr));
        int chance = rand()%256; 
        if(F > chance) { // the random number is less than F, the flee is successful
            return 1;
        }
        else { // otherwise the flee wasn't successful
            return 0;
        }
    }
}

/** switchActivePokemon() - prompts user to choose a new active pokemon, after displaying the current active pokemon and the list of pokemon in their suite.
 *  1. Display  a list of the pokemon in their suite, not including the active pokemon (in position 0)
 *      a. Depending on how long the party vector is, display different numbers.
 *  2. Prompt the user to choose a new pokemon, as a character value.
 *      a. If that value is valid for the length of the party vector, then switch the current active pokemon with the desired active pokemon.
 *      b. If that value is not valid, display an error message asking the user to pick a different value.
 *  3. Display the user's new current active pokemon along with its stats.
*/

void Game::switchActivePokemon() {
    int availablePokemon = 0;
    vector<Pokemon> userParty;
    userParty = trainers[15].getPartyPokemon();
    for(int i=0; i<userParty.size(); i++) { // display the pokemon in the suite, ignoring the first one (the current active pokemon)
        if(userParty[i].isFainted() == false) { // if the pokemon is not fainted
            availablePokemon++; // increase the number of pokemon that the user can choose from
        }
    }
    if(availablePokemon >= 1) { // if the user has more pokemon in their suite other than the current active pokemon
        if(availablePokemon == 1) { // only one other pokemon in suite
            cout << "Pick another Active Pokemon (1): " << endl;
        }
        else if(availablePokemon == 2) { // two other pokemon in suite
            cout << "Pick another Active Pokemon (1, or 2): " << endl;
        }
        else if(availablePokemon == 3) { // three other pokemon in suite
            cout << "Pick another Active Pokemon (1, 2, or 3): " << endl;
        }
        else if(availablePokemon == 4) { // four other pokemon in suite
            cout << "Pick another Active Pokemon (1, 2, 3, or 4): " << endl;
        }
        else if(availablePokemon == 5) { // five other pokemon in suite
            cout << "Pick another Active Pokemon (1, 2, 3, 4, or 5): " << endl;
        }
        int faintedCounter = 0;
        for(int i=0; i<userParty.size(); i++) { // display the pokemon in the suite, ignoring the first one (the current active pokemon)
            if(userParty[i].isFainted() == false) { // if the pokemon is not fainted
                cout << i+1-faintedCounter << ". " << userParty[i].getPokemonName() << endl; // display the pokemon
            }
            else {
                faintedCounter++; // increase the number of fainted pokemon (which are at the end of the vector ideally)
            }
        }
        Pokemon tempPok;
        char choice;
        bool validChoice = false;
        while(validChoice == false) { // until the user gives a valid response
            string stringChoice;
            cin >> stringChoice;
            choice = stringChoice[0];
            switch(choice) {
                case '1' : // if they chose the first pokemon displayed (the pokemon in position 1): 
                    if(availablePokemon >= 1) { // the desired active pokemon is already in position 1
                        validChoice = true; // the user has made a valid choise
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    break;
                case '2' : // if they chose the second pokemon displayed (the pokemon in position 2): 
                    if(availablePokemon >= 2) { // and there exists a pokemon in position 2: 
                        userParty[0] = tempPok;
                        userParty[0] = userParty[1]; // switch the current active pokemon with the desired pokemon
                        userParty[1] = tempPok;
                        validChoice = true; // the user has made a valid choice
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    else { // otherwise there isn't a second pokemon
                        cout << "Invalid option, please enter a different number. " << endl; 
                    }
                    break;
                case '3' : // if they chose the third pokemon displayed (the pokemon in position 3):
                    if(availablePokemon >= 3) { // and there exists a pokemon in position 3:
                        userParty[0] = tempPok;
                        userParty[0] = userParty[2]; // switch the current active pokemon with the desired pokemon
                        userParty[2] = tempPok;
                        validChoice = true; // the user has made a valid choice
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    else { // otherwise there isn't a third option
                        cout << "Invalid option, please enter a different number. " << endl;
                    }
                    break;
                case '4' : // if they chose the fourth pokemon displayed (the pokemon in position 4):
                    if(availablePokemon >= 4) { // and there exists a pokemon in position 4:
                        userParty[0] = tempPok;
                        userParty[0] = userParty[3]; // switch the current active pokemon with the desired pokemon
                        userParty[3] = tempPok;
                        validChoice = true; // the user has made a valid choice
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    else { // otherwise there isn't a fourth option
                        cout << "Invalid option, please enter a different number. " << endl;
                    }
                    break;
                case '5' : // if the chose the fifth pokemon displayed (the pokemon in position 5):
                    if(availablePokemon >= 5) { // and there axists a pokemon in position 5:
                        userParty[0] = tempPok;
                        userParty[0] = userParty[4]; // switch the current active pokemon with the desired pokemon
                        userParty[4] = tempPok;
                        validChoice = true; // the user has made a valid choice
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    else { // otherwise there isn't a fifth option
                        cout << "Invalid option, please enter a different number. " << endl;
                    }
                    break;
                case '6' : 
                    if(availablePokemon >= 6) { // and there axists a pokemon in position 5:
                        userParty[0] = tempPok;
                        userParty[0] = userParty[5]; // switch the current active pokemon with the desired pokemon
                        userParty[5] = tempPok;
                        validChoice = true; // the user has made a valid choice
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                    }
                    else { // otherwise there isn't a fifth option
                        cout << "Invalid option, please enter a different number. " << endl;
                    }
                    break;
                default : // a valid number (1-6) wasn't given
                    cout << "Please enter one of the numbers given. " << endl;
                    break;
            }
        }
        trainers[15].setPartyPokemon(userParty); // update the user's party
    }
    else { // there is only 1 pokemon in the party, being the current active pokemon
        cout << "You don't have any Pokemon left! " << endl; // the user has no pokemon that aren't fainted and therefore can't choose a new active pokemon
    }
}

/** trainerBattle() - runs the battle prompt for when battling a trainer
 *  1. Displays the trainer pokemon and the user pokemon, then displays a menu for the options: fight or switch active pokemon
 *  2. If fight, run the fight function
 *  3. If switch function, run the switch pokemon function, then return to the menu.
*/

void Game::trainerBattle(int index) {
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon();
    vector<Pokemon> trainerParty = trainers[index].getPartyPokemon();
    int userAttack;
    int userDamage;
    int userDefense;
    int userBlock;
    int currentUserHealth;
    int trainerAttack;
    int trainerDamage;
    int trainerDefense;
    int trainerBlock;
    int currentTrainerHealth;
    int deadCounter = 0;
    int userAttempts = 1;
    bool userPokemonDead = false;
    bool allUserPokemonDead = false;
    bool trainerPokemonDead = false;
    bool allTrainerPokemonDead = false;
    Pokemon tempPok;
    
    // display the menu for the pokemon battle
    cout << "You arrived at the Gym and trainer " << trainers[index].getUsername() << " wants to fight." << endl;
    cout << "Their ACTIVE Pokemon is: " << endl;
    cout << "Name: " << trainerParty[0].getPokemonName() << ", HP: " << trainerParty[0].getHealth() << ", A: " << trainerParty[0].getAttack() << ", D: " << trainerParty[0].getDefense() << ", S: " << trainerParty[0].getSpeed() << ", M: " << trainerParty[0].getMaxStats() << endl;
    
    cout << "And their Party Pokemon are:" << endl;
    for(int i=1; i<trainerParty.size(); i++) {
        cout << "Name: " << trainerParty[i].getPokemonName() << ", HP: " << trainerParty[i].getHealth() << ", A: " << trainerParty[i].getAttack() << ", D: " << trainerParty[i].getDefense() << ", S: " << trainerParty[i].getSpeed() << ", M: " << trainerParty[i].getMaxStats() << endl;
    }
    char choice;
    bool validChoice = false;
    while(validChoice == false && allUserPokemonDead == false && allTrainerPokemonDead == false) { // until the user has made a valid choice, or everyone's pokemon die
        cout << endl;
        cout << "Your ACTIVE Pokemon is: " << endl;
        cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
        cout << endl;
        cout << "What do you want to do? (Pick 1, 2, or 3)" << endl; // display the menu
        cout << "1. Fight" << endl;
        cout << "2. Switch Active Pokemon" << endl;
        string stringChoice;
        cin >> stringChoice;
        choice = stringChoice[0];
        switch(choice) {
            case '1' : { // if the user wants to fight
                // run the battle phase function
                if(trainerParty[0].getSpeed() > userParty[0].getSpeed()) { // if the trainer's pokemon is faster
                    // first attack phase
                    cout << trainerParty[0].getPokemonName() << " attacks first." << endl; // trainer attack first
                    trainerAttack = trainerParty[0].getAttack();
                    userDefense = userParty[0].getDefense();
                    trainerDamage = rand()%(trainerAttack) + 1; // generate a number between 1 and trainer attack
                    userBlock = rand()%(userDefense) + 1; // generate a number between 1 and user defense
                    if(trainerDamage > userBlock) { // if the attack is greater then the defense
                        cout << trainerParty[0].getPokemonName() << " deals " << trainerDamage << " damage." << endl; // damage occurs
                        currentUserHealth = userParty[0].getHealth(); 
                        userParty[0].setHealth(currentUserHealth - trainerDamage); // update the user's health
                        cout << endl; // display the stats
                        cout << "Trainer's Active Pokemon: " << endl;
                        cout << "Name: " << trainerParty[0].getPokemonName() << ", HP: " << trainerParty[0].getHealth() << "/" << trainerParty[0].getMaxHealth() << ", A: " << trainerParty[0].getAttack() << ", D: " << trainerParty[0].getDefense() << ", S: " << trainerParty[0].getSpeed() << ", M: " << trainerParty[0].getMaxStats() << endl;
                        cout << endl;
                        cout << "Your ACTIVE Pokemon: " << endl;
                        cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                        cout << endl;
                        trainers[15].setPartyPokemon(userParty); // update the user's party
                        trainers[index].setPartyPokemon(trainerParty); // update the trainer's party
                        if(userParty[0].getHealth() == 0) { // if the user pokemon died during the first attack phase
                            userParty[0].setFainted(true); // set that pokemon has fainted
                            trainers[15].setPartyPokemon(userParty); // update the user party
                            userPokemonDead = true; // a user's pokemon has died
                        }
                        else if(trainerParty[0].getHealth() == 0) { // if the trainer pokemo diead during the first attack phase
                            trainerParty[0].setFainted(true); // set that pokemon to fainted
                            trainers[index].setPartyPokemon(trainerParty); // update the trainer party
                            trainerPokemonDead = true; // trainer pokemon has died
                        }
                    }
                    else if(trainerDamage <= userBlock) { // otherwise if the attack isn't greater than the defense, the attack misses
                        cout << trainerParty[0].getPokemonName() << "'s attack misses!" << endl;
                        cout << endl;
                    }
                    // second attack phase
                    if(userPokemonDead == false && trainerPokemonDead == false) { // if both pokemon are still alive after the first attack phase
                        cout << userParty[0].getPokemonName() << " attacks next." << endl; // the user's pokemon attacks next
                        userAttack = userParty[0].getAttack();
                        trainerDefense = trainerParty[0].getDefense();
                        userDamage = rand()%(userAttack) +1; // generate a number between 1 and the user attack
                        trainerBlock = rand()%(trainerDefense) +1; // generate a number between 1 and the trainer defense
                        if(userDamage > trainerBlock) { // if the attack is greater than the defense
                            cout << userParty[0].getPokemonName() << " deals " << userDamage << " damage." << endl; // damage is dealt
                            currentTrainerHealth = trainerParty[0].getHealth();
                            trainerParty[0].setHealth(currentTrainerHealth - userDamage); // update the trainers health
                            cout << endl; // display stats again
                            cout << "Trainer's Active Pokemon: " << endl;
                            cout << "Name: " << trainerParty[0].getPokemonName() << ", HP: " << trainerParty[0].getHealth() << "/" << trainerParty[0].getMaxHealth() << ", A: " << trainerParty[0].getAttack() << ", D: " << trainerParty[0].getDefense() << ", S: " << trainerParty[0].getSpeed() << ", M: " << trainerParty[0].getMaxStats() << endl;
                            cout << endl;
                            cout << "Your ACTIVE Pokemon: " << endl;
                            cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            cout << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user party
                            trainers[index].setPartyPokemon(trainerParty); // update the trainer party
                            if(userParty[0].getHealth() == 0) { // if the users pokemon died during the second attack phase
                                userParty[0].setFainted(true); // set the pokemon to fainted
                                trainers[15].setPartyPokemon(userParty); // update the party
                                userPokemonDead = true; // user pokemon has died
                            }
                            else if(trainerParty[0].getHealth() == 0) { // if the trainer's pokemon died during the second attack phase
                                trainerParty[0].setFainted(true); // set the pokemon to fainted
                                trainers[0].setPartyPokemon(trainerParty); // update the party
                                trainerPokemonDead = true; // trainer pokemon has died
                            }
                        }
                        else { // otherwise the attack wasn't greater than the defense and the attack misses
                            cout << userParty[0].getPokemonName() << "'s attack misses.!" << endl;
                            cout << endl;
                        }
                    }
                }
                else if(trainerParty[0].getSpeed() <= userParty[0].getSpeed()) { // if the user pokemon is faster than the trainer pokemon
                    // first attack phase
                    cout << userParty[0].getPokemonName() << " attacks first." << endl; // the user attacks first
                    userAttack = userParty[0].getAttack();
                    trainerDefense = trainerParty[0].getDefense();
                    userDamage = rand()%(userAttack) +1; // generate a number between 1 and the user attack
                    trainerBlock = rand()%(trainerDefense) +1; // generate a number between 1 and the trainer defense
                    if(userDamage > trainerBlock) { // if the attack is greater than the block
                        cout << userParty[0].getPokemonName() << " deals " << userDamage << " damage." << endl; // damage is dealt
                        currentTrainerHealth = trainerParty[0].getHealth(); 
                        trainerParty[0].setHealth(currentTrainerHealth - userDamage); // update the trainer's health
                        cout << endl; // display the stats of the active pokemon
                        cout << "Trainer's Active Pokemon: " << endl;
                        cout << "Name: " << trainerParty[0].getPokemonName() << ", HP: " << trainerParty[0].getHealth() << "/" << trainerParty[0].getMaxHealth() << ", A: " << trainerParty[0].getAttack() << ", D: " << trainerParty[0].getDefense() << ", S: " << trainerParty[0].getSpeed() << ", M: " << trainerParty[0].getMaxStats() << endl;
                        cout << endl;
                        cout << "Your ACTIVE Pokemon: " << endl;
                        cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                        cout << endl;
                        trainers[15].setPartyPokemon(userParty); // update the user party
                        trainers[index].setPartyPokemon(trainerParty); // update the trainer party
                        if(userParty[0].getHealth() == 0) { // if the user pokemon died during the first attack phase
                            userParty[0].setFainted(true); // set that pokemon as fainted
                            trainers[15].setPartyPokemon(userParty); // update the party
                            userPokemonDead = true; // user pokemon has died
                        }
                        else if(trainerParty[0].getHealth() == 0) { // if the trainer pokemon died during the first attack phase
                            trainerParty[0].setFainted(true); // set that pokemon as fainted
                            trainers[index].setPartyPokemon(trainerParty); // update the partt
                            trainerPokemonDead = true; // trainer pokemon has died
                        }
                    }
                    else { // if the attack is not greater than the defense, the attack misses
                        cout << userParty[0].getPokemonName() << "'s attack misses!" << endl;
                        cout << endl;
                    }
                    // second attack phase
                    if(userPokemonDead == false && trainerPokemonDead == false) { // if both pokemon are still alive after the first attack phase
                        cout << trainerParty[0].getPokemonName() << " attacks next." << endl; // the trainer pokemon attacks next
                        trainerAttack = trainerParty[0].getAttack();
                        userDefense = userParty[0].getDefense();
                        trainerDamage = rand()%(trainerAttack) +1; // generate a number between 1 and the trainer attack
                        userBlock = rand()%(userDefense) +1; // generate a number between 1 and the user defense
                        if(trainerDamage > userBlock) { // if the attack is greater than the defense
                            cout << trainerParty[0].getPokemonName() << " deals " << trainerDamage << " damage." << endl; // damage occurs
                            currentUserHealth = userParty[0].getHealth();
                            userParty[0].setHealth(currentUserHealth - trainerDamage); // update the user's health
                            cout << endl; // display the stats again
                            cout << "Trainer's Active Pokemon: " << endl;
                            cout << "Name: " << trainerParty[0].getPokemonName() << ", HP: " << trainerParty[0].getHealth() << "/" << trainerParty[0].getMaxHealth() << ", A: " << trainerParty[0].getAttack() << ", D: " << trainerParty[0].getDefense() << ", S: " << trainerParty[0].getSpeed() << ", M: " << trainerParty[0].getMaxStats() << endl;
                            cout << endl;
                            cout << "Your ACTIVE Pokemon: " << endl;
                            cout << "Name: " << userParty[0].getPokemonName() << ", HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            cout << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user party
                            trainers[index].setPartyPokemon(trainerParty); // update the trainer party
                            if(userParty[0].getHealth() == 0) { // if the user pokemon died during the second attack phase
                                userParty[0].setFainted(true); // set that pokemon as fainted
                                trainers[15].setPartyPokemon(userParty); // update the user's party
                                userPokemonDead = true; // user pokemon has died
                            }
                            else if(trainerParty[0].getHealth() == 0) { // if the trainer pokemon during the second attack phase
                                trainerParty[0].setFainted(true); // set that pokemon as fainted
                                trainers[index].setPartyPokemon(trainerParty); // update the tainer's party
                                trainerPokemonDead = true; // trainer pokemon has died
                            }
                        }
                        else if(trainerDamage <= userBlock) { // if the attack wasn't greater than the defense, the attack misses
                            cout << trainerParty[0].getPokemonName() << "'s attack misses!" << endl;
                            cout << endl;
                        }
                    }
                }
                // if your pokemon dies : 
                if(userPokemonDead == true) {
                    deadCounter = 0;
                    trainerParty[0].levelUp(); // level up the trainer pokemon
                    trainers[index].setPartyPokemon(trainerParty); // update the trainer party
                    for(int x=0; x<userParty.size(); x++) { // go through th user's party
                        if(userParty[x].isFainted() == true) { // if the pokemon has fainted 
                            deadCounter++; // increase the dead counter
                        }
                    }
                    if(deadCounter == userParty.size()) { // if all of the pokemon have fainted
                        cout << "All of your Pokemon have fainted! You will be teleported to the nearest Pokemon Center!" << endl;
                        int r = trainers[15].getTrainerRow();
                        int c = trainers[15].getTrainerColumn();
                        Game::nearestPokemonCenter(r, c); // teleport user to nearest pokemon center
                        validChoice = true; // the user has made a valid choice
                        allUserPokemonDead = true; // all of the user pokemon have died
                    }
                    else { // the user still has non-fainted pokemon
                        cout << "Your Active Pokemon has fainted!" << endl;
                        tempPok = userParty[0]; // move their active party to the end
                        userParty.erase(userParty.begin() + 0);
                        userParty.push_back(tempPok);
                        trainers[15].setPartyPokemon(userParty); // update the user's party
                        Game::switchActivePokemon(); // switch active pokemon (not fainted)
                        userPokemonDead = false; // user active pokemon is no longer dead
                        // validChoice = false
                    }
                }
                // if trainer pokemon dies:
                if(trainerPokemonDead == true) {
                    deadCounter = 0; 
                    userParty[0].levelUp(); // level up the current user active pokemon 
                    trainers[15].setPartyPokemon(userParty); // update the user party
                    for(int x=0; x<trainerParty.size(); x++) { // go through the trainer's party
                        if(trainerParty[x].isFainted() == true) { // if the pokemon has fainted
                            deadCounter++; // increase the counter
                        }
                    }
                    if(deadCounter == trainerParty.size()) { // if all of the trainer's pokemon have fainted: you get them!
                        cout << "All of " << trainers[index].getUsername() << "'s Pokemon have fainted!" << endl;
                        cout << "You have won the trainer battle!" << endl;
                        trainers[index].setDefeated(true); // the trainer has been defeated
                        int userBadges = trainers[15].getBadges(); // give the user a badge
                        trainers[15].setBadges(userBadges + 1); 
                        int userPokeballs = trainers[15].getPokeballs(); // give the user 5 pokeballs
                        trainers[15].setPokeballs(userPokeballs + 5);
                        trainers[15].addPoints(60); // give the user 60 points
                        for(int i=0; i<trainerParty.size(); i++) {
                            if(userParty.size() != 6) { // if the party is not full, add the pokemon to the party
                                userParty.push_back(trainerParty[i]);
                                trainers[15].setPartyPokemon(userParty); // update the user's party
                                cout << trainerParty[i].getPokemonName() << " has been added to your party! " << endl;
                            }
                            else if (userParty.size() == 6) { // if the party is full
                                cout << "Your party is full! Would you like to add " << trainerParty[i].getPokemonName() << " to your Active Party? (Y/N)" << endl;
                                char addChoice;
                                bool addChoiceValid = false;
                                string stringAddChoice;
                                while(addChoiceValid == false) { // until the user has made a valid choice for if they want to add that pokemon to their party
                                    cin >> stringAddChoice;
                                    addChoice = stringAddChoice[0];
                                    switch(addChoice) {
                                        case 'Y' : { // if the user wants to add the pokemon
                                            cout << "Which Pokemon would you like to replace " << trainerParty[i].getPokemonName() << " with?" << endl;
                                            for(int j=0; j<userParty.size(); j++) { // display all of the pokemon in the user's party
                                                cout << j+1 << ". " << userParty[i].getPokemonName() << endl;
                                            }
                                            char switchChoice;
                                            bool switchChoiceValid;
                                            string stringSwitchChoice;
                                            while(switchChoiceValid == false) { // until the user has made a valid choice for which pokemon to replace
                                                cin >> stringSwitchChoice;
                                                switchChoice = stringSwitchChoice[0];
                                                switch(switchChoice) {
                                                    case '1' : // if the first pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party and is now your Active Pokemon!" << endl;
                                                        cout << userParty[0].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[0]; 
                                                        userParty[0] = trainerParty[i]; // set the first pokemon as the trainer's pokemon
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break;
                                                    case '2' : // if the second pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party!" << endl;
                                                        cout << userParty[1].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[1]; 
                                                        userParty[1] = trainerParty[i]; // set the second pokemon as the trainer's pokemon
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break;
                                                    case '3' : // if the third pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party!" << endl;
                                                        cout << userParty[2].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[2];
                                                        userParty[2] = trainerParty[i]; // set the third pokemon as the trainer's pokemon
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break;
                                                    case '4' : // if the fourth pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party!" << endl;
                                                        cout << userParty[3].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[3];
                                                        userParty[3] = trainerParty[i]; // set the fourth pokemon as the trainer's pokemon
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break; 
                                                    case '5' : // if the fifth pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party!" << endl;
                                                        cout << userParty[4].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[4];
                                                        userParty[4] = trainerParty[i]; // set the fifth pokemon as the trainer's pokemon
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break;
                                                    case '6' : // if the sixth pokemon displayed
                                                        cout << trainerParty[i].getPokemonName() << " has been added to your Party!" << endl;
                                                        cout << userParty[5].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                                        tempPok = userParty[5];
                                                        userParty[5] = trainerParty[i]; // set the sixth pokemon as the trainer's pokemon 
                                                        userPokedex.push_back(tempPok); // add the user's pokemon to the pokedex
                                                        trainers[15].setPartyPokemon(userParty); // update the user's party
                                                        switchChoiceValid = true; // the user has made a valid choice
                                                        break;
                                                    default : // the user has not made a valid choice
                                                        cout << "Please choose a valid option (1-6)." << endl;
                                                        break;
                                                }
                                            }
                                            addChoiceValid = true; // the user has made a valid yes or no choice (for if they want to add the trainer's pokemon to their party)
                                            break;
                                        }
                                        case 'N' : // the user doesn't want to add the trainer's pokemon to their party
                                            cout << "Okay! " << trainerParty[i].getPokemonName() << " will be added to your Pokedex!" << endl;
                                            userPokedex.push_back(trainerParty[i]); // add the trainer's pokemon to the pokedex
                                            trainers[15].setPokedexPokemon(userPokedex); // update the user's party
                                            addChoiceValid = true; // the user has made a valid yes or no choice
                                            break;
                                        default : // the user has not made a valid yes or no choice
                                            cout << "Please enter either Y or N." << endl;
                                            break;
                                    }
                                }
                            }
                        }
                        validChoice = true; // the user has made a valid choice for the battle
                        allTrainerPokemonDead = true; // all of the trainer pokemon have died (and been added to the user's pokemon)
                    }
                    else { // if the user's active pokemon has fainted
                        cout << trainers[index].getUsername()  << "'s Active Pokemon has fainted!" << endl;
                        tempPok = trainerParty[0]; // move their active pokemon to the end (that has just fainted)
                        trainerParty.erase(trainerParty.begin() + 0); // the new pokemon in the first position will become their next active pokemon
                        trainerParty.push_back(tempPok);
                        trainers[index].setPartyPokemon(trainerParty); // update the party
                        trainerPokemonDead = false; // the trainer's active pokemon is no longer dead
                    }
                }
                break;
            }
            case '2' : { // if the user wants to pick a new active pokemon
                if(userParty.size() > 1) { // if the user has more pokemon in their suite other than the current active pokemon
                    if(userParty.size() == 2) { // only one other pokemon in suite
                        cout << "Pick another Active Pokemon (1): " << endl;
                    }
                    else if(userParty.size() == 3) { // two other pokemon in suite
                        cout << "Pick another Active Pokemon (1, or 2): " << endl;
                    }
                    else if(userParty.size() == 4) { // three other pokemon in suite
                        cout << "Pick another Active Pokemon (1, 2, or 3): " << endl;
                    }
                    else if(userParty.size() == 5) { // four other pokemon in suite
                        cout << "Pick another Active Pokemon (1, 2, 3, or 4): " << endl;
                    }
                    else if(userParty.size() == 6) { // five other pokemon in suite
                        cout << "Pick another Active Pokemon (1, 2, 3, 4, or 5): " << endl;
                    }
                    int i = 1;
                    int faintedCounter = 0;
                    while(i<userParty.size()) { // display the pokemon in the suite, ignoring the first one (the current active pokemon)
                        if(userParty[i].isFainted() == false) { // if the pokemon is not fainted
                            cout << i-faintedCounter << ". " << userParty[i].getPokemonName() << endl; // display the pokemon
                        }
                        else { // if the pokemon is fainted
                            faintedCounter++; // increase the fainted counter
                        }
                        i++;
                    }
                    Pokemon tempPok;
                    char choice;
                    bool validChoice = false;
                    while(validChoice == false) { // until the user gives a valid response
                        string stringChoice;
                        cin >> stringChoice;
                        choice = stringChoice[0];
                        switch(choice) {
                        case '1' : // if they chose the first pokemon displayed (the pokemon in position 1): 
                            userParty[0] = tempPok; 
                            userParty[0] = userParty[1]; // switch the current active pokemon with the desired pokemon
                            userParty[1] = tempPok;
                            validChoice = true; // the user has made a valid choise
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                            break;
                        case '2' : // if they chose the second pokemon displayed (the pokemon in position 2): 
                            if(userParty.size()-faintedCounter > 2) { // and there exists a pokemon in position 2: 
                                userParty[0] = tempPok;
                                userParty[0] = userParty[2]; // switch the current active pokemon with the desired pokemon
                                userParty[2] = tempPok;
                                validChoice = true; // the user has made a valid choice
                                cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                                cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                            }
                            else { // otherwise there isn't a second pokemon
                                cout << "Invalid option, please enter a different number. " << endl; 
                            }
                            break;
                        case '3' : // if they chose the third pokemon displayed (the pokemon in position 3):
                            if(userParty.size()-faintedCounter > 3) { // and there exists a pokemon in position 3:
                                userParty[0] = tempPok;
                                userParty[0] = userParty[3]; // switch the current active pokemon with the desired pokemon
                                userParty[3] = tempPok;
                                validChoice = true; // the user has made a valid choice
                                cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                                cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                            }
                            else { // otherwise there isn't a third option
                                cout << "Invalid option, please enter a different number. " << endl;
                            }
                            break;
                        case '4' : // if they chose the fourth pokemon displayed (the pokemon in position 4):
                            if(userParty.size()-faintedCounter > 4) { // and there exists a pokemon in position 4:
                                userParty[0] = tempPok;
                                userParty[0] = userParty[4]; // switch the current active pokemon with the desired pokemon
                                userParty[4] = tempPok;
                                validChoice = true; // the user has made a valid choice
                                cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                                cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                            }
                            else { // otherwise there isn't a fourth option
                                cout << "Invalid option, please enter a different number. " << endl;
                            }
                            break;
                        case '5' : // if the chose the fifth pokemon displayed (the pokemon in position 5):
                            if(userParty.size()-faintedCounter > 5) { // and there axists a pokemon in position 5:
                                userParty[0] = tempPok;
                                userParty[0] = userParty[5]; // switch the current active pokemon with the desired pokemon
                                userParty[5] = tempPok;
                                validChoice = true; // the user has made a valid choice
                                cout << "Your ACTIVE Pokemon is: " << endl; // display the new active pokemon stats
                                cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << " A: " << userParty[0].getAttack() << " D: " << userParty[0].getDefense() << " S: " << userParty[0].getSpeed() << " M: " << userParty[0].getMaxStats() << endl;
                            }
                            else { // otherwise there isn't a fifth option
                                cout << "Invalid option, please enter a different number. " << endl;
                            }
                            break;
                        default : // a valid number (1-5) wasn't given
                            cout << "Please enter one of the numbers given. " << endl;
                            break;
                        }
                    }
                    trainers[15].setPartyPokemon(userParty); // update the user's party pokemon
                }
                validChoice = false; // it is a valid choice, but it basically just needs to run until the user chooses 1 or 3
                break;
            }
            default : // the user has not made a valid choice
                cout << "Please choose a valid option (1 or 2)" << endl;
                validChoice = false;
                break;
        }
    }
}

/** turn() - displays the menu of options for each turn
 *  1. Check is there is a pokemon near by (run that function first, then continue)
 *  2. Check if position of user is on a gym or a pokemon center (if yes, run those functions instead)
 *  3. Display the menu of options (rest, move, try your luck, quit).
 *  4. Runs those functions based on the given option
 *  5. If the given option is invalid, tell the user to try again and re-display the menu
*/

void Game::turn() {
    // running what happens each turn
    char choice = '0'; // initialize the choice at 0
    bool won = false;
    int pokemonCaught = 0;
    while(choice != '4') { // while the choice is not 4, (as in the user wants to quit)
        int row = trainers[15].getTrainerRow();
        int column = trainers[15].getTrainerColumn();
        int pokeFound = Game::checkIfPokemon();
        if(pokeFound != -1) { // if a pokemon has been found
            if(pokemonCaught < 2) { // if it is the first 2 pokemon
                Game::catchPokemon(pokeFound); // catch pokemon automatically
                pokemonCaught++; // increase the number of pokemon caught automatically
            }
            else { // if not first 2 pokemon
                // battle function
                Game::pokemonBattle(pokeFound);
            }
        }
        int gymFound = Game::checkIfGym(); // check if there is a gym at the user's current position
        if(gymFound != -1) { // if a gym has been found
            if(trainers[gymFound].ifDefeated() == false) { // and the gym is not already defeated
                Game::trainerBattle(gymFound); // battle with trainer
            }
            else { // else the gym has already been defeated
                cout << "You have arrived at Trainer " << trainers[gymFound].getUsername() << "'s Gym, but you have already defeated them!" << endl;
            }
        }
        bool centerFound = Game::checkIfCenter(); // check if there is a pokemon center at the user's current position
        if(centerFound == true) { // if yes
            bool change = Game::pokemonCenter(); // run the pokemon center function, if they want to change their active pokemon
            if(change == true) {
                Game::switchPokemonSuite(); // run the switch pokemon suite function
            }
        }
        vector<Pokemon> userParty = trainers[15].getPartyPokemon();
        cout << endl; // display the stats of the active pokemon
        cout << "The sun is shining, " << trainers[15].getUsername() << "! It's a beautiful day, we have " << trainers[15].getPokeballs() << " pokeballs left and your Pokemon are strong." << endl;
        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getHealth() << "/" << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
        for(int i=1; i<userParty.size(); i++) { // go through all the other pokemon and display their stats
            cout << "Name: " << userParty[i].getPokemonName() << ", HP: " << userParty[i].getHealth() << "/" << userParty[i].getMaxHealth() << ", A: " << userParty[i].getAttack() << ", D: " << userParty[i].getDefense() << ", S: " << userParty[i].getSpeed() << ", M: " << userParty[i].getMaxStats() << endl;
        }
        Game::displayMap(row, column); // display the map
        cout << "Please choose from the following options: " << endl; // display the turn options
        cout << "1. Travel" << endl;
        cout << "2. Rest" << endl;
        cout << "3. Try your luck" << endl;
        cout << "4. Quit the game" << endl;
        string turnChoice;
        cin >> turnChoice;
        choice = turnChoice[0];
        switch (choice) {
            case '1' : {// user travels
                cout << "What direction would you like to move? ('w': north, 'a': west, 's': south, 'd': east)" << endl;
                char direction;
                string stringDirection;
                cin >> stringDirection;
                direction = stringDirection[0]; // take the first position of the string given (to prevent user error)
                Game::travel(direction); // move in the direction the user indicated
                // random events:
                Game::pokemonFound();
                Game::treasureFound();
                Game::pokemonDeath();
                // check if the user is winning:
                Game::checkNumTypes();
                trainers[15].checkIfWinning();
                if(trainers[15].checkIfWinning() == true && won == false) { // if they haven't won yet
                    int x = Game::userWinning(); // prompt the user to see if they want to continue playing after winning
                    if(x == 0) { // if no
                        Game::quit(); // quit
                        choice = '4';
                    }
                    else if(x == 1) { // if yes
                        won = true; // mark them as having won
                    }
                }
                break;
            }
            case '2' : // user rests
                Game::rest(); 
                // random events: 
                Game::pokemonFound();
                Game::treasureFound();
                Game::pokemonDeath();
                // check if the user is winning:
                Game::checkNumTypes();
                trainers[15].checkIfWinning();
                if(trainers[15].checkIfWinning() == true && won == false) { // if they haven't won yet
                    Game::userWinning(); // prompt the user to see if they want to continue playing after winning
                    if(Game::userWinning() == 0) { // if no
                        Game::quit(); // quit
                        choice = '4';
                    }
                    else if(Game::userWinning() == 1) { // if yes
                        won = true; // mark them as having won
                    }
                }
                break;
            case '3' : // try your luck
                Game::tryYourLuck();
                // random events:
                Game::pokemonFound();
                Game::treasureFound();
                Game::pokemonDeath();
                // check if the user is winning:
                Game::checkNumTypes();
                trainers[15].checkIfWinning();
                if(trainers[15].checkIfWinning() == true && won == false) { // if they haven't won yet
                    int x = Game::userWinning(); // prompt to see if they want to continue playing after winning
                    if(x == 0) { // if no 
                        Game::quit(); // quit 
                        choice = '4';
                    }
                    else if(x == 1) { // if yes
                        won = true; // mark them as having won
                    }
                }
                break;
            case '4' : { // quit
                bool ifQuit = Game::quit();
                if (ifQuit == false) { // if the user doesn't actually want to quit:
                    choice = '0'; // reset the choice option
                }
                break;
            }
            default : // if the user has not chosen 1,2,3, or 4
                cout << "Please choose a valid option. (1, 2, 3, or 4)" << endl;
                break;
        }
    }
}

/** catchPokemon(int index) - catches the wild pokemon and puts it in the party or the pokedex
 * Add Points and decrease pokeballs
 * Move the pokemon into the party if there is room
 * If not, ask the user if they want to add the pokemon to their party
 * If yes, ask which pokemon they should replace
 * Depending on their choice, put the pokemon they just caught in the pokedex, or the pokemon they replace in the pokedex
*/

void Game::catchPokemon(int index) { // for catching wild Pokemon
    int currentPokeballs = trainers[15].getPokeballs();
    trainers[15].setPokeballs(currentPokeballs -1); // decrease the number of pokeballs
    trainers[15].addPoints(10); // add 10 points 
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon();
    if(currentPokeballs == 0) { // if the user is out of pokeballs:
        cout << "Oh no! You are out of Pokeballs! " << wildPokemon[index].getPokemonName() << " has been released back into the wild!" << endl;
        trainers[15].setPokeballs(0);
    }
    else if(userParty.size() < 6) { // if the user has room in their party
        wildPokemon[index].healPokemon(); // heal the pokemon
        cout << "Awesome! " << wildPokemon[index].getPokemonName() << " joins the Party!" << endl;
        userParty.push_back(wildPokemon[index]); // add it to the party
        wildPokemon.erase(wildPokemon.begin() + index); // remove it from the wild pokemon vector
        trainers[15].setPartyPokemon(userParty); // update the user's party
    }
    else if(userParty.size() == 6) { // if the user doesn't have room in their party
        wildPokemon[index].healPokemon(); // heal pokemon
        cout << "Awesome! " << wildPokemon[index].getPokemonName() << " joins the Pokedex! Your battle party is full. Do you want to add " << wildPokemon[index].getPokemonName() << "to your active party? (Y/N)" << endl;
        char choice; // ask the user if they want to add the new pokemon into their active party
        bool validChoice = false;
        while(validChoice == false) { // until user has given a valid answer
            string stringChoice;
            cin >> stringChoice;
            choice = stringChoice[0];
            switch(choice) {
                case 'Y' : { // if they want the new pokemon in their active party
                    cout << "Which Pokemon should not be part of the Active Party anymore? " << endl;
                    for(int i=0; i<userParty.size(); i++) { // display the pokemon in their party now
                        cout << i+1 << ". " << userParty[i].getPokemonName() << endl;
                    }
                    char secondChoice;
                    bool validSecondChoice = false;
                    Pokemon tempPok;
                    while(validSecondChoice == false) {
                        string stringSecondChoice;
                        cin >> stringSecondChoice;
                        secondChoice = stringSecondChoice[0];
                        switch(secondChoice) {
                            case '1' : // if the first pokemon displayed is chosen
                                cout << wildPokemon[index].getPokemonName() << " has been added to your Party and is now your Active Pokemon!" << endl;
                                // replace the pokemon in the active party:
                                tempPok = userParty[0];
                                userParty[0] = wildPokemon[index];
                                wildPokemon[index] = tempPok;
                                userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon
                                trainers[15].setPartyPokemon(userParty); // update the party
                                validSecondChoice = true; // the user has made a valid choice
                                break;
                            case '2' : // if the second pokemon displayed is chosen
                                if(userParty.size() >= 2) { // if the party has at least 2 pokemon:
                                    cout << wildPokemon[index].getPokemonName() << " has been added to your Party and " <<  userParty[1].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                    // replace the pokemon in the active party:
                                    tempPok = userParty[1];
                                    userParty[1] = wildPokemon[index];
                                    wildPokemon[index] = tempPok;
                                    userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                    wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon 
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    validSecondChoice = true; // the user has made a valid choice
                                }
                                else { // 2nd pokemon is not available
                                    cout << "Please enter a valid number." << endl;
                                    validSecondChoice = false; // the user has not made a valid choice
                                }
                                break;
                            case '3' : // if the third pokemon dispplayed is chosen
                                if(userParty.size() >= 3) { // if the party has at least 3 pokemon: 
                                    cout << wildPokemon[index].getPokemonName() << " has been added to your Party and " <<  userParty[2].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                    // replace the pokemon in the active party
                                    tempPok = userParty[2];
                                    userParty[2] = wildPokemon[index];
                                    wildPokemon[index] = tempPok;
                                    userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                    wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    validSecondChoice = true; // the user has made a valid choice
                                }
                                else { // 3rd pokemon is not available
                                    cout << "Please enter a valid number." << endl;
                                    validSecondChoice = false; // the user has not made a valid choice
                                }
                                break;
                            case '4' : // if the fourth pokemon displayed is chosen
                                if(userParty.size() >= 4) { // if the party has at least 4 pokemon:
                                    cout << wildPokemon[index].getPokemonName() << " has been added to your Party and " <<  userParty[3].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                    // replace the pokemon in the active party
                                    tempPok = userParty[3];
                                    userParty[3] = wildPokemon[index];
                                    wildPokemon[index] = tempPok;
                                    userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                    wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    validSecondChoice = true; // the user has made a valid choice
                                }
                                else { // the 4th pokemon the not available
                                    cout << "Please enter a valid number." << endl;
                                    validSecondChoice = false; // the user has not made a valid choice
                                }
                                break;
                            case '5' :  // if the fifth pokemon displayed is chosen
                                if(userParty.size() >= 5) { // if the party has at least 5 pokemon: 
                                    cout << wildPokemon[index].getPokemonName() << " has been added to your Party and " <<  userParty[4].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                    // replace the pokemon in the active party
                                    tempPok = userParty[4];
                                    userParty[4] = wildPokemon[index];
                                    wildPokemon[index] = tempPok;
                                    userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                    wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    validSecondChoice = true; // the user has made a valid choice
                                }
                                else {  // the 5th pokemon is not available
                                    cout << "Please enter a valid number." << endl;
                                    validSecondChoice = false;
                                }
                                break;
                            case '6' : // if the sixth pokemon displayed is chosen
                                if(userParty.size() >= 6) { // if the party has at least 6 pokemon:
                                    cout << wildPokemon[index].getPokemonName() << " has been added to your Party and " <<  userParty[5].getPokemonName() << " has been moved to your Pokedex!" << endl;
                                    // replace the pokemon in the active party
                                    tempPok = userParty[5];
                                    userParty[5] = wildPokemon[index];
                                    wildPokemon[index] = tempPok;
                                    userPokedex.push_back(wildPokemon[index]); // add the replaced pokemon in the pokedex
                                    wildPokemon.erase(wildPokemon.begin() + index); // remove the wild pokemon
                                    trainers[15].setPartyPokemon(userParty); // update the party
                                    validSecondChoice = true; // the user has made a valid choice
                                }
                                else { // the 6th pokemon is not available
                                    cout << "Please enter a valid number." << endl;
                                    validSecondChoice = false;
                                }
                                break;
                            default : // invalid choice
                                cout << "Please choose a valid number." << endl;
                                validSecondChoice = false;
                                break;
                        }
                    }
                    validChoice = true; // yes was a valid choice
                    break;
                }
                case 'N' : { // the pokemon stays in the pokedex
                    cout << wildPokemon[index].getPokemonName() << " shall stay in the Pokedex! Visit a Pokemon Center to change your Pokemon Party!" << endl;
                    userPokedex.push_back(wildPokemon[index]); // put the pokemon in the pokedex
                    wildPokemon.erase(wildPokemon.begin() + index); // remove the pokemon from the wild pokemon
                    trainers[15].setPokedexPokemon(userPokedex); // update the user's pokedex
                    validChoice = true; // the user has made a valid choice
                    break;
                }
                default : {
                    cout << "Please choose a valid option. Do you want to add " << wildPokemon[index].getPokemonName() << " to your Active Party? (Y/N)" << endl;
                    validChoice = false;
                    break;
                }
            }
        }
    }
}

/** rest() - don't change the position of the user, increase the pokemon health by one, decrease the number of pokeballs by one */

void Game::rest() {
    if(trainers[15].getPokeballs() < 1) {
        cout << "You cannot rest! You have no Pokeballs!" << endl;
    }
    else {
        // decrease pokeballs:
        trainers[15].setPokeballs(trainers[15].getPokeballs() - 1);
        // heal each pokemon is the party:
        vector<Pokemon> userParty = trainers[15].getPartyPokemon();
        for(int i=0; i<userParty.size(); i++) { // for each pokemon in the user's party
            int currentHealth = userParty[i].getHealth(); // get their health
            if(currentHealth < userParty[i].getMaxHealth()) { // if the pokemon is not already at max health
                userParty[i].setHealth(currentHealth + 1); // add 1 to their health
            }
        }
        trainers[15].setPartyPokemon(userParty); // update the user's party
    }
}

/** travel(char move) - moves the user based on desired movement
 *  1. If the character gives either a 'w', 'a', 's', or 'd', move in that corresponding direction (if it isn't a water tile)
 *  2. If the input is invalid, cout "Enter a different key".
 *  3. The function will return -2 if the tile is water. (if the travel function catches it)
 *  4. The function will return -1 if it is the end of the map. (if the move function catches it)
 *  5. The function will return 0 if the move was successful. (if it passes through the move function successfully)
*/

int Game::travel(char move) { // make it so the user cannot go on a water tile, then do the actual move 
    int row = trainers[15].getTrainerRow();
    int column = trainers[15].getTrainerColumn();
    if(move == 'w' || move == 'W') {
        if(map[row-1][column].ifWater() == true) { // if the position the user is trying to move to is a water tile: 
            cout << "You cannot move onto a water tile. Please try a different direction." << endl;
        }
        else { // if the tile is not a water tile, run the move function 
            trainers[15].moveUser(move);
        }
    } 
    else if(move == 's' || move == 'S') {
        if(map[row+1][column].ifWater() == true) { // if the position the user is trying to move to is a water tile: 
            cout << "You cannot move onto a water tile. Please try a different direction." << endl;
            return -2;
        }
        else { // if the tile is not a water tile, run the move function
            return trainers[15].moveUser(move);
        }
    } 
    else if(move == 'a' || move == 'A') {
        if(map[row][column-1].ifWater() == true) { // if the position the user is trying to move to is a water tile: 
            cout << "You cannot move onto a water tile. Please try a different direction." << endl;
            return -2;
        }
        else { // if the tile is not a water tile, run the move function
            return trainers[15].moveUser(move);
        }
    } 
    else if(move == 'd' || move == 'D') {
        if(map[row][column+1].ifWater() == true) { // if the position the user is trying to move to is a water tile: 
            cout << "You cannot move onto a water tile. Please try a different direction." << endl;
            return -2;
        }
        else { // if the tile is not a water tile, run the move function
            return trainers[15].moveUser(move);
        }
    } 
    else { // if the move wasn't w,a,s,d the move function will catch it and return -1
       return trainers[15].moveUser(move);
    }
} 

/** tryYourLuck() - random number decides if a pokemon is caught for free, position unchanged 
 *  1. Go through the vector of wild pokemon. If a pokemon is found within the 7x7 area:
 *  2. Generate a random number between 1 and 100, if that number is greater than 50, the user catches the pokemon.
 *  3. If the user's party is not full, add that pokemon to the user's party.
 *  4. If the user's party is full, add that pokemon to the user's pokedex.
*/

void Game::tryYourLuck() {
    // based on the locations of the wild pokemon, if there is a pokemon in the 7x7 grid, 50% to catch it for free.
    int row = trainers[15].getTrainerRow();
    int column = trainers[15].getTrainerColumn();
    srand(time(nullptr));
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon();
    bool pokemonFound = false;
    for(int i=0; i<wildPokemon.size(); i++) { // go through each wild pokemon. 
        if(wildPokemon[i].getPokemonRow() >= row-3 && wildPokemon[i].getPokemonRow() <= row+3 && wildPokemon[i].getPokemonColumn() >= column-3 && wildPokemon[i].getPokemonColumn() <= column+3 && pokemonFound == false) {
            // if there is a pokemon found in that 7x7 area.
            int chance = rand()%100 +1; // random number between 1 and 100
            if(chance >= 50) { // if the user does catch the pokemon:
                if(userParty.size() < 6) { // if there is room in the user's party, add that pokemon to the party
                    cout << "A wild " << wildPokemon[i].getPokemonName() << " has appeared and been added to your party!" << endl;
                    userParty.push_back(wildPokemon[i]); // add the pokemon to the party
                    wildPokemon.erase(wildPokemon.begin() + i); // remove that pokemon from the wild pokemon vector
                    i = i-1;
                    trainers[15].setPartyPokemon(userParty); // update the party vector
                }
                else { // if not room, add the pokemon to the pokedex
                    cout << "A wild " << wildPokemon[i].getPokemonName() << " has appeared and been added to your Pokedex!" << endl;
                    userPokedex.push_back(wildPokemon[i]); // add the pokemon to the pokedex
                    wildPokemon.erase(wildPokemon.begin() + i); // remove that pokemon from the wild pokemon vector
                    i = i-1;
                    trainers[15].setPokedexPokemon(userParty); // update the pokedex vector
                }
            }
            pokemonFound = true;
        } 
    }
}

/** quit() - end the game, write the scores to a file, say goodbye */

bool Game::quit() {
    cout << "Are you sure you want to quit? (Y/N)" << endl;
    bool validChoice = false;
    string choice;
    while(validChoice == false) {
        cin >> choice;
        if(choice[0] == 'Y') { // if yes the user wants to quit
            Game::endOfGame(); // run the end of game function and return true
            validChoice = true;
            return true;
        }
        else if (choice[0] == 'N') { // if no the user wants to continue playing
            validChoice = true; 
            return false; // return false
        }
        else {
            cout << "Invalid choice. Please choose either Y or N." << endl;
        }
    }
}

/** movePokemon() - randomly moves all of the wild pokemon around the map
 *  1. Go through each wild pokemon, and use a random number function to determine the direction the pokemon will go. 
 *      a. If the given position is water, a gym, a pokecenter, or already ocuppied, move in a different direction.
 *  2. Once the pokemon has been sucessfully moved, change that position bool to occupied. Then start over with the next pokemon in the vector
*/

void Game::movePokemon() {
    srand(time(nullptr));
    for(int i=0; i<wildPokemon.size(); i++) { // going through each pokemon in the wild pokemon vector
        int row = wildPokemon[i].getPokemonRow();
        int column = wildPokemon[i].getPokemonColumn();
        bool moved = false;
        while(moved == false) {
            int value = rand()%4 +1; // value is between 1 and 4
            switch (value) {
                case 1 :  { // move up
                    if(map[row-1][column].ifOccupied() == false && map[row-1][column].ifEndOfMap() == false && map[row-1][column].getTile() == '*') { // if it is not the end of the map or already occupied
                        map[row-1][column].setOccupied(true); // marking new position as occupied
                        map[row][column].setOccupied(false); // marking old position as not occupied
                        wildPokemon[i].setPokemonRow(row-1); // setting new position
                        moved = true; // the pokemon has moved successfully
                    }
                    break;
                }
                case 2 : { // move down
                    if(map[row+1][column].ifOccupied() == false && map[row+1][column].ifEndOfMap() == false && map[row+1][column].getTile() == '*') { // if it is not the end of the map or already occupied
                        map[row+1][column].setOccupied(true); // marking new position as occupied
                        map[row][column].setOccupied(false); // marking old position as not occupied
                        wildPokemon[i].setPokemonRow(row+1); // setting new position
                        moved = true; // the pokemon has moved successfully
                    }
                    break;
                }
                case 3 :  { // move left
                    if(map[row][column-1].ifOccupied() == false && map[row][column-1].ifEndOfMap() == false && map[row][column-1].getTile() == '*') { // if it is not the end of the map or already occupied
                        map[row][column-1].setOccupied(true); // marking new position as occupied
                        map[row][column].setOccupied(false); // marking old position as not occupied
                        wildPokemon[i].setPokemonColumn(column-1); // setting new position
                        moved = true; // the pokemon has moved successfully
                    }
                    break;
                }
                case 4 : { // move right
                    if(map[row][column+1].ifOccupied() == false && map[row][column+1].ifEndOfMap() == false && map[row][column+1].getTile() == '*') { // if it is not the end of the map or already occupied
                        map[row][column+1].setOccupied(true); // marking new position as occupied
                        map[row][column].setOccupied(false); // marking old position as not occupied
                        wildPokemon[i].setPokemonColumn(column+1); // setting new position
                        moved = true; // the pokemon has moved successfully
                    }
                    break;
                }
                default : { // if the random number generator for some reason gives a value that is none of the above, nothing happens.
                    break;
                }
            }
        }
    }
}

/** checkIfPokemon() - checks in the 3x3 area around the user for pokemon to catch, and returns the index of the nearest pokemon
 *  1. Looking through the wild pokemon vector, if there is a pokemon within the 5x5 area around the user: return the index of the nearest pokemon
 *  2. If no wild pokemon were found: return -1 
*/

int Game::checkIfPokemon() {
    int row = trainers[15].getTrainerRow(); // save the row and column values
    int column = trainers[15].getTrainerColumn();
    for(int i=0; i<wildPokemon.size(); i++) { // go through each position of the wild pokemon vector
        if(wildPokemon[i].getPokemonRow() >= row-2 && wildPokemon[i].getPokemonRow() <= row+2 && wildPokemon[i].getPokemonColumn() >= column-2 && wildPokemon[i].getPokemonColumn() <= column+2) {
            // if a pokemon is found: return the index of that pokemon
            return i;
        }
    }
    // if no pokemon were found in that area:
    return -1;
}

/** checkIfGym() - checks if the position of the user is at a gym 
 *  1. Take position of user, and use the Map member function ifGym.
 *  2. Return that value.
*/

int Game::checkIfGym() {
    int row = trainers[15].getTrainerRow(); // save the row and column values
    int column = trainers[15].getTrainerColumn();
    bool gymFound = map[row][column].ifGym(); // use the function to return if there is a gym at the trainer's location or not.
    if(gymFound == true) {
        for(int i=0; i<15; i++) { // go through each trainer
            if(trainers[i].getTrainerRow() == trainers[15].getTrainerRow() && trainers[i].getTrainerColumn() == trainers[15].getTrainerColumn()) {
                // if the trainer's positions are the same as the user's current position:
                return i; // return the index of the trainer at that gym
            }
        }
    }
    else { // if no gym trainer was found at the user's current positions:
        return -1; // return -1
    }
}

/** checkIfCenter() - checks if the position of the user is at a pokecenter
 *  1. take the position of the user, and use the Map member function ifPokeCenter.
 *  2. Return that value.
*/

bool Game::checkIfCenter() {
    int row = trainers[15].getTrainerRow(); // save the row and column values
    int column = trainers[15].getTrainerColumn();
    bool centerFound = map[row][column].ifPokeCenter(); // use the function to return if there is a pokecenter at the trainer's location or not.
    return centerFound; // return either true or false
}

/** nearestPokemonCenter() - find the nearest pokemon center to the user
 * go through each position and find the nearest pokemon center
 * update the user's postion
*/ 

void Game::nearestPokemonCenter(int r, int c) {
    // for(int i=0; i<16; i++) {
    //     // go through the positions, first 1 block away, then 2 blocks away, then 3 blocks away
    //     // then once a center is found, set the user's position to the position of the pokemon center found
    // }
    if(r >= 1 && r <= 4) {  // if the user's row is between 1-4, the nearest Pokemon Center is 2,11
        trainers[15].setTrainerRow(2); // set the user positions at the center
        trainers[15].setTrainerColumn(11);
    }
    else if(r >= 5 && r <=8 && c >= 1 && c <=5) { // if the user's row is 5-8 and column is 1-5, the nearest Pokemon Center is 6,2
        trainers[15].setTrainerRow(6); // set the user positions at the center
        trainers[15].setTrainerColumn(2);
    }
    else if(r >= 5 && r <= 8 && c >= 6 && c <=16) { // if the user's row is 5-8 and column is 6-16, the nearest Pokemon Center is 6,9
        trainers[15].setTrainerRow(6); // set the user positions at the center
        trainers[15].setTrainerColumn(9);
    }
    else if(r>=9 && r<=11) { // if the user's row is 9-11, the nearest Pokemon Center is 10,12
        trainers[15].setTrainerRow(10); // set the user positions at the center
        trainers[15].setTrainerColumn(12);
    } 
    else if(r>=12 && r<=16) { // if the user's row is 12-16, the neareast Pokemon Center is 14,10
        trainers[15].setTrainerRow(14); // set the user positions at the center
        trainers[15].setTrainerColumn(10);
    }
    else if(r>=22 && r<=25) { // if the user's row is 22-25, the nearest Pokemon Center is 24,8
        trainers[15].setTrainerRow(24); // set the user positions at the center
        trainers[15].setTrainerColumn(8);
    }
    else { // edge case, set the position to the Center at the middle of the map
        trainers[15].setTrainerRow(12);
        trainers[15].setTrainerColumn(10);
    }
}

/** pokemonCenter() - offers the user to switch pokemon and heals all pokemon 
 *  1. Go through all the pokemon in the user's party and use the heal member function to heal them.
 *  2. Output the saying for the Pokemon Center, telling the user their pokemon have been healed, and asking if they want to change the members of their party.
 *  3. Based on their decision, return different numbers:
 *      a. Returns 1 if the user wants to switch the pokemon in their Party.
 *      b. Returns 0 if the user doesn't want to switch the pokemon in their party.
*/

int Game::pokemonCenter() {
    vector<Pokemon> userParty = trainers[15].getPartyPokemon(); // save the user's party
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon(); // save the user's pokedex
    for(int i=0; i<userParty.size(); i++) { // go through and heal the user's party pokemon
        userParty[i].healPokemon();
        userParty[i].setFainted(false);
    }
    trainers[15].setPartyPokemon(userParty);
    // prompt the user if they would like the change the pokemon in their party:
    cout << endl;
    cout << "Welcome to the Pokemon Center. All Pokemon in your party have been healed. Do you want to change the members of your party? (Y/N):" << endl;
    bool validChoice = false;
    char choice;
    while(validChoice == false) { // ask until the user gives a valid input
        string stringChoice;
        cin >> stringChoice;
        choice = stringChoice[0];
        switch(choice) {
            case 'Y' : // if the user says yes
                return 1; 
                break;
            case 'N' : // if the user says no
                return 0;
                break;
            default : // if the user gives an invalid input
                cout << "Please choose either 'Y' or 'N'." << endl;
                break;
        }
    }
}

/** switchPokemonSuite() - prompts user to switch their active pokemon suite 
 *  1. Move the pokemon from the user's party into the user's pokedex and clear the user's party.
 *  2. Display all of the pokemon in the user's pokedex currently (including the ones from the party).
 *  3. Ask the user to choose at most 6 Pokemon to add to their party, until they have made all valid choices.
 *  4. Split the input from the user based on spaces.
 *  5. Check to make the user has not given any letters for the input (as that would cause an error when using stoi)
 *  6. Then convert each number given to an integer. This - 1 becomes the index of the pokemon.
 *  7. Check if the index is a valid index for the pokemon (so that the user doesn't try to take a pokemon from position 300 or anything)
 *  8. If everything goes smoothly, copy the pokemon from the pokedex index given by the user, into the user's party vector.
 *  9. If the user input a letter or an incorrect number, output a statement saying so.
 *  10. Otherwise, output the list of pokemon that has been added to the user's party vector.
 *  11. Prompt the user to choose an active pokemon.
 *  12. If the input is valid, switch that pokemon with the first pokemon in the vector (as that is the active pokemon).
 *  13. Ask until the user gives a valid input.
 *  14. Then replace the user's party with the one they just created.
 *  15. Remove the pokemon in the pokedex vector that were added to the party vector.
 *  16. Then replace the user's pokedex with the one they just created.
*/

int Game::switchPokemonSuite() {
    // display current active pokemon and the pokemon in the pokedex
    // prompts user to choose up to 6 active pokemon
    // once the active pokemon have been chosen, display the new suite
    
    cout << "Here are all the Pokemon in your Pokedex. Choose at most 6 numbers, separated by spaces, then press enter once complete. " << endl;
    vector<Pokemon> userParty = trainers[15].getPartyPokemon(); // save the user's party pokemon
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon(); // save the user's pokedex pokemon
    for(int i=0; i<userParty.size(); i++) { // move the user's party pokemon to the pokedex
        userPokedex.push_back(userParty[i]); // add that pokemon to the end of the pokedex
    }
    userParty.clear(); // clear the user's party pokemon vector
    for(int i=0; i<userPokedex.size(); i++) { // display each pokemon in the pokedex vector
        cout << i+1 << ". " << userPokedex[i].getPokemonName() << endl;
    }
    bool validInput = false;
    bool letters = false;
    bool indexValid = true;
    vector<int> indexes; // the indexes of the pokedex pokemon that were moved to the party (and need to be removed from the pokedex)
    int erasedCounter = 0;
    while(validInput == false && indexValid == true || letters == true) { // until the user gives a valid input for which pokemon to include in their party 
        letters = false;
        userParty = trainers[15].getPartyPokemon();
        userParty.clear(); // clear the party again (in case the user gave invalid inputs)
        string line;
        string pok[6];
        cin.ignore();
        getline(cin, line); // get the line given by the user
        split(line, ' ', pok, 6); // split it with a space as the deliminator
        int i = 0;
        while(pok[i]!="" && i<6) { // go through the first 6 numbers given in the line and if the string of given numbers is not empty (they gave a number for the pokemon at that position)
            string str = pok[i];
            for(int j=0; j<str.length(); j++) { // making sure the user only gave numbers and no letters (as that would break the stoi)
                if(str[j] < '0' || str[j] > '9') {
                    letters = true; // if the given string (should be just numbers for which pokemon to include in the party vector) includes letters, stop (will break the stoi used in the next step)
                }
            }
            if(letters == false) { // if the string does not contain letters:
                int index = stoi(pok[i])-1; // convert the string to an integer as the index of the pokemon (-1 since it started at 1 and should start at 0)
                if(index+1 > userPokedex.size()+1) { // if the index is outside the userPokedex vector
                    indexValid = false; // not a valid response
                }
                else { // if the index is a valid index: move the pokemon
                    userParty.push_back(userPokedex[index]); // add that pokemon to the party vector
                    trainers[15].setPartyPokemon(userParty);
                    indexes.push_back(index); // add the index of the pokemon within the pokedex that was just added to the party
                    validInput = true;
                }
            }
            i++;
        }
        if(letters == true) { // if there were letters included in the input
            cout << "Please only enter the numbers given." << endl;
        }
        else if(indexValid == false) { // if one of the numbers gave an invalid index, tell the user to try again.
            cout << "One or more of the numbers given is not a valid option. Please enter the numbers again. " << endl;
        }
        else if(validInput == true) { // if everything is good:
            cout << "You have chosen the " << userParty.size() << " Pokemon below. Please choose which one should be the ACTIVE Pokemon. " << endl;
            for(int i=0; i<userParty.size(); i++) { // display the pokemon that have been added to the party
                cout << i+1 << ". " << userParty[i].getPokemonName() << endl;
            }
            char activeChoice;
            bool validActiveChoice = false;
            Pokemon tempPoke;
            while(validActiveChoice == false) { // until the user has made a valid choice for which active pokemon to choose
                string stringActiveChoice;
                cin >> stringActiveChoice; // get choice from user
                activeChoice = stringActiveChoice[0];
                switch(activeChoice) {
                    case '1' : // if the first pokemon displayed is chosen:
                        validActiveChoice = true; // that pokemon is already in the location of the active pokemon (the first position)
                        cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                        cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                        trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        break;
                    case '2' : // if the second pokemon displayed is chosen:
                        if(userParty.size() >= 2) { // and the userParty has a pokemon at that position
                            tempPoke = userParty[0]; // switch the pokemon in the first position with the pokemon in the second position (making it the new active pokemon)
                            userParty[0] = userParty[1];
                            userParty[1] = tempPoke;
                            validActiveChoice = true; // the user has made a valid choice
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        }
                        else { // meaning the user does not have a pokemon in their party at the second position
                            cout << "Invalid option, please enter a different number." << endl;
                        }
                        break;
                    case '3' : // if the third pokemon displayed is chosen:
                        if(userParty.size() >= 3) { // and the userParty has a pokemon at that position
                            tempPoke = userParty[0]; // switch the pokemon in the first position with the pokemon in the third position (making it the new active pokemon)
                            userParty[0] = userParty[2];
                            userParty[2] = tempPoke;
                            validActiveChoice = true; // the user has made a valid choice
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        }
                        else {  // meaning the user does not have a pokemon in their party at the third position
                            cout << "Invalid option, please enter a different number." << endl;
                        }
                        break;
                    case '4' : // if the fourth pokemon displayed is chosen:
                        if(userParty.size() >= 4) { // and the userParty has a pokemon at that position
                            tempPoke = userParty[0]; // switch the pokemon in the first position with the pokemon in the fourth position (making it the new active pokemon)
                            userParty[0] = userParty[3];
                            userParty[3] = tempPoke;
                            validActiveChoice = true; // the user has made a valid choice
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        }
                        else { // meaning the user does not have a pokemon in their party at the fourth position
                            cout << "Invalid option, please enter a different number." << endl;
                        }
                        break;
                    case '5' : // if the fifth pokemon displayed is chosen:
                        if(userParty.size() >= 5) { // and the userParty has a pokemon at that position
                            tempPoke = userParty[0]; // switch the pokemon in the first position with the pokemon in the fifth position (making it the new active pokemon)
                            userParty[0] = userParty[4];
                            userParty[4] = tempPoke;
                            validActiveChoice = true; // the user has made a valid choice
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        }
                        else { // meaning the user does not have a pokemon in their party at the fifth position
                            cout << "Invalid option, please enter a different number." << endl;
                        }
                        break;
                    case '6' : // if the sixth pokemon displayed is chosen:
                        if(userParty.size() >= 6) { // and the userParty has a pokemon at that position
                            tempPoke = userParty[0]; // switch the pokemon in the first position with the pokemon in the sixth position (making it the new active pokemon)
                            userParty[0] = userParty[5];
                            userParty[5] = tempPoke;
                            validActiveChoice = true; // the user has made a valid choice
                            cout << "Your ACTIVE Pokemon is: " << endl; // display the stats of the new active pokemon
                            cout << "Name: " << userParty[0].getPokemonName() << " (ACTIVE), HP: " << userParty[0].getMaxHealth() << ", A: " << userParty[0].getAttack() << ", D: " << userParty[0].getDefense() << ", S: " << userParty[0].getSpeed() << ", M: " << userParty[0].getMaxStats() << endl;
                            trainers[15].setPartyPokemon(userParty); // replace the user's party with the one they have just created
                        }
                        else { // meaning the user does not have a pokemon in their party at the sixth position
                            cout << "Invalid option, please enter a different number." << endl;
                        }
                        break;
                    default : // if the user gave an invalid input (either a letter or a number outside of 1-6)
                        cout << "Please enter one of the numbers given. " << endl;
                        break;
                }
            }
        }
    }
    sort(indexes.begin(), indexes.end()); // organize the vector array of indexes for which pokemon got moved
    for(int j=indexes.size()-1; j>-1; j--) { // going back through the array, get rid of the pokemon within the pokedex that were added to the party (to prevent duplicates)
        userPokedex.erase(userPokedex.begin() + indexes[j]);
    }
    trainers[15].setPokedexPokemon(userPokedex); // once the pokemon have been moved, replace the user's pokedex with the one they just created
}

/** RANDOM EVENTS */
/** pokemonFound() - random number generator, if the number says yes: add pokemon to party for free 
 * If pokemon has been found:
 *  1. Prompt the user if they want to catch the pokemon, or release the pokemon.
 *  2. If they want to catch it (and have a pokeball to catch with), and if the party is empty add it to the party.If the party is full, add it to the pokedex
 *  3. If they want to catch it and don't have any pokeballs, tell them the pokemon ran away.
 *  4. If the user wants to release the pokemon, say the pokemon has been let back into the wild.
 * If a pokemon wasn't found:
 *  1. do nothing.

*/

void Game::pokemonFound() {
    srand(time(nullptr));
    int chance = rand()%100 +1;
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon();
    if(chance <= 30) { // if the chance is less than 30 (meaning a pokemon was found)
        int value = rand()%151; // random value between 0 and 150
        cout << "Suddenly, " << allPokemon[value].getPokemonName() << " appears in your path. Do you want to: " << endl;
        cout << "1. Catch it." << endl; // prompt the user to either catch it or release it.
        cout << "2. Release it." << endl;
        bool validChoice = false;
        char choice;
        while(validChoice == false) { // until the user makes a valid choice
            string stringChoice;
            cin >> stringChoice;
            choice = stringChoice[0];
            switch(choice) {
                case '1' : // if the user wants to catch the pokemon:
                    if(trainers[15].getPokeballs() > 0) { // and they have pokeballs
                        int currentPokeballs = trainers[15].getPokeballs();
                        trainers[15].setPokeballs(currentPokeballs - 1); // decrease pokeballs by 1
                        if(userParty.size() == 6) { // if the party is full:
                            cout << "Awesome! " << allPokemon[value].getPokemonName() << " joined the Pokedex!" << endl; // add the pokemon to the pokedex
                            userPokedex.push_back(allPokemon[value]);
                            trainers[15].setPokedexPokemon(userPokedex); // update the user's pokedex
                        }
                        else { // else the party has room:
                            cout << "Awesome! " << allPokemon[value].getPokemonName() << " joined the Party!" << endl; // add the pokemon to the party
                            userParty.push_back(allPokemon[value]);
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                        }
                    }
                    else { // else the user has no pokeballs
                        cout << "Oh no! You don't have enough Pokeballs! " << allPokemon[value].getPokemonName() << " has run away!" << endl;
                    }
                    validChoice = true; // the user has made a valid choice
                    break;
                case '2' : // the user wants to release the pokemon
                    cout << allPokemon[value].getPokemonName() << " has been released back into the wild!" << endl;
                    validChoice = true; // the user has made a valid choice
                    break;
                default : // the user has not made a valid choice
                    cout << "Please choose either 1 or 2." << endl;
                    break;
            }
        }
    }
}

/** treasureFound() - random number generator, if number says yes, user gets 20 pokeballs or level up berries 
 *  1. Generate a random number to figure out if a treasure was found or not.
 *  2. If a treasure was found, generate another random number to figure out what type of treasure was found. 
 *      a. If pokeballs have been found, add 2 pokeballs.
 *      b. If berries, ask the user which pokemon they want to give berries to to level up.
*/

void Game::treasureFound() {
    srand(time(nullptr));
    int chance = rand()%100 +1; // chance that a treasure was found, 1-100
    if(chance <= 25) { // if the chance is less than 25, meaning a treasure was found
        int value = rand()%100 +1; // generate another random value
        if(value <= 50) { // if the value is less than 50, pokeballs were found:
            int currentPokeballs = trainers[15].getPokeballs();
            trainers[15].setPokeballs(currentPokeballs + 2);
            cout << "Great news! You have stumbled upon a hidden stash of Pokeballs. Your reserves have increased to " << trainers[15].getPokeballs() << " Pokeballs." << endl;
        }
        else if (value > 50) { // if the value is greater than 50, beries were found:
            cout << "Great news! You have stumbled upon a hidden stash of Poffins! Your Pokemon are delighted! Choose one of them to feast on the Poffins and level up: " << endl;
            vector<Pokemon> userParty = trainers[15].getPartyPokemon();
            for(int i=0; i<userParty.size(); i++) { // display the user's party
                cout << i+1 << ". " << userParty[i].getPokemonName() << endl;
            }
            char choice;
            bool validChoice = false;
            while(validChoice == false) { // until the user has made a valid choice
                string stringChoice;
                cin >> stringChoice;
                choice = stringChoice[0];
                switch(choice) {
                    case '1' : // the first pokemon displayed
                        userParty[0].levelUp(); // level up
                        cout << userParty[0].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                        trainers[15].setPartyPokemon(userParty); // update the user's party
                        validChoice = true; // the user has made a valid choice
                        break;
                    case '2' : // the second pokemon displayed
                        if(userParty.size() >= 2) { // if the user's party has at least 2 pokemon
                            userParty[1].levelUp(); // level up
                            cout << userParty[1].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            validChoice = true; // the user has made a valid choice
                        }
                        else { // the party does not have a second pokemon
                            cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        }
                        break;
                    case '3' : // the third pokemon displayed
                        if(userParty.size() >= 3) { // if the user's party has at least 3 pokemon
                            userParty[2].levelUp(); // level up
                            cout << userParty[2].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            validChoice = true; // the user has made a valid choice
                        }
                        else { // the party does not have a third pokemon
                            cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        }
                        break;
                    case '4' : // the fourth pokemon displayed
                        if(userParty.size() >= 4) { // if the user's party has at least 4 pokemon
                            userParty[3].levelUp(); // level up
                            cout << userParty[3].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            validChoice = true; // the user has made a valid choice
                        }
                        else { // the party does not have a fourth pokemon
                            cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        }
                        break;
                    case '5' : // the fifth pokemon displayed
                        if(userParty.size() >= 5) { // if the user's party has at least 5 pokemon
                            userParty[4].levelUp(); // level up
                            cout << userParty[4].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            validChoice = true; // the user has made a valid choice
                        }
                        else { // the party does not have a fifth pokemon
                            cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        }
                        break;
                    case '6' : // the sixth pokemon displayed
                        if(userParty.size() >= 6) { // if the user's party has at least 6 pokemon 
                            userParty[5].levelUp(); // level up
                            cout << userParty[5].getPokemonName() << " ate the Poffins and leveled up!" << endl;
                            trainers[15].setPartyPokemon(userParty); // update the user's party
                            validChoice = true; // the user has made a valid choice 
                        }
                        else { // the party does not have a sixth pokemon
                            cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        }
                        break;
                    default : // the user has not made a valid choice
                        cout << "Please choose a valid number for which Pokemon gets to feast." << endl;
                        break;
                }
            }
        }
    }
}

/** pokemonDeath() - random number generator, if number says yes, another random number generator, pokemon dies
 *  1. Generate a random number to determine if a pokemon dies.
 *  2. If a pokemon does die, generate another random number to determine which pokemon in the party dies.
*/

void Game::pokemonDeath() {
    srand(time(nullptr));
    int chance = rand()%100 +1; // random number between 1 and 100
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    if(chance <= 20) { // if it is less than 20:
        int value; // get another random number between 0 and 5 for which pokemon is going to die
        if(userParty.size() == 2) { // if there are only 2 pokemon in the party
            value = rand()%1 +1; // generate a random number between 0 and 1
            cout << "Oh no! After years of legendary battles, " << userParty[value].getPokemonName() << " died of old age. Thank you for your companionship, dear friend. " << userParty[value].getPokemonName() << " will be missed." << endl;
            userParty.erase(userParty.begin() + value); // delete that pokemon
            trainers[15].setPartyPokemon(userParty); // update the user's party
        }
        else if(userParty.size() == 3) { // if there are only 3 pokemon in the party
            value = rand()%2 +1; // generate a random number between 0 and 2
            cout << "Oh no! After years of legendary battles, " << userParty[value].getPokemonName() << " died of old age. Thank you for your companionship, dear friend. " << userParty[value].getPokemonName() << " will be missed." << endl;
            userParty.erase(userParty.begin() + value); // delete that pokemon
            trainers[15].setPartyPokemon(userParty); // update the user's party
        }
        else if(userParty.size() == 4) { // if there are only 4 pokemon in the party
            value = rand()%3 +1; // generate a random number between 0 and 3
            cout << "Oh no! After years of legendary battles, " << userParty[value].getPokemonName() << " died of old age. Thank you for your companionship, dear friend. " << userParty[value].getPokemonName() << " will be missed." << endl;
            userParty.erase(userParty.begin() + value); // delete that pokemon
            trainers[15].setPartyPokemon(userParty); // update the user's party
        }
        else if(userParty.size() == 5) { // if there are only 5 pokemon in the party
            value = rand()%4+1; // generate a random number between 0 and 4
            cout << "Oh no! After years of legendary battles, " << userParty[value].getPokemonName() << " died of old age. Thank you for your companionship, dear friend. " << userParty[value].getPokemonName() << " will be missed." << endl;
            userParty.erase(userParty.begin() + value); // delete that pokemon
            trainers[15].setPartyPokemon(userParty); // update the user's party
        }
        else { // if the party is full
            value = rand()%5 +1; // generate a random number between 0 and 5
            cout << "Oh no! After years of legendary battles, " << userParty[value].getPokemonName() << " died of old age. Thank you for your companionship, dear friend. " << userParty[value].getPokemonName() << " will be missed." << endl;
            userParty.erase(userParty.begin() + value); // delete that pokemon
            trainers[15].setPartyPokemon(userParty); // update the user's party
        }
    }
}

/** checkNumTypes() - check the number of types in the user's pokedex and party
 * Basically just go through the vectors and see how many different types there are? 
*/ 

int Game::checkNumTypes() {
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    vector<Pokemon> userPokedex = trainers[15].getPokedexPokemon();
    for(int i=0; i<userParty.size(); i++) {
        userPokedex.push_back(userParty[i]);
    }
    vector<string> types;
    types.push_back(userPokedex[0].getTypeA()); // put the first type into the types array to start out
    for(int j=1; j<userPokedex.size(); j++) { // looking through type A pokemon
        bool typeAFound = false;
        for(int k=0; k<types.size(); k++) { // go through the types already counter 
            if(types[k] == userPokedex[j].getTypeA()) { // if the types have not been counted
                typeAFound = true;
            }
        }
        if(typeAFound == false) { // if the type was not found
            types.push_back(userPokedex[j].getTypeA()); // add it to the vector
        }
    }
    for(int j=0; j<userPokedex.size(); j++) { // go through the pokedex again, this time looking at type B
        bool typeBFound = false;
        for(int k=0; k<types.size(); k++) { // go through the types already counter
            if(types[k] == userPokedex[j].getTypeB() && userPokedex[j].getTypeB() != "") { // if the types have not been counted
                typeBFound = true;
            }
        }
        if(typeBFound == false) { // if the type was not found
            types.push_back(userPokedex[j].getTypeB()); // add it to the vector
        }
    }
    int numTypes = types.size();
    trainers[15].setNumTypes(numTypes); // set the number of types
    return numTypes; 
}

/** welcome() - sets up the new user with a name, start pokemon and position. 
 *  1. Get the user's name
 *  2. Ask the user which start pokemon the want
 *  3. Based on that, intialize the starting position of the user.
*/

void Game::welcome() {
    vector<Pokemon> userParty = trainers[15].getPartyPokemon();
    cout << "Welcome to Pokemon!" << endl;
    cout << "Please state your name: " << endl;
    string name; 
    getline(cin, name); // get name from user
    trainers[15].setUsername(name); // set that as their username
    trainers[15].setPokeballs(10); // give the user 10 pokeballs
    cout << "Welcome, " << name << "! Before you can begin your Pokémon adventure, you must choose a starting Pokémon, courtesy of the Professor. Please choose from the following Pokémon: " << endl;
    cout << "1. Bulbasaur" << endl; // prompt user to choose a starter pokemon
    cout << "2. Charmander" << endl;
    cout << "3. Squirtle" << endl;
    cout << "4. Pikachu" << endl;
    char starter;
    bool starterValid = false;
    while(starterValid == false) { // until the user makes a valid choice
        string stringStarter;
        cin >> stringStarter; // get which pokemon they want
        starter = stringStarter[0];
        switch(starter) {
            case '1' : // if user chose 1 (Bulbasaur)
                cout << "Bulbasaur has joined your party!" << endl;
                userParty.push_back(allPokemon[0]); // add bulbasaur to their party
                trainers[15].setPartyPokemon(userParty);
                trainers[15].setTrainerRow(13); // update the user's location
                trainers[15].setTrainerColumn(7);
                starterValid = true; // the user has made a valid starter pokemon choice
                break;
            case '2' : // if user chose 2 (Charmander)
                cout << "Charmander has joined your party!" << endl;
                userParty.push_back(allPokemon[3]); // add charmander to their party
                trainers[15].setPartyPokemon(userParty);
                trainers[15].setTrainerRow(13); // update the user's location
                trainers[15].setTrainerColumn(8);
                starterValid = true; // the user has made a valid starter pokemon choice
                break;
            case '3' :  // if user chose 3 (Squirtle)
                cout << "Squirtle has joined your party!" << endl;
                userParty.push_back(allPokemon[6]); // add squirtle to their party
                trainers[15].setPartyPokemon(userParty);
                trainers[15].setTrainerRow(13); // updates the user's location
                trainers[15].setTrainerColumn(9);
                starterValid = true; // the user has made a valid starter pokemon choice
                break;
            case '4' : // if user chose 4 (Pikachu)
                cout << "Pikachu has joined your party!" << endl;
                userParty.push_back(allPokemon[24]); // add pikachu to their party
                trainers[15].setPartyPokemon(userParty); 
                trainers[15].setTrainerRow(13); // update the user's location
                trainers[15].setTrainerColumn(10);
                starterValid = true; // the user has made a valid starter choice
                break;
            default : // the user has not entered a valid choice
                cout << "Please enter the number corresponding to the starter Pokemon you want. (1, 2, 3, or 4)" << endl;
                break;
        }
    }
}

/** userWinning() - if the user has won the game, ask if the user wants to continue playing or quit the game 
 * Returns true if the user is already winning but wants to continue playing
 * Returns 0 if the user wants to quit
 * Returns 1 if the user wants to continue playing 
*/

int Game::userWinning() {
    if(trainers[15].getNumTypes() >= 8 && trainers[15].getBadges() < 6) { // if the user has collected more than 8 types of pokemon but not 6 badges:
        cout << "You have collected more than 8 types of Pokemon! You have won the game! Would you like to continue playing? (Y/N)" << endl;
    }
    else if(trainers[15].getNumTypes() < 8 && trainers[15].getBadges() >= 6) { // if the user has collected 6 badges but not 8 types of pokemon:
        cout << "You have successfully battled 6 or more trainers and acquired badges for each trainer! You have won the game! Would you like to continue playing? (Y/N)" << endl;
    }
    else if(trainers[15].getNumTypes() >= 8 && trainers[15].getBadges() >= 6) { // if the user has collected both 6 badges AND 8 types of pokemon:
        cout << "You have successfully defeated 6 or more trainers AND have collected more than 8 types of Pokemon! Great job " << trainers[15].getUsername() << "! Would you like to continue playing? (Y/N)" << endl;
    }
    char choice;
    bool validChoice = false;
    while(validChoice == false) { // until the user has made a valid choice
        string stringChoice;
        cin >> stringChoice; // get answer from user
        choice = stringChoice[0]; // only take the first character of the string given (to prevent user error)
        switch(choice) {
            case 'Y' : // if yes, the user wants to continue playing:
                cout << "Okay! Press 4 to quit when you are ready! Have fun trainer!" << endl;
                validChoice = true; // the user has made a valid choice
                return 1; // return 1
                break;
            case 'N' : // if no, the user wants to quit
                validChoice = true; // the user has made a valid choice
                return 0; // return 0
                break;
            default : // if the user has not made a valid choice
                cout << "Please enter a valid letter (Y/N)" << endl;
                validChoice = false;
                break;
        }
    }
}

/** endOfGame() - displays the username and points and writes them to a file */

void Game::endOfGame() {
    cout << endl;
    cout << "Thank you for playing " << trainers[15].getUsername() << "! Come back again soon!" << endl;
    cout << trainers[15].getUsername() << ": " << trainers[15].getPoints() << endl; // display the number of points the user got
    char winning;
    if(trainers[15].checkIfWinning() == true) { // if the user is winning
        winning = 'Y'; // write Y to the file for winning
    } 
    else if(trainers[15].checkIfWinning() == false) { // if the user is not winning
        winning = 'N'; // write N to the file for winning
    }
    ofstream outFile; 
    outFile.open("resultsPokemon.txt",ios::app); // append the username and points to the end of the file
    string line;
    int tab = 9; // add tabs for beautiful tabulated values
    outFile << trainers[15].getUsername() << (char)tab << (char)tab << (char)tab << winning << (char)tab << (char)tab << trainers[15].getPoints() << endl;
    outFile.close();
}