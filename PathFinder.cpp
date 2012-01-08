#include "PathFinder.hpp"

PathFinder::PathFinder(){

}


PathFinder::~PathFinder(){

  clearNodes();

}

void PathFinder::genPath(int fromx, int fromy, int tox, int toy){

  xtarget=tox;
  ytarget=toy;
  Node* start=new Node(NULL,fromx,fromy,xtarget,ytarget);
  Node* actual=start;
  sol=NULL;
  clearClosed();
  pushandclose(actual);
  found=0;
  while(found==0 && popFull()){
    actual=popOpen();
    putpixel(screen,actual->get_x(),actual->get_y(),makecol(0,255,0));
    if (isTarget(actual)){
      found++;
      sol=actual;
    }else
      setClosed(actual);
    pushandcloseadj(actual);
  }

}

void PathFinder::clearNodes(){

  while(popFull())
    delete popOpen();
  if (sol!=NULL)
    delete sol;
  destroy_bitmap(map);
}

void PathFinder::clearClosed(){

  int i;  int j;
  for (i=0;i<640;i++)
    for (j=0;j<480;j++)
      closed[i][j]=1;

}

int PathFinder::isWalkable(Node* node){

  if (node->get_x()<0 || node->get_y()<0 || node->get_x()>640 || node->get_y()>480)
    return 0;
  int value=getpixel(map,node->get_x(),node->get_y());
  int r= getr(value);
  int g= getg(value);
  int b= getb(value);
  if (r==0 && g==0 && b==0)
    return 1;
  else return 0;

}

int PathFinder::isValid(Node* node){

  if(isWalkable(node)){
    if (node->get_x()<0 || node->get_y()<0 || node->get_x()>=640 || node->get_y()>=480)
      return 0;
    else
      return closed[node->get_x()][node->get_y()];
  }
  else return 0;
  
}

int PathFinder::isTarget(Node* n){

  int i,j;

  for (i=-scale;i<=scale;i++)
    for (j=-scale;j<=scale;j++){
      if (n->get_x()==xtarget+i && n->get_y()==ytarget+j)
	return 1;
    }
  return 0;

}

void PathFinder::setClosed(Node* node){

  if (node->get_x()>=0 || node->get_y()>=0 || node->get_x()<640 || node->get_y()<480)
    closed[node->get_x()][node->get_y()]=0;

}

Node* PathFinder::popOpen(){

  Node* ret=openlist.front();
  openlist.pop_front();
  return ret;

}

void PathFinder::pushOpen(Node* node){

  openlist.push_front(node);
  openlist.sort(nearer);

}

int PathFinder::popFull(){

  return (!openlist.empty());

}

void PathFinder::pushandclose(Node* node){

  if (isValid(node)){
    pushOpen(node);
    setClosed(node);
  }

}

void PathFinder::pushandcloseadj(Node* node){

  int i,j;
  for (i=-scale;i<=scale;i+=scale)
    for (j=-scale;j<=scale;j+=scale){
      if (i==0 && j==0){}
      else
	if (i==j || i==-j) {
	  Node* n=new Node(node,node->get_x()+i,node->get_y()+j,xtarget,ytarget,node->get_gcost()+14);
	  pushandclose(n);
	}
	else {
	  Node* n=new Node(node,node->get_x()+i,node->get_y()+j,xtarget,ytarget,node->get_gcost()+10);
	  pushandclose(n);
	}
    }
  
}

void PathFinder::setScale(int s){

  scale=s;

}

void PathFinder::setMap(BITMAP* m){

  map=m;

}

BITMAP* PathFinder::getMap(){

  return map;

}

Node* PathFinder::solution(){

  return sol;

}

int nearer (Node* n1,Node* n2){

  if (n1->get_fcost()<n2->get_fcost())
    return 1;
  else return 0;
  
}

//

int main(int argc,char* argv[]){

  allegro_init();
  install_keyboard();
  install_mouse();
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  int x,y;
  PathFinder* path= new PathFinder();  
  path->setScale(1);
  if(argc==2)
  path->setMap(load_bitmap(argv[1],NULL));
  else path->setMap(load_bitmap("test.bmp",NULL));
  draw_sprite(screen,path->getMap(),0,0);
  show_mouse(screen);

  while(!(mouse_b & 1)){
    
  }

  x=mouse_x;y=mouse_y;

  while(!(mouse_b & 2)){
    
  }
  

  path->genPath(x,y,mouse_x,mouse_y);  
  Node* actual=path->solution();
  
  while (actual!=NULL){
    putpixel(screen,actual->get_x(),actual->get_y(),makecol(255,0,0));
    actual=actual->get_parent();
  }
  
  delete path;
  
  readkey();
}
END_OF_MAIN();
