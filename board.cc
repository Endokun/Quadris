#include <iostream>
#include <sstream>
#include "board.h"
using namespace std;

//Constructor
Board::Board() {
   for(int i = 0; i < 18; i++) {
      for(int j = 0; j < 10; j++) {
         board[i][j].changecord(i,j);
      }
   }
   level = 1; //Initially start on level 1
   currentscore = 0;
   highscore = 0;
   graphicstate = 1;
}

//Destructor
Board::~Board() {
   for(int i = 0; i < 18; i++) { //Goes through all the rows from top to bottom
      for(int j = 0; j < 10; j++) { //Go through each column on that row
         if(board[i][j].bp != NULL) {
            if(board[i][j].bp->numsquares == 1) { //If there's only one square left in the block, delete it
               delete board[i][j].bp; //Delete the block
            }
            else
               board[i][j].bp->numsquares--;
         }
      }
   }
}

//Checks if row n is filled
bool Board::checkline(int n) {
   for(int i = 0; i < 10; i++) {
      if(!board[n][i].currentstate()) { //If there's at least one square on the line that's not active
         return false;
      }
   }
   return true;
}

//Shifts the lines above the int n down
void Board::lineshift(int n) {
   for(int i = n; i >= 0; i--) {
      for(int j = 0; j < 10; j++) {
         if(board[i][j].currentstate()) {
            if(graphicstate)
               board[i][j].undraw(); //Undraws the block
            board[i+1][j].levelchange(board[i][j].currentlevel()); //Inherits the stats from the upper square
            board[i+1][j].typechange(board[i][j].currenttype());
            board[i+1][j].statechange(board[i][j].currentstate());
            board[i+1][j].bp = board[i][j].bp;
            if(graphicstate) 
               board[i+1][j].draw();
            board[i][j].statechange(0); //Disables the upper square
            board[i][j].bp = NULL;
         }
         else
            board[i+1][j].bp = NULL; //No squares above
      }
   }
}

//Removes all filled lines and calculates score
void Board::clearline() {
   int numclearedlines = 0; //Keeps track if there's multiple lines that are cleared at once
   int squarescore = 0; //Keeps track of points
   for(int i = 0; i < 18; i++) { //Goes through all the rows from top to bottom
      if(checkline(i)) { //Checks if the row i is filled with squares
         numclearedlines++; //Increment for score purposes
         for(int j = 0; j < 10; j++) { //Go through each column on that row
            if(board[i][j].bp != NULL) {
               if(graphicstate)
                  board[i][j].undraw();
               board[i][j].statechange(0); //Turn off the square
               board[i][j].bp->numsquares--; //Decrease the number of squares from the block associated
               if(board[i][j].bp->numsquares == 0) { //If there's no more squares for a given block
                  squarescore = squarescore + (board[i][j].bp->level + 1)*(board[i][j].bp->level + 1);
                  delete board[i][j].bp; //Delete the block
               }
            }
         }
         lineshift(i-1); //Shifts all the lines above down
         currentscore = currentscore + squarescore + (numclearedlines + level)*(numclearedlines + level); //Calculates score
         if(currentscore >= highscore)
            highscore = currentscore;
      }
   }
}

//For random generation of blocks
void Board::Change(int n) {
	newp.seed(n);
}

//Creates a block
Block *Board::createblock(char type, Xwindow *mainboard, Xwindow *sidewindow) {
   Block *b;
   if(type == 'I')
      b = new I(level,mainboard,sidewindow,graphicstate);
   else if (type == 'J')
      b = new J(level,mainboard,sidewindow,graphicstate);
   else if (type == 'L')
      b = new L(level,mainboard,sidewindow,graphicstate);
   else if (type == 'O')
      b = new O(level,mainboard,sidewindow,graphicstate);
   else if (type == 'S')
      b = new S(level,mainboard,sidewindow,graphicstate);
   else if (type == 'Z')
      b = new Z(level,mainboard,sidewindow,graphicstate);
   else if (type == 'T')
      b = new T(level,mainboard,sidewindow,graphicstate);
   for(int i = 0; i < 4; i++) { //Makes each square point to the block
      b->pos[i]->attachbp(b);
   }
   return b;
}

