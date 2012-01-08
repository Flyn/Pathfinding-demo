#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <list>
#include "Node.hpp"
#include <allegro.h>

class PathFinder {
  
protected:
  
  list<Node*> openlist;
  Node* sol;
  int closed[640][480];
  int xtarget;
  int ytarget;
  int found;
  int scale;
  BITMAP* map;

public:

  PathFinder();
  ~PathFinder();

  void genPath(int fromx, int fromy, int tox, int toy);
  void clearNodes();
  void clearClosed();
  int isWalkable(Node* node);
  int isValid(Node* node);
  int isTarget(Node* node);
  void setClosed(Node* node);
  Node* popOpen();
  int popFull();
  void pushOpen(Node* node);
  void pushandclose(Node* node);
  void pushandcloseadj(Node* node);
  void setScale(int s);
  void setMap(BITMAP* m);
  BITMAP* getMap();
  Node* solution();

};

int nearer(Node* n1,Node* n2);

#endif
