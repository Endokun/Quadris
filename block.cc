#include <iostream>
#include "block.h"
#include <math.h>
using namespace std;

Block::Block(int lvl, char type, Xwindow *mb, Xwindow *sb, bool gs) {
   level = lvl;
   c = type;
   orientation = 0;
   board = mb;
   sidewindow = sb;
   numsquares = 4;
   graphicstate = gs;
}

Block::~Block() {
   for(int i = 0; i < 4; i++) {
      delete pos[i];
   }
}

//Prints out individual blocks
ostream& operator<<(ostream &out, const Block &b) {
   if(b.graphicstate) {
      b.sidewindow->fillRectangle(0,0, 500, 500, Xwindow::White);
      b.sidewindow->drawString(5, 15, "Next Block:", Xwindow::Black);
      b.sidewindow->fillRectangle(0, 20, 300, 2, Xwindow::Black);
      b.sidewindow->fillRectangle(b.pos[0]->ypos()*30, b.pos[0]->xpos()*30-30, 30, 30, Xwindow::Black);
      b.sidewindow->fillRectangle(b.pos[0]->ypos()*30+1, b.pos[0]->xpos()*30-29, 28, 28, b.colour);
      b.sidewindow->fillRectangle(b.pos[1]->ypos()*30, b.pos[1]->xpos()*30-30, 30, 30, Xwindow::Black);
      b.sidewindow->fillRectangle(b.pos[1]->ypos()*30+1, b.pos[1]->xpos()*30-29, 28, 28, b.colour);
      b.sidewindow->fillRectangle(b.pos[2]->ypos()*30, b.pos[2]->xpos()*30-30, 30, 30, Xwindow::Black);
      b.sidewindow->fillRectangle(b.pos[2]->ypos()*30+1, b.pos[2]->xpos()*30-29, 28, 28, b.colour);
      b.sidewindow->fillRectangle(b.pos[3]->ypos()*30, b.pos[3]->xpos()*30-30, 30, 30, Xwindow::Black);
      b.sidewindow->fillRectangle(b.pos[3]->ypos()*30+1, b.pos[3]->xpos()*30-29, 28, 28, b.colour);
   }
   if(b.c == 'I') {
      out << "IIII" << endl;
   }
   else if(b.c == 'J') {
      out << "J  " << endl;
      out << "JJJ" << endl;
   }
   else if(b.c == 'L') {
      out << "  L" << endl;
      out << "LLL" << endl;
   }
   else if(b.c == 'O') {
      out << "OO" << endl;
      out << "OO" << endl;
   }
   else if(b.c == 'S') {
      out << " SS" << endl;
      out << "SS " << endl;
   }
   else if(b.c == 'Z') {
      out << "ZZ " << endl;
      out << " ZZ" << endl;
   }
   else if(b.c == 'T') {
      out << "TTT" << endl;
      out << " T " << endl;
   }
   else
      out << "Something went wrong here, invalid block" << endl;
   return out;
}

//Constructor for I blocks
I::I(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'I', m, s, gs) {
   //Intial position of the block (top left of the board)
   pos[0] = new Square; //Done so the block intially looks like: IIII
   pos[0]->initsquare(3,0,lvl,c);
   pos[1] = new Square;
   pos[1]->initsquare(3,1,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(3,2,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(3,3,lvl,c);
   originx = 3;
   originy = 0;
   colour = 2; //Red
}


//Deconstructor for I blocks
I::~I() {
}

//Moves the block to the left
void I::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() - 1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool I::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void I::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool I::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void I::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool I::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void I::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void I::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void I::clockwise() {
   double const pi = 4*atan(1);
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)), //Using rotation matrix
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
      if(pos[i]->xpos() > 0)
         pos[i]->changecord(-pos[i]->xpos(), -pos[i]->ypos()); //Adjustments
   }
   unshift();
}

//Rotates the block counterclockwise
void I::counterclockwise() {
   clockwise(); //Since the I block only has 2 possible positions, vertical and horizontal
}

//Returns block type
char I::blocktype() {
   return c;
}

/////////////////////////////////////////////////////////////

//Constructor for J blocks
J::J(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'J', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so the block is initially like: J
   pos[0]->initsquare(3,0,lvl,c);  //                          JJJ
   pos[1] = new Square;
   pos[1]->initsquare(4,0,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(4,1,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,2,lvl,c);
   originx = 4;
   originy = 0;
   colour = 3; //Green
}

//Deconstructor for J blocks
J::~J() {
}

//Moves the block to the left
void J::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() - 1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool J::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void J::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool J::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void J::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool J::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void J::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void J::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void J::clockwise() {
   double const pi = 4*atan(1);
   orientation = orientation + 90;
   if(orientation == 360)
      orientation = 0;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 2,pos[j]->ypos());
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 1,pos[j]->ypos());
      }
   }
   unshift();
}

