[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jIKk4bke)
# CS210 Data Structures SP25
## Programming Assignment 2: Text-Based RPG Using Decision Trees

### **Student Name:** `Idan Haim`  
### **Student ID:** `[132250570]`  

---

## **1. Project Overview**
(Provide a brief summary of your RPG game. Describe how it uses a decision tree and how the player interacts with it.)

Example:
> This is an RBG game that tells a story about a genie. The game work by navigating a pre-made decision (binary) tree. The tree is built from a text file using an algorithm I made to parse the lines and correctly connect the nodes to each other (as I will explain below in other sections). When playing the game, the player will be read the description of the current node, and will then be presented with his following action choices (coupled with their corresponding event numbers). To choose an option, the player will enter its event number. The player will always start at event number 0. The game will end once the player reaches a node with at least one (-1) child value.

---

## **2. Folder & File Structure**
(Explain the role of each file in your project.)

- **`main.cpp`** → `main.cpp is responsible for running the code - giving the command to construct the tree (which also providing the corrent file path for the code to work), and giving the command to start playing. main.cpp also determines the delimiter value.`  
- **`GameDecisionTree.h`** → `GameDecisionTree.h is the file that will mostly excecute the instructions from main. It will construct the tree and will then run it.`  
- **`Node.h`** → `Node.h contains the implementation for the nodes. It might seem small, but Node.h is an integral part of running and constructing a GameDecisionTree (as GameDecisionTree is built from nodes).`  
- **`Story.h`** → `Each Node in our GameDecisionTree will contain a story instance. A story object holds the description of the even of the story, while also holding its current, right, and left event numbers. The Story class helps us correctly read the data and navigate the tree.`  
- **`story.txt`** → `This file will contain the whole story (each event has its own line). When creating the GameDecisionTree, story.txt will be read, and exach of its lines will be converted to Story objects that are held inside the nodes of the tree.`  

---

## **3. Decision Tree Construction**
(Explain how the decision tree is built from the `story.txt` file.)

- How are `Story` objects created from the text file?  
  - To create story objects, the code will go over story.txt line by line. Each line will be split by the delimiter into a String array of size 4. The 4 parts of te array will then create a new story that will later on be added to the tree. This process is repeated until all lines are processed.
- How are nodes linked based on left and right event numbers?
  - A simple way to do this is for each waned event number, I would look in the file again to find the line matching the number and create a node from it.
  - This system has some problems:
    - To fully run this implementation. Repeated readings of the story.txt file will be needed (because we need to search through the file for each separate event) - which will severely harm time complexity.
    - Using this system, it will be harder to handle cases of two parents leading to the same child (as this system will create multiple nodes for one event).
  - Instead, I used a hash map to help construct the tree
    - I started by adding a map property to the GameDecisionTree class (to be able to quickly access it from every method)
    - When going over story.txt, instead of constructing the tree, I will create a node for each Story object, and add it to the map (key=eventNumber, value=NodePointer)
    - After constructing the map, I will get the node of key 0 (the first event), and recursively define the children of each node by using the 'leftEventNumber' and 'rightEventNumber' to obtain the nodes corresponding to these values from the created map and adding them to the tree.
    - After the tree is create, the map is not used anymore (although another interesting implementation would be to traverse the tree using a hash map and scraping the binary tree implementation entirely)
- What happens if an event has `-1` as left or right children?
  - As the assignment instructed, there will be no node with exactly one option to choose. Because of this, I check if the current node has at lease one (-1) value as one of his children. If so, the recursion returned (this is a base case)

---

## **4. Game Traversal**
(Describe how the game moves through the decision tree.)

- How does user input determine the path taken?
  - When the user inputs an eventNumber, the program will check if this eventNumber is one of the nodes children (eg. leftEventNumber, rightEventNumber). If so, it will go to that node, and ask for player input again (for the next event)
- What happens when the player reaches a leaf node? 
  - When a player reaches a leaf node, they will not be offered any further choice. The game will end and a "game over" message will be printed
- Explain the special case where multiple events lead to the same outcome.
  - If multiple events lead to the same outcome, all the specified parent nodes will have this outcome node as a child node. No special instructions were needed to implement this case (the code naturally builds the tree in a way that accounts for this)

---

## **5. File Parsing & Data Loading**
(Explain the process of reading `story.txt` and constructing the decision tree.)