//Dictates what the next block should be
char Board::nextblock(istream &blocktype) {
   char type;
   if(level == 0)
      blocktype >> type;
   else if(level == 1) {
      int ran = newp(1,12);
		if (ran == 1)
			type = 'S';
		if (ran == 2)
			type = 'Z';
		if (ran == 3 || ran == 4)
			type = 'I';
		if (ran == 5 || ran == 6)
			type = 'J';
		if (ran == 7 || ran == 8)
			type = 'L';
		if (ran == 9 || ran == 10)
			type = 'O';
		if (ran == 11 || ran == 12)
			type = 'T';
   }
	else if(level == 2) {
		int newnum = newp(1, 7);
		if (newnum == 1)
			type = 'I';
		else if (newnum == 2)
			type = 'J';
		else if (newnum == 3)
			type = 'L';
		else if (newnum == 4)
			type = 'O';
		else if(newnum == 5)
			type = 'S';
		else if (newnum == 6)
			type = 'Z';
		else if (newnum == 7)
			type = 'T';
	}
	else if (level == 3) {
		int randomnum = newp(1,9);
		if (randomnum == 1 || randomnum == 2)
			type = 'S';
		else if (randomnum == 3 || randomnum == 4)
			type = 'Z';
		else if (randomnum == 5)
			type = 'I';
		else if (randomnum == 6)
			type = 'J';
		else if (randomnum == 7)
			type = 'L';
		else if (randomnum == 8)
			type = 'O';
		else if (randomnum == 9)
			type = 'T';
	}
	return type;
}

//Updates the board with the current position of the block
void Board::boardadd(Board *B, Block *b) {
   B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].typechange(b->blocktype()); //Gives blocktype to the board square
   B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].statechange(1); //Turns on the board square
   B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].attachbp(b); //Gives the pointer to the board square
   if(graphicstate)
      B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].draw(); //Draw the square on the board
   B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].typechange(b->blocktype());
   B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].statechange(1);
   B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].attachbp(b);
   if(graphicstate)
      B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].draw();
   B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].typechange(b->blocktype());
   B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].statechange(1);
   B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].attachbp(b);
   if(graphicstate)
      B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].draw();
   B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].typechange(b->blocktype());
   B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].statechange(1);
   B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].attachbp(b);
   if(graphicstate)
      B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].draw();
}

//Removes the block from the board and makes those squares dead
void Board::boardremove(Board *B, Block *b) {
   if(graphicstate)
      B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].undraw(); //Undraws the board square
   B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].statechange(0); //Disable board square
   B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].bp = NULL;
   if(graphicstate)
      B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].undraw();
   B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].statechange(0);
   B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].bp = NULL;
   if(graphicstate)
      B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].undraw();
   B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].statechange(0);
   B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].bp = NULL;
   if(graphicstate)
      B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].undraw();
   B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].statechange(0);
   B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].bp = NULL;
}

//Moves a block based on input
void Board::move(string command, Block *b) { //Moves a block based on input
   if(command == "left")
      b->left();
   else if(command == "right")
      b->right();
   else if(command == "down")
      b->down();
   else if(command == "clockwise")
      b->clockwise();
   else if(command == "counterclockwise")
      b->counterclockwise();
}

//Makes sure that the block is not currently over existing blocks, mainly used to check rotation
bool Board::checkcollision(Board *B, Block *b) {
   if(B->board[b->pos[0]->xpos()][b->pos[0]->ypos()].currentstate() ||
      B->board[b->pos[1]->xpos()][b->pos[1]->ypos()].currentstate() ||
      B->board[b->pos[2]->xpos()][b->pos[2]->ypos()].currentstate() ||
      B->board[b->pos[3]->xpos()][b->pos[3]->ypos()].currentstate())
      return true;
   else 
      return false;
}