//Rotates the block counterclockwise
void J::counterclockwise() {
   double const pi = 4*atan(1);
   if(orientation == 0)
      orientation = 360;
   orientation = orientation - 90;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord(-(pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         -(pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(), pos[j]->ypos() + 1);
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(), pos[j]->ypos() + 2);
      }
   }
   unshift();
}

char J::blocktype() {
   return c;
}

/////////////////////////////////////////////////////////////

//Constructor for L blocks
L::L(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'L', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so initially the block looks like:    L
   pos[0]->initsquare(3,2,lvl,c); //                               LLL
   pos[1] = new Square;
   pos[1]->initsquare(4,0,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(4,1,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,2,lvl,c);
   originx = 4;
   originy = 0;
   colour = 4; //Blue
}

//Deconstructor for L blocks
L::~L() {
}

//Moves the block to the left
void L::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() - 1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool L::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void L::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool L::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void L::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool L::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void L::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void L::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void L::clockwise() {
   double const pi = 4*atan(1);
   orientation = orientation + 90;
   if(orientation == 360)
      orientation = 0;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 2,pos[j]->ypos());
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 1,pos[j]->ypos());
      }
   }
   unshift();
}

//Rotates the block counterclockwise
void L::counterclockwise() {
   double const pi = 4*atan(1);
   if(orientation == 0)
      orientation = 360;
   orientation = orientation - 90;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((-pos[i]->xpos()*cos(pi/2) + pos[i]->ypos()*sin(pi/2)),
                         (-pos[i]->xpos()*sin(pi/2) + pos[i]->ypos()*cos(pi/2)));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(), pos[j]->ypos() + 1);
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(), pos[j]->ypos() + 2);
      }
   }
   unshift();
}

char L::blocktype() {
   return c;
}
/////////////////////////////////////////////////////////////

//Constructor for O blocks
O::O(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'O', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so the block intially appears like: 00
   pos[0]->initsquare(3,0,lvl,c);  //                              00
   pos[1] = new Square;
   pos[1]->initsquare(3,1,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(4,0,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,1,lvl,c);
   colour = 5; //Cyan
}

//Deconstructor for O blocks
O::~O() {
}

//Moves the block to the left
void O::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos()-1);
      }
   }
}

//Checks to see if there's any space below the block for it to go left
bool O::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void O::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
   }
}

//Checks to see if there's any space below the block for it to go right
bool O::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void O::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
   }
}

//Checks to see if there's any space below the block for it to go down
bool O::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//These are useless functions since O blocks don't change at all
void O::shift() {}
void O::unshift() {}
void O::clockwise() {}
void O::counterclockwise() {}

char O::blocktype() {
   return c;
}
/////////////////////////////////////////////////////////////

//Constructor for S blocks
S::S(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'S', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so the block intially appears like:   SS
   pos[0]->initsquare(3,1,lvl,c); //                                SS
   pos[1] = new Square;
   pos[1]->initsquare(3,2,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(4,0,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,1,lvl,c);
   originx = 4;
   originy = 0;
   colour = 6; //Yellow
}

//Deconstructor for S blocks
S::~S() {
}

//Moves the block to the left
void S::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos()-1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool S::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void S::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool S::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void S::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool S::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void S::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void S::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void S::clockwise() {
   double const pi = 4*atan(1);
   orientation = orientation + 90;
   if(orientation == 360)
      orientation = 0;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
      if(orientation == 90 || orientation == 270)
         pos[i]->changecord(pos[i]->xpos() - 2, pos[i]->ypos());
      else
         pos[i]->changecord(pos[i]->xpos() - 1, pos[i]->ypos());
   }
   unshift();
}

//Rotates the block counterclockwise
void S::counterclockwise() {
   clockwise(); //Since the block only has 2 possible positions
}

char S::blocktype() {
   return c;
}
/////////////////////////////////////////////////////////////

//Constructor for Z blocks
Z::Z(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'Z', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so the block intially appears like: ZZ
   pos[0]->initsquare(3,0,lvl,c); //                                ZZ
   pos[1] = new Square;
   pos[1]->initsquare(3,1,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(4,1,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,2,lvl,c);
   originx = 4;
   originy = 0;
   colour = 7; //Magenta
}

//Deconstructor for Z blocks
Z::~Z() {
}

//Moves the block to the left
void Z::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() - 1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool Z::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void Z::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool Z::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void Z::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool Z::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void Z::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void Z::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void Z::clockwise() {
   double const pi = 4*atan(1);
   orientation = orientation + 90;
   if(orientation == 360)
      orientation = 0;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
      if(orientation == 90 || orientation == 270)
         pos[i]->changecord(pos[i]->xpos() - 2, pos[i]->ypos());
      else
         pos[i]->changecord(pos[i]->xpos() - 1, pos[i]->ypos());
   }
   unshift();
}

