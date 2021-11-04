//
//  main.cpp
//  Jamir Nunley - MP2
//
//  Created by Jamir Nunley on 10/18/21.
//

// BUG

// This program plays the game of Beetle where both players are human and each player has their own beetle. The game allows each player to take turns with Player 1 going first and player 2 going second. Before starting a turn the game asks each player weather they want to build or consume, entering "Roll" to build or "Break" to consume the oppenent's beetle. The die is then rolled and the body part rolled is built or broken. Each dice roll and each player's current beetle is displayed during the game.

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <random>

using namespace std;

int rollDie() { // Dice Function randomly generates sides 1-6
  srand((int) time(nullptr));
  int dice = (rand() % 6 ) + 1;
  cout << "Dice: " << dice << endl;
    
    return dice;
}

bool isBodyPart( string currentBody , char c);
bool isBeetleComplete( string currentBody );
char getUserInput( void );
char convertDieToPart(int roll);
bool attack(string currentBody);

class Beetle // Beetle represented by main class
{
public: // Public so that parts can be accessed outside of class
    Beetle() { // Initialize number of each part
        body_num = 0;
        head_num = 0;
        leg_num = 0;
        eye_num = 0;
        antenna_num = 0;
        tail_num = 0;
        complete_beetles = false;

    }
    void beetle_game(int roll_a_dice) { // Roll dice and add corresponding part, increment based on position
       
        if (roll_a_dice == 1 && body_num < 1) { // Body
            body_num = 1;
            for (int i = 4; i < 9; i++) {
                partial_beetle[i] = body[i - 4];
            }
        }
        if (body_num == 1 && roll_a_dice == 2 && head_num < 1) { // Head
            head_num = 1;
            for (int i = 1; i < 4; i++) {
                partial_beetle[i] = head[i - 1];
            }
        }
        if (body_num == 1 && roll_a_dice == 3 && leg_num < 1) { // Legs
            leg_num = 1;
            partial_beetle[4] = leg_1[0];
        }
    
        if (leg_num == 1 && roll_a_dice == 3 && 1 <= leg_num < 2) {
            leg_num = 2;
            partial_beetle[5] = leg_2[0];
        }
        if (leg_num == 2 && roll_a_dice == 3 && 2 <= leg_num < 3) {
            leg_num = 3;
            partial_beetle[6] = leg_3[0];
        }

        if (body_num == 1 && roll_a_dice == 6 && tail_num < 1) { // Tail
            tail_num = 1;
            for (int i = 9; i < len_beetle; i++) {
                partial_beetle[i] = tail[i - 9];
            }
        }
        if (head_num == 1 && roll_a_dice == 5 && antenna_num < 1) { // Antennas
            antenna_num = 1;
            for (int i = 0; i < 2; i++) {
                partial_beetle[i] = antenna_1[i];
            }
            
        }
        else if (antenna_num == 1 && roll_a_dice == 5 && 1 <= antenna_num < 2) {
            antenna_num = 2;
            for (int i = 0; i < 2; i++) {
                partial_beetle[i] = antenna_2[i];
            }
        }
        if (head_num == 1 && roll_a_dice == 4 && eye_num < 1) { // Eyes
            eye_num = 1;
            partial_beetle[2] = eye_1[0];
        }
        if (eye_num == 1 && roll_a_dice == 4 && 1<= eye_num < 2) {
            eye_num = 2;
            partial_beetle[2] = eye_2[0];
        }
    }

    bool complete_beetle() { // Check for all parts
        
        if (body_num == 1 && head_num == 1 && leg_num == 3 && eye_num == 2 && antenna_num == 2 && tail_num == 1) {
            complete_beetles = true;
        }
        else
        {
            complete_beetles = false;
        }
        return complete_beetles;
        
    }
    void show() const { // Show beetle 1 & 2 in debug window
      
        for (int i = 0; i < len_beetle; i++) {
            cout<<partial_beetle[i]<< endl;
        }
        return;
    }

    friend ostream& operator<<(ostream& stream, const Beetle& thebeetle); // Output operator for beetle
public: // Public so that parts are accessible outside of class
    bool complete_beetles;
    int body_num;
    int head_num;
    int leg_num;
    int eye_num;
    int antenna_num;
    int tail_num;
    const int len_beetle = 12; // Body part elements total = 12
    string body[5] = {
    "     /  -  \\      ",
    "    |---.---|      ",
    "    |   |   |      ",
    "    \\   |   /     ",
    "     '. : .'       ",
        
    };
    string head[3] = {

    "      \\_          ",
    "                   ",
    "      \\___/       "
        

    };

    string antenna_1[2] = {
    "      Y           ",
    "      \\\\_       ",
    };
    string antenna_2[2] = {
    "      Y   Y         ",
    "      \\\\_//       ",

    };

