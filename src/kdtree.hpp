#ifndef _KDTREE_
#define _KDTREE_
#include "node.hpp"
#include <deque>

class KDTree
{
public:
  KDTree(int k, float* input, int size);
  ~KDTree();
  float* NN(float* s_data);

private:
  int dim;
  void addPoint(tnode* node);
  float dist(tnode* n1, tnode* n2);
  float distS(tnode* n1, float* data);
  tnode* head;
};

#endif