- How is the file read and parsed using a delimiter?
  - The program knows how to split each line of the text file by the delimiter and construct a Story object from those parts 
- How do you ensure nodes are properly linked?
  - The discussed hash map helps with this. The hash map knows to return the correct node values for each eventNumber
- Any challenges faced while handling file input?  
  - At first, I forgot to add the full file path to the string, which caused an error when attempting to open the file

---

## **6. Debugging Process (Errors & Fixes)**
(Describe one or more debugging challenges you faced and how you fixed them.)

> One annoying mistake that I had was that the code kept throwing a sigmentation error (which was confusing because it has worked before I changed the story.txt file). I assumed I somehow formatted the story file wrong, but the formatting was valid. Turns out, after removing some of the code and focusing on a more manageable snippet of story, I discovered that the problem was that empty lines on the story.txt file were causing unneeded Story objects to be constructed, which were attempted to then be accessed. To solve this, I modified my program to ignore empty lines in the text file.

---

## **7. Sample Output & Walkthrough**
(Provide an example of how the game runs, including player input.)

> You, an SDSU student, are about to leave for your CS210 class today, but a sudden change of heart comes to your mind. Do you go to class(1) or go on an adventure with your friend(2)?
> 
> 2
> 
> You and your friend embark on your journey, leave SDSU, and go to the unexplored desert next to one of those freeways no one cares about. There, you find a cave. You are very curious about what awaits you inside, but you are also scared to go in. So you enter the cave(5)? or do you return to your room and call it a day(3)?
> 
> 3
> 
> When you go back to your room, you study for a couple of hours and finish your assignments. You feel ready to go to sleep, but suddenly you hear a storm outside. Do you ignore it and go to sleep(7) or go outside to check what is happening(8)?
>
> 8
> 
> When you look outside, you see a calamity never seen before. You see a huge storm of fire and lightning covered by a red sky. You want to escape but you are not sure you'll make it in time. Do you take your car and drive away(17) or try to hide in your room(16)?
>
> 17
> 
> You take your car and drive away just in time. You hear in the news that most of your city is now destroyed, but when you come back and see your house, it seems untouched, as if something... or someone... was protecting it
> 
> Game Over!

---

## **8. Big-O Analysis of Core Methods**
(Analyze the complexity of key methods.)

- **Loading the tree from the file** → `O(n), while n is the number of events in story.txt`
- Creating the hash map: for each line a Story object is created, and it is added to the hash map (~O(1))
  - Creating the tree. Each node is retrieved from the map (~O(1)), and the needed pointer is set to it (O(1)). All n nodes are added in this process. The total complexity of this stem is O(n), as the tree is traversed once (each node is immediately added, and we do not traverse from the root for every insertion)
- **Searching for an event in the tree** → `O(log(n))`
  - You will not need to "search" for a specific event, but to reach an event you will go through log(n) steps on average.
- **Game traversal efficiency** → `O(log(n))`
  - This is the same as searching a specific event, as you do not need to search each node all over again for each event. The tree is intentionally constructed such that the traversal from one even to its following even is O(1) (moving from parent to child once), so the entire complexity would be for traversing one branch of the tree

---

## **9. Edge Cases & Testing**
(Describe at least one edge case you tested and its outcome.)

> One edge case that I handled is printing "Error opening file!" when they file did not open correctly. This also helped me identify some of the bugs that I had later on in the code.

---

## **10. Justification of Additional Features (If Any)**
(If you added extra features, describe them and explain why.)

> As an extra feature, I added the hash map to my implementation of the code. We were no required to use this method, and we are not evaluated on efficiency, but I wanted to start practicing on optimizing my code efficiency - so before creating the code, I compared different implementation methods with different time complexities, and decided to go with a hash-map implementation to help create the tree.
>
> Important note: I only used the hash map to help create the tree more efficiently, but the main implementation (and the main part of the code) is based on the binary tree. I did not replace the binary tree with the hash map.
> 
> If you wish to learn more about how I used the hash map, read my explanation in section 3 - Decision Tree Construction.

---

## **Final Notes**
- **README is mandatory** → `(-10 points deduction if missing).`  
- **Code must compile and run** → `(Code that does not run will receive a 0).`  
- **Do not modify provided skeleton code** → `(You may only add to it).`  

---