    string eye_1[1] = {
    "     (0             "
        
    };
    string eye_2[1] = {
    "    (0     0)      ",
    };
    string tail[3] = {
    "      |-|-|        ",
    "      |-|-|        ",
    "       V V         "
    };
    string leg_1[1] = {
    "  ]--/  -  \\--[  ",

    };
    string leg_2[1] = {
    "]---|---.---|---[ ",
    };
    string leg_3[1] = {
    " ]--|   |   |--[  ",
    };

    string partial_beetle[12] = { // Total of elements for partial or complete beetle
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  "
    };


};

class BeetleBreak // Beetle break represented by main class
{
public: // Public so that blank parts can be accessed outside of class
    BeetleBreak() {
        body_num = 0;
        head_num = 0;
        leg_num = 0;
        eye_num = 0;
        antenna_num = 0;
        tail_num = 0;
        complete_beetles = false;

    }
    void beetle_game(int roll_a_dice) { // Roll dice and break corresponding part
       
        if (roll_a_dice == 1 && body_num < 1) { // Body
            body_num = 1;
            for (int i = 4; i < 9; i++) {
                partial_beetle[i] = body[i - 4];
            }
        }
        if (body_num == 1 && roll_a_dice == 2 && head_num < 1) { // Head
            head_num = 1;
            for (int i = 1; i < 4; i++) {
                partial_beetle[i] = head[i - 1];
            }
        }
        if (body_num == 1 && roll_a_dice == 3 && leg_num < 1) { // Legs
            leg_num = 1;
            partial_beetle[4] = leg_1[0];
        }
    
        if (leg_num == 1 && roll_a_dice == 3 && 1 <= leg_num < 2) {
            leg_num = 2;
            partial_beetle[5] = leg_2[0];
        }
        if (leg_num == 2 && roll_a_dice == 3 && 2 <= leg_num < 3) {
            leg_num = 3;
            partial_beetle[6] = leg_3[0];
        }

        if (body_num == 1 && roll_a_dice == 6 && tail_num < 1) { // Tail
            tail_num = 1;
            for (int i = 9; i < len_beetle; i++) {
                partial_beetle[i] = tail[i - 9];
            }
        }
        if (head_num == 1 && roll_a_dice == 5 && antenna_num < 1) { // Antennas
            antenna_num = 1;
            for (int i = 0; i < 2; i++) {
                partial_beetle[i] = antenna_1[i];
            }
            
        }
        else if (antenna_num == 1 && roll_a_dice == 5 && 1 <= antenna_num < 2) {
            antenna_num = 2;
            for (int i = 0; i < 2; i++) {
                partial_beetle[i] = antenna_2[i];
            }
        }
        if (head_num == 1 && roll_a_dice == 4 && eye_num < 1) { // Eyes
            eye_num = 1;
            partial_beetle[2] = eye_1[0];
        }
        if (eye_num == 1 && roll_a_dice == 4 && 1<= eye_num < 2) {
            eye_num = 2;
            partial_beetle[2] = eye_2[0];
        }
    }

    bool complete_beetle() { // Check for all parts
        
        if (body_num == 1 && head_num == 1 && leg_num == 3 && eye_num == 2 && antenna_num == 2 && tail_num == 1) {
            complete_beetles = true;
        }
        else
        {
            complete_beetles = false;
        }
        return complete_beetles;
        
    }
    void show() const { // Show broken beetle 1 & 2 in debug window
      
        for (int i = 0; i < len_beetle; i++) {
            cout<<partial_beetle[i]<< endl;
        }
        return;
    }

    friend ostream& operator<<(ostream& stream, const Beetle& thebeetle); // Output operator for beetle
public: // Public so that broken parts are accessible outside of class
    bool complete_beetles;
    int body_num;
    int head_num;
    int leg_num;
    int eye_num;
    int antenna_num;
    int tail_num;
    const int len_beetle = 12; // Broken part elements
    string body[5] = {
    "                   ",
    "                   ",
    "                   ",
    "                   ",
    "                   ",
        
    };
    string head[3] = {

    "                   ",
    "                   ",
    "                   "
        

    };

    string antenna_1[2] = {
    "                  ",
    "                  ",
    };
    string antenna_2[2] = {
    "                  ",
    "                  ",

    };

    string eye_1[1] = {
    "                  "
        
    };
    string eye_2[1] = {
    "                  ",
    };
    string tail[3] = {
    "                  ",
    "                  ",
    "                  "
    };
    string leg_1[1] = {
    "                  ",

    };
    string leg_2[1] = {
    "                  ",
    };
    string leg_3[1] = {
    "                  ",
    };

    string partial_beetle[12] = { // Total of elements for broken beetle
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  ",
    "                  "
    };


};

ostream& operator<<(ostream& stream, const Beetle& thebeetle) { // Access public members of beetle again
    thebeetle.show();
    return stream; // Return output stream
}


