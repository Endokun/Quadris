#include <iostream>
#include "square.h"
#include "block.h"
using namespace std;

//Default constructor
Square::Square() {
   state = 0;
   bp = NULL;
}

Square::~Square() {
}

//Draws block on board
void Square::draw() {
   if(bp != NULL) {
      bp->board->fillRectangle(ycord*30, xcord*30+60, 30, 30, Xwindow::Black);
      bp->board->fillRectangle(ycord*30+1, xcord*30+61, 28, 28, bp->colour);
   }
}

//Undraws blocks
void Square::undraw() {
   if(bp != NULL)
      bp->board->fillRectangle(ycord*30, xcord*30+60, 30, 30, Xwindow::White);
}

//Sets the coordinates for the square as well as stores the level
//the square appears in and what type of block it belongs to
void Square::initsquare(int x, int y, int l, char t) {
   xcord = x;
   ycord = y;
   level = l;
   type = t;
   state = 1;
}

//Assigns a square pointing to a block
void Square::attachbp(Block *b) {
   bp = b;
}
//Unassigns the block
void Square::detachbp() {
   bp = NULL;
}

//Gives coordinates to change the position of the square
void Square::changecord(int a, int b) {
   xcord = a;
   ycord = b;
}

//Returns the value of xcord
int Square::xpos() {
   return xcord;
}

//Returns the vale of ycord
int Square::ypos() {
   return ycord;
}

//Returns the current state of the Square
bool Square::currentstate() {
   return state;
}

//Returns the type of the Square
char Square::currenttype() {
   return type;
}

//Returns the Square's level
int Square::currentlevel() {
   return level;
}

//Changes whether or not the Square exists or not
void Square::statechange(bool s) {
   state = s;
}

//Changes the type of square it is
void Square::typechange(char c) {
   type = c;
}

//Changes the level
void Square::levelchange(int l) {
   level = l;
}

//Prints out the square if it's alive
ostream &operator<<(ostream &out, Square s) {
   if(s.currentstate())
      out << s.currenttype();
   else
      out << " ";
   return out;
}