//Rotates the block counterclockwise
void Z::counterclockwise() {
   clockwise(); //Since the block only has 2 possible positions
}

char Z::blocktype() {
   return c;
}
/////////////////////////////////////////////////////////////

//Constructor for T blocks
T::T(int lvl, Xwindow *m, Xwindow *s, bool gs) : Block(lvl, 'T', m, s, gs) {
   //Intial position of the block (top left of the board)   
   pos[0] = new Square; //Done so the block intially appears like: TTT
   pos[0]->initsquare(3,0,lvl,c); //                                T
   pos[1] = new Square;
   pos[1]->initsquare(3,1,lvl,c);
   pos[2] = new Square;
   pos[2]->initsquare(3,2,lvl,c);
   pos[3] = new Square;
   pos[3]->initsquare(4,1,lvl,c);
   originx = 4;
   originy = 0;
   colour = 8; //Orange
}

//Deconstructor for T blocks
T::~T() {
}

//Moves the block to the left
void T::left() {
   if(!checkleft()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() - 1);
      }
      originy--;
   }
}

//Checks to see if there's any space below the block for it to go left
bool T::checkleft() {
   if(pos[0]->ypos() == 0 || pos[1]->ypos() == 0 || pos[2]->ypos() == 0 || pos[3]->ypos() == 0)
      return true;
   else
      return false;
}

//Moves the block to the right
void T::right() {
   if(!checkright()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos(),pos[i]->ypos() + 1);
      }
      originy++;
   }
}

//Checks to see if there's any space below the block for it to go right
bool T::checkright() {
   if(pos[0]->ypos() == 9 || pos[1]->ypos() == 9 || pos[2]->ypos() == 9 || pos[3]->ypos() == 9)
      return true;
   else
      return false;
}

//Moves block down
void T::down() {
   if(!checkbelow()) {
      for(int i = 0; i < 4; i++) {
         pos[i]->changecord(pos[i]->xpos() + 1, pos[i]->ypos());
      }
      originx++;
   }
}

//Checks to see if there's any space below the block for it to go down
bool T::checkbelow() {
   if(pos[0]->xpos() == 17 || pos[1]->xpos() == 17 || pos[2]->xpos() == 17 || pos[3]->xpos() == 17)
      return true;
   else
      return false;
}

//Shifts the block for rotational purposes
void T::shift() {
      pos[0]->changecord(-(pos[0]->xpos() - originx), -(pos[0]->ypos() - originy));
      pos[1]->changecord(-(pos[1]->xpos() - originx), -(pos[1]->ypos() - originy));
      pos[2]->changecord(-(pos[2]->xpos() - originx), -(pos[2]->ypos() - originy));
      pos[3]->changecord(-(pos[3]->xpos() - originx), -(pos[3]->ypos() - originy));
}

//Shifts the block back to its original position after rotation
void T::unshift() {
      pos[0]->changecord(pos[0]->xpos() + originx, pos[0]->ypos() + originy);
      pos[1]->changecord(pos[1]->xpos() + originx, pos[1]->ypos() + originy);
      pos[2]->changecord(pos[2]->xpos() + originx, pos[2]->ypos() + originy);
      pos[3]->changecord(pos[3]->xpos() + originx, pos[3]->ypos() + originy);
}

//Rotates the block clockwise
void T::clockwise() {
   double const pi = 4*atan(1);
   orientation = orientation + 90;
   if(orientation == 360)
      orientation = 0;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord((pos[i]->xpos()*cos(pi/2) - pos[i]->ypos()*sin(pi/2)),
                         (pos[i]->xpos()*sin(pi/2) - pos[i]->ypos()*cos(pi/2)));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 2,pos[j]->ypos());
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos() - 1,pos[j]->ypos());
      }
   }
   unshift();
}

//Rotates the block counterclockwise
void T::counterclockwise() {
   double const pi = 4*atan(1);
   if(orientation == 0)
      orientation = 360;
   orientation = orientation - 90;
   shift();
   for(int i = 0; i < 4; i++) {
      pos[i]->changecord(-pos[i]->xpos()*cos(pi/2) + pos[i]->ypos()*sin(pi/2), 
                         -pos[i]->xpos()*sin(pi/2) + pos[i]->ypos()*cos(pi/2));
   }
   if(orientation == 90 || orientation == 270) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(),pos[j]->ypos() + 1);
      }
   }
   else if(orientation == 0 || orientation == 180) {
      for(int j = 0; j < 4; j++) {
         pos[j]->changecord(pos[j]->xpos(),pos[j]->ypos() + 2);
      }
   }
   unshift();
}

char T::blocktype() {
   return c;
}
