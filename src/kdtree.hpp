#ifndef _KDTREE_
#define _KDTREE_
#include "node.hpp"

class KDTree
{
public:
  KDTree(int k, float* input, int size);
  ~KDTree();
  void findNearestNeighbour();

private:
  int dim;
  void addPoint(tnode* node);
  tnode* head;
};

#endif
