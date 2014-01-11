#include "kdtree.hpp"

KDTree::KDTree(int k, float* input, int size) {
  int index=0;
  dim = k;
  head = new tnode;
  head->data = new float[k];
  head->leftL = nullptr;
  head->rightL = nullptr;
  for (int i=0; i<k;i++) {
    head->data[index] = input[index];
    index++;
  }
  for (int i=1;i<size;i++) {
    //make new node
    tnode* node = new tnode;
    node->data = new float[k];
    node->leftL = nullptr;
    node->rightL = nullptr;
    for (int j=0;j<k;j++) {
      node->data[index] = input[index];
      index++;
    }
    addPoint(node);
  }

}

KDTree::~KDTree() {
}

void KDTree::findNearestNeighbour(int k, float* s_data)
{
  tnode* currentBest = head;
  tnode* tmp = head;

}

// private
void KDTree::addPoint(tnode* node)
{
  int level = 0;
  // go thru the tree iteratively to find our spot
  // head always exists
  tnode* tmp = head;
  while(true) {
    // check against current tmp and move towards, if null.
    // Well thats where we add
    if (level == dim) {
      level = 0;
    }
    if (tmp->data[level] < node->data[level]) // "new data" is bigger
    {
      if (tmp->rightL != nullptr)
        tmp = tmp->rightL;
      else {
        tmp->rightL = node;
        break;
      }
    } else {
      if (tmp->leftL != nullptr)
        tmp = tmp->leftL;
      else {
        tmp->leftL = node;
        break;
      }
    }
    level++;
  }
}
