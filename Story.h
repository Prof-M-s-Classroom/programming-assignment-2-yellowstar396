#ifndef STORY_H
#define STORY_H

#include <string>
using namespace std;
class Story {
public:
    string description;
    int eventNumber;
    int leftEventNumber;
    int rightEventNumber;

    // Default constructor
    Story();

    // Parameterized constructor
    Story(string desc, int num, int leftNum, int rightNum);
};

//

#endif // STORY_H