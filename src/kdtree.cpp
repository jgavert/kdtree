#include "kdtree.hpp"

KDTree::KDTree(int k, float* input, int size) {
  int index=0;
  dim = k;
  head = new tnode;
  head->data = new float[k];
  head->leftL = nullptr;
  head->rightL = nullptr;
  for (int i=0; i<k;i++) {
    head->data[i] = input[index];
    index++;
  }
  for (int i=1;i<size/k;i++) {
    //make new node
    tnode* node = new tnode;
    node->data = new float[k];
    node->leftL = nullptr;
    node->rightL = nullptr;
    for (int j=0;j<k;j++) {
      node->data[j] = input[index];
      index++;
    }
    addPoint(node);
  }

}

KDTree::~KDTree() {
}


float KDTree::dist(tnode* n1, tnode* n2)
{
  float sum = 0.f;
  for (int i=0;i<dim;i++) {
    sum += (n1->data[i] - n2->data[i]) * (n1->data[i] - n2->data[i]);
  }
  return sum;
}

float KDTree::distS(tnode* n1, float* data)
{
  float sum = 0.f;
  for (int i=0;i<dim;i++) {
    sum += (n1->data[i] - data[i]) * (n1->data[i] - data[i]);
  }
  return sum;
}


void KDTree::pn(tnode* node)
{
  for (int i=0;i<dim-1;i++) {
    std::cout << node->data[i] << " ";
  }
  std::cout << node->data[dim-1];
}


void KDTree::print()
{
  std::deque<tnode*> nodes;
  nodes.push_back(head);
  printlevel(nodes);
}

void KDTree::printlevel(std::deque<tnode*> nodes)
{
  bool hadreal = false;
  std::deque<tnode*> next;
  while(nodes.size() > 0) {
    tnode* tmp = nodes.front();
    nodes.pop_front();
    if (tmp != nullptr) {
      if (tmp->leftL != nullptr || tmp->rightL != nullptr)
        hadreal = true;

      next.push_back(tmp->leftL);
      next.push_back(tmp->rightL);
      std::cout << "[";
      pn(tmp);
      std::cout << "] ";
    } else { // print the nullptr
      std::cout << "[-] ";
      next.push_back(nullptr);
      next.push_back(nullptr);
    }
  }
  std::cout << std::endl;
  if (hadreal) {
    printlevel(next);
  }
}

float* KDTree::NN(float* s_data)
{
  tnode* curBest = nullptr;
  curBest = recNN(s_data, head, 0);
  return curBest->data;
}

tnode* KDTree::recNN(float* s_data, tnode* tmp, int level)
{
  //pn(tmp);
  //std::cout << std::endl;
  if (level == dim)
    level = 0;
  tnode* newbest = nullptr;
  if (tmp->data[level] < s_data[level]) // "new data" is bigger
  {
    if (tmp->rightL != nullptr)
      newbest = recNN(s_data, tmp->rightL, level+1);
  } else {
    if (tmp->leftL != nullptr)
      newbest = recNN(s_data, tmp->leftL, level+1);
  }
  if (newbest == nullptr)
    newbest = tmp;

  float distToBest = distS(newbest, s_data);
  float distToTmp = distS(tmp, s_data);
  if (distToTmp < distToBest) {
    newbest = tmp;
    distToBest = distToTmp;
    //std::cout << "New Best!\n";
  }
  /*
  std::cout << "I am: ";
  pn(tmp);
  std::cout << " And current best: ";
  pn(newbest);
  std::cout << std::endl;
*/
  // the "big if", checks if there could be better on the other side of the axis
  if (distToBest > (tmp->data[level] - s_data[level]) * (tmp->data[level] - s_data[level])) {
    //std::cout << "I want to go to another side." << std::endl;
    bool asd = false;

    if (tmp->data[level] < s_data[level])
    {
      if (tmp->leftL != nullptr) { // so we go to the opposite
        tmp = tmp->leftL;
        asd = true;
      }
    } else {
      if (tmp->rightL != nullptr) {// because the "big if" told us to do so
        tmp = tmp->rightL;
        asd = true;
      }
    }
    if (asd)
    {
      tnode* another = recNN(s_data, tmp, level++); // we go to the other branch
      if (distS(another, s_data) < distToBest)
        newbest = another;
    }
  }

  return newbest;
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
