#include "kdtree.hpp"

KDTree::KDTree(int k, float* input, int size) {
  int index=0;
  dim = k;
  head = new tnode;
  head->data = new float[k];
  for (int i=0; i<k;i++) {
    node->data[index] = input[index];
    index++;
  }
  for (int i=1;i<size;i++) {
    //make new node
    tnode* node = new tnode;
    node->data = new float[k];
    for (int j=0;j<k;j++) {
      node->data[index] = input[index];
      index++;
    }
    addPoint(node)
  }

}

KDTree::~KDTree() {
}

void KDTree::findNearestNeighbour()
{
}

// private
void KDTree::addPoint(tnode* node)
{


}
