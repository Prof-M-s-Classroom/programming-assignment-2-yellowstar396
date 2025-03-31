#include <iostream>
#include <string>
#include "GameDecisionTree.h"
using namespace std;
int main() {
    GameDecisionTree<Story> myGame;

    string filename = "story.txt";  // Specify the input file
    // This should be specifically on my computer:
    //C:\\College\\Spring 2025\\CS 210\\Code\\programming-assignment-2-yellowstar396\\story.txt
    char delimiter = '|';                // '|' is the delimiter, change if needed

    // Load the story data from the file
    myGame.loadStoryFromFile(filename, delimiter);

    // Start the game
    myGame.playGame();

    return 0;
}