int main() {

    char readchar; // Transfer array strings to and from connections

    
    string answer; // "Yes" to roll "Break" to attack player
    Beetle beetle1;
    Beetle beetle2;
    Beetle beetle3;
    Beetle beetle4;
    cout << "Do you want to roll? (Answer 'yes' to roll, 'break' to attack player)." << endl;
    cin >> answer;


    while (1>0) { // Loop to update each beetle
        if (answer == "yes") {
            int dice = rollDie();
            
            cout << "Player 1 rolled a " << dice << endl;
            beetle1.beetle_game(dice);
            if (beetle1.complete_beetle() == false) {
                cout << "This is Player 1's beetle" << endl; // Dispay Player 1 beetle
                cout << beetle1 << endl;
            }
            else {
                cout << "This is Player 1's beetle" << endl;
                cout << beetle1 << endl;
                break;
            }
        }
        else if(answer == "break") {
            int dice = rollDie();
            
            cout << "Player 1 rolled a " << dice << endl;
            beetle1.beetle_game(dice);
            if (beetle1.complete_beetle() == false) {
                cout << "This is Player 1's beetle" << endl; // Dispay Player 1 broken beetle
                if (dice == 3){beetle1.leg_1[0] = beetle3.leg_1[0];} // Converts selected element to blank or "broken"
                if (dice == 3){beetle1.leg_2[0] = beetle3.leg_2[0];}
                if (dice == 3){beetle1.leg_3[0] = beetle3.leg_3[0];}
                if (dice == 4){beetle1.eye_1[0] = beetle3.eye_1[0];}
                if (dice == 4){beetle1.eye_2[0] = beetle3.eye_2[0];}
                if (dice == 5){beetle1.antenna_1[0] = beetle3.antenna_1[0];}
                if (dice == 5){beetle1.antenna_1[1] = beetle3.antenna_1[1];}
                if (dice == 5){beetle1.antenna_2[0] = beetle3.antenna_2[0];}
                if (dice == 5){beetle1.antenna_2[1] = beetle3.antenna_2[1];}
                if (dice == 6){beetle1.tail[0] = beetle3.tail[0];}
                if (dice == 6){beetle1.tail[1] = beetle3.tail[1];}
                if (dice == 6){beetle1.tail[2] = beetle3.tail[2];}
                cout << beetle1 << endl;
            }
            else {
                cout << "This is Player 1's beetle" << endl;
                cout << beetle3 << endl;
                break;
            }
            
                cout << "Player 2 rolled a " << dice << endl; // Display Player 2 broken beetle
                beetle2.beetle_game(dice);
                if (beetle2.complete_beetle() == false) {
                    cout << "This is Player 2's beetle" << endl;
                    if (dice == 3){beetle2.leg_1[0] = beetle4.leg_1[0];} // Converts selected elements to blank or "broken"
                    if (dice == 3){beetle2.leg_2[0] = beetle4.leg_2[0];}
                    if (dice == 3){beetle2.leg_3[0] = beetle4.leg_3[0];}
                    if (dice == 4){beetle2.eye_1[0] = beetle4.eye_1[0];}
                    if (dice == 4){beetle2.eye_2[0] = beetle4.eye_2[0];}
                    if (dice == 5){beetle2.antenna_1[0] = beetle4.antenna_1[0];}
                    if (dice == 5){beetle2.antenna_1[1] = beetle4.antenna_1[1];}
                    if (dice == 5){beetle2.antenna_2[0] = beetle4.antenna_2[0];}
                    if (dice == 5){beetle2.antenna_2[1] = beetle4.antenna_2[1];}
                    if (dice == 6){beetle2.tail[0] = beetle4.tail[0];}
                    if (dice == 6){beetle2.tail[1] = beetle4.tail[1];}
                    if (dice == 6){beetle2.tail[2] = beetle4.tail[2];}
                    cout << beetle2 << endl;
                }
                else {
                    cout << "This is Player 2's beetle" << endl;
                    cout << beetle4 << endl;
                    break;
        
                }
        
        }

        int dice = rollDie();
        cout << "Player 2 rolled a " << dice << endl; // Display Player 2 beetle
        beetle2.beetle_game(dice);
        if (beetle2.complete_beetle() == false) {
            cout << "This is Player 2's beetle" << endl;
            cout << beetle2 << endl;
        }
        else {
            cout << "This is Player 2's beetle" << endl;
            cout << beetle2 << endl;
            break;
        }

        
        cout << "Do you want to roll? (Answer 'yes' to roll, 'break' to attack player)" << endl; // Ask to roll or break
        cin >> answer;
    }

    
    cout << "Game Over.\n" << endl; // Determine the winner
    if (beetle1.complete_beetle() == true) {
        cout << "Player 2 wins!" << endl;
    }
    else {
        cout << "Player 1 wins!" << endl;
    }
    cin >> readchar; //  Keep player screen open
    return 0;
    
    }

