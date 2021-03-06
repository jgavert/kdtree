#ifndef _KDTREE_
#define _KDTREE_
#include "node.hpp"
#include <deque>
#include <iostream>

class KDTree
{
public:
  KDTree(int k, float* input, int size);
  ~KDTree();
  float* NN(float* s_data);
  void print();

private:
  tnode* recNN(float*, tnode*, int);
  void printlevel(std::deque<tnode*> nodes);
  int dim;
  void pn(tnode* node);
  void addPoint(tnode* node);
  float dist(tnode* n1, tnode* n2);
  float distS(tnode* n1, float* data);
  tnode* head;
};

#endif
