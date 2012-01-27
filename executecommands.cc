#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include "board.h"
#include "block.h"
#include "square.h"
#include "trie.h"
using namespace std;

//Preloads trie node with commands for shortcut use
void preloadshortcuts(TrieNode *node) {
   insert(node, "lef");
   insert(node, "left");
   insert(node, "ri");
   insert(node, "rig");
   insert(node, "righ");
   insert(node, "right");
   insert(node, "do");
   insert(node, "dow");
   insert(node, "down");
   insert(node, "cl");
   insert(node, "clo");
   insert(node, "cloc");
   insert(node, "clock");
   insert(node, "clockw");
   insert(node, "clockwi");
   insert(node, "clockwis");
   insert(node, "clockwise");
   insert(node, "co");
   insert(node, "cou");
   insert(node, "coun");
   insert(node, "count");
   insert(node, "counte");
   insert(node, "counter");
   insert(node, "counterc");
   insert(node, "countercl");
   insert(node, "counterclo");
   insert(node, "countercloc");
   insert(node, "counterclock");
   insert(node, "counterclockw");
   insert(node, "counterclockwi");
   insert(node, "counterclockwis");
   insert(node, "counterclockwise");
   insert(node, "dr");
   insert(node, "dro");
   insert(node, "drop");
   insert(node, "levelu");
   insert(node, "levelup");
   insert(node, "leveld");
   insert(node, "leveldo");
   insert(node, "leveldow");
   insert(node, "leveldown");
   insert(node, "re");
   insert(node, "res");
   insert(node, "rest");
   insert(node, "resta");
   insert(node, "restar");
   insert(node, "restart");
}

//Used for short-cut commands
string shortcut(string command, TrieNode *node) {
   istringstream ss (command.c_str()); //Declare a istringstream to read in the command
   int val;
   if (ss >> val) { //Checks to see if there's a number in front of the command, if so, it filters it out
	   string newstr;
	   ss >> newstr; //Grabs the rest of the string from the input
	   if (checkifexists(node, newstr)) //If the shortcut exists, grab the full command
		   return grabfullcommand(node, newstr);
		else
		   return command; //Otherwise just return the regular command and let executecommands deal with it
	}
	else if(checkifexists(node, command))
	   return grabfullcommand(node, command);
	else
	   return command;
}

