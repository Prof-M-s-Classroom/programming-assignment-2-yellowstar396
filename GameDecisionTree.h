#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "Node.h"
#include "Story.h"
using namespace std;

template <typename T>
class GameDecisionTree {
private:
    Node<Story*>* root;
    map<int,Node<Story*>* > eventMap;

public:
    // TODO: Constructor
    GameDecisionTree() : root(nullptr) {}

    // TODO: Function to load story data from a text file and build the binary tree
    //we will assume that the first action is always eventNumber=0
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        getEventMap(filename, delimiter);
        loadStoryFromFileHelper(delimiter, 0);
    }

    Node<Story*>* loadStoryFromFileHelper(char delimiter, int currentEventNumber) {
        //base case
        if (currentEventNumber==-1) {
            return nullptr;
        }

        Node<Story*>* currentNode = this->eventMap[currentEventNumber];
        int leftEventNumber = currentNode->data->leftEventNumber;
        int rightEventNumber = currentNode->data->rightEventNumber;
        currentNode->left = loadStoryFromFileHelper(delimiter, leftEventNumber);
        currentNode->right = loadStoryFromFileHelper(delimiter, rightEventNumber);
        return currentNode;
    }

    void getEventMap(const string& fileName, char delimiter){
        ifstream file(fileName);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
        }
        map<int, Node<Story*>*> events;
        Story* story;
        string line;
        Node<Story*>* current;
        while (getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            if (line.empty()) continue;

            story = stringToStory(line, delimiter);
            current = new Node<Story*>(story);
            events.insert({story->eventNumber, current});
        }
        file.close();
        this->root = events[0];
        this->eventMap = events;
        //return events;
    }

    Story* stringToStory(string str, char delimiter) const {
        string parts[4];
        int currentPart = 0;
        string temp = "";
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == delimiter) {
                temp.erase(0, temp.find_first_not_of(" \t\r\n")); //
                parts[currentPart] = temp;
                temp = "";
                currentPart++;
            }
            else {
                temp += str[i];
            }
        }
        parts[currentPart] = temp;
        Story* story = new Story();
        //cout << parts[0] << endl;
        story->eventNumber = stoi(parts[0]);
        story->description = parts[1];
        //cout << parts[2] << endl;
        story->leftEventNumber = stoi(parts[2]);
        //cout << parts[3] << endl;
        story->rightEventNumber = stoi(parts[3]);
        return story;
    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        playEvent(root);
    }

    void playEvent(Node<Story*>* currentNode) {
        if (currentNode == nullptr) {
            cout << "Game Over!" << endl;
            return;
        }
        cout << currentNode->data->description << endl;
        playEvent(askForAction(currentNode));
    }

    Node<Story*>* askForAction(Node<Story*>* currentNode) {
        if (currentNode->data->leftEventNumber == -1 || currentNode->data->rightEventNumber == -1) {
            return nullptr;
        }
        int nextEventNumber;
        cin >> nextEventNumber;
        if (nextEventNumber == currentNode->data->leftEventNumber) {
            return currentNode->left;
        }
        if (nextEventNumber == currentNode->data->rightEventNumber) {
            return currentNode->right;
        }
        cout << "No such event!" << endl;
        return nullptr;
    }
};

#endif // GAMEDECISIONTREE_H