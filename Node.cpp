#include "Node.hpp"

Node::Node(Node* p, int mx, int my, int xtarget,int ytarget){

  parent=p;
  x=mx;
  y=my;
  gcost=0;
  hcost=get_distance(xtarget,ytarget)*10;
  fcost=gcost+hcost;
}

Node::Node(Node* p, int mx, int my, int xtarget,int ytarget,int g){

  parent=p;
  x=mx;
  y=my;
  gcost=g;
  hcost=get_distance(xtarget,ytarget)*10;
  fcost=gcost*hcost;
}

int Node::get_x(){

  return x;

}

int Node::get_y(){

  return y;

}

int Node::get_gcost(){

  return gcost;

}

int Node::get_hcost(){

  return hcost;

}

int Node::get_fcost(){

  return fcost;

}

int Node::get_distance(int nx, int ny){

  return (int)sqrt((nx-x)*(nx-x)+(ny-y)*(ny-y));

}

Node* Node::get_parent(){

  return parent;

}

void Node::set_x(int n){

  x=n;

}

void Node::set_y(int n){

  y=n;

}
