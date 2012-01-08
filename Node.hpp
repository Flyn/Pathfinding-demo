#ifndef __NODE_H__
#define __NODE_H__

#include <math.h>

using namespace std;

class Node {
  
protected:
  int x;
  int y;
  int gcost;
  int hcost;
  int fcost;
  Node* parent;

public:

  Node(Node* p,int mx, int my,int xtarget,int ytarget);
  Node(Node* p,int mx, int my,int xtarget,int ytarget,int g);
  
  int get_x();
  int get_y();
  int get_gcost();
  int get_hcost();
  int get_fcost();
  int get_distance(int nx,int ny);
  Node* get_parent();
  void set_x(int n);
  void set_y(int n);

};

#endif
