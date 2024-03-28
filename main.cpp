/*
    Name: Chase Prasad

    Title: Everglades RPG

    Given multiple user inputs, run a simple game where the player has to meet a goal while facing obstacles along the way.

    Input: Desired cell location to move too and action taken when facing a danger.

    Processing: 1. Initialize variables and start main menu-driven loop.
                2. Prompt user for menu choice.
                3. Display output of chosen menu choice.
                   3-1. If menu choice is to play the game then display map and time left.
                   3-2. Prompt user for cell choice to move to and validate input.
                   3-3. Display output of chosen cell choice, either player moves to cell or faces a danger.
                        3-3-1. If danger appears then display options to face danger.
                        3-3-2. Prompt user for option choice and validate input.
                        3-3-3. Display output of chosen option choice and return to main game-driving loop.

    Output: The Lost in the Everglades game.
*/

// Header files
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function prototypes
void instructions();
void displayMap(const char[][5]);
int errorCheck(int, int, int, int);
void createDangers(int[][5]);
void danger(char[][5], int, int, int&, int&, int&);

int main()
{
    // Variables
    int choice, gong = 12, currentR = 0, currentC = 0, moveR, moveC;
    char map[][5] = {{'R', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', 'T'}};
    int dangerLocs[][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},{0, 0, 0, 0, 0}};

    // Randomizing danger locations
    createDangers(dangerLocs);

    do
    {
        
        // App title and main menu-driven loop
        cout << "Welcome to Lost in the Everglades!\n\nWhat would you like to do?\n\t";
        cout << "1. See rules.\n\t2. Play game.\n\t3. Quit.\n\nOption : ";

        // Switch for different menu choices
        switch(cin >> choice; choice)
        {
            case 1:
                instructions();
                break;
            
            case 2:
                
                // Main loop for game driving
                while(gong > 0)
                {
                    displayMap(map);

                    // Cell input validation
                    int error = 0;
                    while(error != 1)
                    {
                        cout << "\n\nGongs Left: " << gong << "\n\nWhere would you like to move? (row & col): ";
                        cin >> moveR >> moveC;
                        switch(error = errorCheck(moveR, moveC, currentR, currentC); error)
                        {
                            case -1:
                                cout << "\nPlease enter a valid cell.";
                                break;
                            
                            case -2:
                                cout << "\nPlease only move to a cell adjacent to the current cell.";
                                break;
                        }
                    }

                    // Checking for danger in desired cell
                    if(dangerLocs[moveR][moveC] == 1)
                    {
                        danger(map, moveR, moveC, currentR, currentC, gong);
                    }
                    else
                    {
                        cout << "\nYou have advanced to (" << moveR << "," << moveC << ")!\n";
                        
                        gong--;
                        map[currentR][currentC] = ' ';
                        map[moveR][moveC] = 'R';
                        currentR = moveR;
                        currentC = moveC;
                        error = 0;
                    }

                    // Checks if game has been won
                    if(map[4][4] == 'R')
                    {
                        cout << "\nCongratulations! You have found the lost tourists!\n";
                        return 0;
                    }
                }

                // Display for when game has been lost
                if(map[4][4] != 'R')
                {
                    cout << "\nYou have ran out of time and the lost tourists are still trapped. Try again next time!\n\n";
                    return 0;
                }
        }
    } while (choice != 3);
    cout << "\nGoodbye!";
    
    return 0;
}

// Function to display game instructions
void instructions()
{
    cout << "\nLost in the Everglades is an RPG (Role-Playing Game) between a player and the computer.\n\n";

    cout << "A group of tourists has been lost in the Everglades and a ranger must rescue them before time runs out.\n\n";

    cout << "The Everglades are represented by a 5x5 map.\n";
    cout << "The ranger (R) starts the rescue at the upper-left corner of the park, the group of tourists (T) are lost at the lower-right corner.\n";
    cout << "The ranger has 12 gongs of time to find and rescue the tourists before they perish.\n\n";

    cout << "During the journey, the ranger might find dangers (hungry alligator, swarm of giant mosquitoes, venomous spider, or python).\n";
    cout << "When the ranger finds a danger, they can choose to fight them, or hide and wait for them to leave.\n\n";

    cout << "If the Ranger waits, they get to move to the desired location but lose 5 gongs of time.\n";
    cout << "If the Ranger fights and wins, they get to move to the desired location and only lose 2 gongs of time.\n";
    cout << "If the Ranger fights and loses, they stay in their location and lose 3 gongs of time. The danger also stays in its location.\n\n";

    cout << "If the Ranger moves to a location with no dangers, they only lose 1 gong of time.\n\n";

    cout << "The game is over when either the Ranger rescues the group of tourists or time runs out and the tourists stay trapped forever.\n\n";

    cout << "Good luck and have fun!\n\n";
}

// Function to display game map
void displayMap(const char m[][5])
{
    cout << "\nLoading Map . . .\n\n    0    1    2    3    4\n  -------------------------\n";
    for(int x = 0; x < 5; x++)
    {
        cout << x << " ";
        for(int y = 0; y < 5; y++)
        {
            cout << "| " << m[x][y] << " |";
        }
        cout << endl;
    }
    cout << "  -------------------------";
}

// Function to validate cell input
int errorCheck(int mR, int mC, int cR, int cC)
{
    if(mR < 0 || mR > 4)
    {
        return -1;
    }
    if(mC < 0 || mC > 4)
    {
        return -1;
    }
    if(cR < --mR || cR > ++mR)
    {
        return -2;
    }
    if(cC < --mC || cC > ++mC)
    {
        return -2;
    }
    return 1;
}

// Function to randomize danger locations
void createDangers(int dL[][5])
{
    srand(time(NULL));

    for(int x = 0; x < 10; x++)
    {
        dL[rand() % 5][rand() % 5] = 1;
    }
    dL[4][4] = 0;
}

// Function to randomize danger in location and drive danger actions
void danger(char m[][5], int mR, int mC, int& cR, int& cC, int& g)
{
    string dangerNames[] = {"Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python"};
    char dangerChars[] = {'A', 'M', 'S', 'P'};
    int move = 0, fight;
    srand(time(NULL));
    int dangerChoice = rand() % 4;

    while(move < 1 || move > 2)
    {
        cout << "\n\nWatch out! There's a " << dangerNames[dangerChoice] << " ahead!\n\nChoose your next move:\n\t1. Wait until it leaves.\n\t2. Fight it.\n\nYour Move: ";
        cin >> move;
        if(move < 1 || move > 2)
        {
            cout << "\nPlease choose a valid move.\n";
        }
    }

    switch(move)
    {
        case 1:
            cout << "\nThe " << dangerNames[dangerChoice] << " is gone! You advance!\n";

            g -= 5;
            m[cR][cC] = ' ';
            m[mR][mC] = 'R';
            cR = mR;
            cC = mC;
            break;
        case 2:
            fight = rand() % 2;
            if(fight == 0)
            {
                cout << "\n\nYou fight the " << dangerNames[dangerChoice] << " and lose. You retreat.\n\n";

                g -= 3;
                m[mR][mC] = dangerChars[dangerChoice];
            }
            else
            {
                cout << "\nYou fight the " << dangerNames[dangerChoice] << " and win! You advance!\n";

                g -= 2;
                m[cR][cC] = ' ';
                m[mR][mC] = 'R';
                cR = mR;
                cC = mC;
            }
            break;
    }
}