//Executes list of commands
void executecommands(istream &input, Board *B, TrieNode *node, Xwindow *boardwindow, Xwindow *sidewindow, bool graphicstate) {
   B->graphicstate = graphicstate; //Give the board the graphicstate
   int highscore; //Used to keep track of highscore
   string command = ""; //Used for commands
   string filteredcommand = ""; //For shortcuts
   ifstream zero("sequence.txt"); //Reads in predetermined blocks used for level 0
   char type = B->nextblock(zero); //Determines the next block
   Block *current; //Block that is controlled by player
   Block *next = B->createblock(type, boardwindow, sidewindow); //Creates next block
   current = next; //Gets block from next
   if(B->checkcollision(B, current))//Restarts the board if there's no space to put the next block
      B->restart(); 
   B->boardadd(B, current); //Updates the board with position of current block
   cout << *B; //Prints board
   type = B->nextblock(zero);
   next = B->createblock(type, boardwindow, sidewindow);
   cout << *next; //Prints the next block
   while(1) { //This entire while loop controls a single block
      input >> command;
      filteredcommand = command;
      command = shortcut(command, node); //Runs the program for command shortcuts
    	istringstream ss (filteredcommand.c_str());
     	int times = 1;
     	if(ss >> times) {} //Checks to see if there's a number in front of the command, if so, grabs it
     	if(times == 0)
     	   times = 1;
      if(input.eof()) { //Ends program
         delete B;
         break;
      }
      if(command == "left") { //Executes "left" commands"
         for (int i = 0; i < times; i++) {
        	   B->boardremove(B, current); //Sets the squares where the block is located off
           	if(!B->checkleftcollision(B, current))
              	   B->move("left", current);
               B->boardadd(B, current); //Sets the squares where the block is located on
        	   }
         cout << *B; //Outputs board
         cout << *next; //Outputs next block
      }
      else if(command == "right") {
         for (int i = 0; i < times; i++) { 	
            B->boardremove(B, current);
            if(!B->checkrightcollision(B, current))
               B->move("right", current);
            B->boardadd(B, current);
         }
         cout << *B;
         cout << *next;
      }
      else if(command == "down") {
         B->boardremove(B, current);
       	for (int i = 0; i < times; i++){  		
           	if(!B->checkbelowcollision(B, current))
              	B->move("down", current);        	
        	}
        	B->boardadd(B, current);
         cout << *B;
         cout << *next;
      }
      else if(command == "clockwise") {
         for(int i = 0; i < times; i++) {
            B->boardremove(B, current);
          	B->move("clockwise", current);
          	if(B->checkcollision(B, current)) //In case the rotation goes over existing blocks
           	   B->move("counterclockwise", current);
            B->boardadd(B, current);
         }
         cout << *B;
         cout << *next;
      }
      else if(command == "counterclockwise") {
         for(int i = 0; i < times; i++) {
            B->boardremove(B, current);
          	B->move("counterclockwise", current);
           	if(B->checkcollision(B, current)) //In case the rotation goes over existing blocks
               B->move("clockwise", current);
           	B->boardadd(B, current);
         }
         cout << *B;
         cout << *next;
      }
      else if(command == "drop") {
         for(int i = 0; i < times; i++) {
            B->boardremove(B, current);
            while(!B->checkbelowcollision(B, current)) { //Repeat down command
               B->move("down", current);
            }
            B->boardadd(B, current);
            B->clearline();
            current = next; //Gets block from next
            if(B->checkcollision(B, current)) { //If there's no more space left
               highscore = B->returnscore(); //Save highscore
               delete B; //Delete board and clears the old blocks
               B = new Board(); //Makes a new one
               B->assignscore(highscore); //Reassigns highscore
               B->graphicstate = graphicstate;
               B->boardwindow = boardwindow;
               B->restart(); //Restarts the board if there's no space to put the next block
            }
            B->boardadd(B, current); //Updates the board with position of current block
            type = B->nextblock(zero);
            next = B->createblock(type, boardwindow, sidewindow);
         }
         cout << *B;
         cout << *next;
      }
      else if(command == "levelup") {
       	for (int i = 0; i < times; i++) {
        		B->levelup();
         }
      }
      else if(command == "leveldown") {
         for (int i = 0; i < times; i++) {
         	B->leveldown();
         }
      }
      else if(command == "restart") {
         B->boardremove(B, current);
         B->restart();
         delete current;
         highscore = B->returnscore();
         delete B;
         B = new Board();
         B->graphicstate = graphicstate;
         B->assignscore(highscore);
         B->boardwindow = boardwindow;
         current = next; //Gets block from next
         if(B->checkcollision(B, current))
            B->restart(); //Restarts the board if there's no space to put the next block
         B->boardadd(B, current); //Updates the board with position of current block
         type = B->nextblock(zero);
         next = B->createblock(type, boardwindow, sidewindow);
         cout << *B;
         cout << *next;
      }
      else
         cout << "Invalid command" << endl;
   }
   delete next; //Deletes the next block if not used
}

int main(int argc, char *argv[]) {
   Board *B;
	B = new Board(); //Create new board
	Xwindow *boardwindow; //Xwindow for main blocks
   Xwindow *sidewindow; //Xwindow for side blocks
	bool graphicstate = 1; //Used to check if -text is used
	for(int i = 1; i < argc; i++) {
      if(string(argv[i]) == "-text")
   	   // Just call the test based version. that is, avoid the x window graphic diaplay
         graphicstate = 0;
	   else if(string(argv[i]) == "-seed") {
		   // update the seed
		   int count = 0;
		   count = atoi(argv[i+1]);
		   B->Change(count);  // update the generator
		}
	}
	if(graphicstate) { //If graphics are enabled, create the Xwindows
   	boardwindow = new Xwindow(300, 600);
      sidewindow = new Xwindow(120, 120);
   	B->boardwindow = boardwindow;
   }
   TrieNode *node = new TrieNode; //TrieNode used for command shortcuts
	preloadshortcuts(node); //Preloads the node with the shortcuts
	executecommands(cin, B, node, boardwindow, sidewindow, graphicstate); //Executes commands
	releasememory(node); //Deletes the shortcuts
	if(graphicstate) { //Deletes the windows if graphics were enabled
   	delete boardwindow;
	   delete sidewindow;
	}
   return 0;
}
