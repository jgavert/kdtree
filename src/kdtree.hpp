#ifndef _KDTREE_
#define _KDTREE_
#include "node.hpp"
#include <cmath>

class KDTree
{
public:
  KDTree(int k, float* input, int size);
  ~KDTree();
  void findNearestNeighbour();

private:
  int dim;
  void addPoint(tnode* node);
  float dist(tnode* n1, tnode* n2);
  tnode* head;
};

#endif