//Makes sure that blocks don't go through each other or the left wall
bool Board::checkleftcollision(Board *B, Block *b) {
   if(!b->checkleft()) { //Checks to make sure that the block isn't already touching the left wall
      if(B->board[b->pos[0]->xpos()][b->pos[0]->ypos()-1].currentstate() ||
         B->board[b->pos[1]->xpos()][b->pos[1]->ypos()-1].currentstate() ||
         B->board[b->pos[2]->xpos()][b->pos[2]->ypos()-1].currentstate() ||
         B->board[b->pos[3]->xpos()][b->pos[3]->ypos()-1].currentstate())
         return true; //Yes, it will collide with another block
      else
         return false;
   }
   else
      return true; //It will collide with the bottom
}

//Makes sure that blocks don't go through each other or the right wall
bool Board::checkrightcollision(Board *B, Block *b) {
   if(!b->checkright()) { //Checks to make sure that the block isn't already touching the right wall
      if(B->board[b->pos[0]->xpos()][b->pos[0]->ypos()+1].currentstate() ||
         B->board[b->pos[1]->xpos()][b->pos[1]->ypos()+1].currentstate() ||
         B->board[b->pos[2]->xpos()][b->pos[2]->ypos()+1].currentstate() ||
         B->board[b->pos[3]->xpos()][b->pos[3]->ypos()+1].currentstate())
         return true; //Yes, it will collide with another block
      else
         return false;
   }
   else
      return true; //It will collide with the bottom
}

//Makes sure that blocks don't go through each other or the ground
bool Board::checkbelowcollision(Board *B, Block *b) {
   if(!b->checkbelow()) { //Checks to make sure that the block isn't already touching the bottom
      if(B->board[b->pos[0]->xpos()+1][b->pos[0]->ypos()].currentstate() ||
         B->board[b->pos[1]->xpos()+1][b->pos[1]->ypos()].currentstate() ||
         B->board[b->pos[2]->xpos()+1][b->pos[2]->ypos()].currentstate() ||
         B->board[b->pos[3]->xpos()+1][b->pos[3]->ypos()].currentstate())
         return true; //Yes, it will collide with another block
      else
         return false;
   }
   else
      return true; //It will collide with the bottom
}

//void Board::checkline(); //Checks if there are any filled lines in the grid
      
void Board::restart() { //Restarts the game
   currentscore = 0;
   for(int i = 0; i < 18; i++) {
      for(int j = 0; j < 10; j++) {
         board[i][j].statechange(0);
         if(graphicstate)
            boardwindow->fillRectangle(0,0, 2000, 2000, Xwindow::White);
      }
   }
}

//Increases level
int Board::levelup() {
   if(level < 3)
      level++;
   return level;
}

//Decreases level
int Board::leveldown() {
   if(level > 0)
      level--;
   return level;
}
//Assigns highscore
void Board::assignscore(int hs) {
   highscore = hs;
}

//Returns highscore
int Board::returnscore() {
   return highscore;
}

//Prints out the board
ostream& operator<<(ostream &out, Board &B) {
   if(B.graphicstate) { //If graphics are enabled, draw the stats
      B.boardwindow->fillRectangle(0, 0, 300, 60, Xwindow::White);
      stringstream ss;
      ss << B.level;
      
      B.boardwindow->drawString(5, 15, "Level:", Xwindow::Black);
      B.boardwindow->drawString(70, 15, ss.str(), Xwindow::Black);
      ss.str("");
      ss << B.currentscore;
      
      B.boardwindow->drawString(5, 33, "Score:", Xwindow::Black);
      B.boardwindow->drawString(70, 33, ss.str(), Xwindow::Black);
      ss.str("");
      ss << B.highscore;
      
      B.boardwindow->drawString(5, 50, "Hi Score:", Xwindow::Black);
      B.boardwindow->drawString(70, 50, ss.str(), Xwindow::Black);
      
      B.boardwindow->fillRectangle(0, 60, 300, 2, Xwindow::Black);
   }
   out << "Level: " << B.level << endl;   
   out << "Score: " << B.currentscore << endl;
   out << "Hi Score: " << B.highscore << endl;
   out << "----------" << endl;
   for(int i = 0; i < 18; i++) {
      for(int j = 0; j < 10; j++) {
         out << B.board[i][j]; //Outputs each block
      }
      out << endl;
   }
   
   out << "----------" << endl;
   out << "Next:" << endl;
   
   return out;
}
