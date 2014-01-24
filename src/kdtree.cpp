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

float* KDTree::NN(float* s_data)
{
  tnode* currentBest = head;
  tnode* tmp = head;
  int level = 0;
  std::deque<tnode*> history;
  while(true) {
    history.push_back(tmp); // adding every node to be compared
    if (level == dim) {
      level = 0;
    }
    if (tmp->data[level] < s_data[level]) // "new data" is bigger
    {
      if (tmp->rightL != nullptr)
        tmp = tmp->rightL;
      else {
        break;
      }
    } else {
      if (tmp->leftL != nullptr)
        tmp = tmp->leftL;
      else {
        break;
      }
    }
    level++;
  }
  currentBest = history.back(); // pop the leaf node
  history.pop_back();
  float distToBest = distS(currentBest, s_data);
  level--; //since we start from before leaf node
  while(history.size() != 0) {
    tmp = history.back();
    history.pop_back();
    float distToTmp = distS(tmp, s_data);
    if (distToTmp < distToBest) {
      currentBest = tmp;
      distToBest = distToTmp;
    }
    if (distToBest > (tmp->data[level] - s_data[level]) * (tmp->data[level] - s_data[level])) {
      // compare the current best distance to distance to current hyperplane
      // or the you understand the above check. durr it's easy but hard to say the term
      // so, basically go to the another branch till end
      // opposite than where we came from... if we can
      if (tmp->data[level] < s_data[level]) // "new data" is bigger
      {
        if (tmp->leftL != nullptr)
          tmp = tmp->leftL;
      } else {
        if (tmp->rightL != nullptr)
          tmp = tmp->rightL;
      }
      //now we are in the right branch, gogo
      //This FAILS, since we cannot know if we already did this same thing.
      if (tmp != nullptr) {
        level++;
        while(true) {
          history.push_back(tmp); // adding every node to be compared
          if (level == dim) {
            level = 0;
          }
          if (tmp->data[level] < s_data[level]) // "new data" is bigger
          {
            if (tmp->rightL != nullptr)
              tmp = tmp->rightL;
            else {
              break;
            }
          } else {
            if (tmp->leftL != nullptr)
              tmp = tmp->leftL;
            else {
              break;
            }
          }
          level++;
        }
      }
    }
    level--;
  }
  // first go to leaf and save that as currentBest, then go backwards and
  // check if difference between the splitting coordinate of the search point
  // and current node is less than the distance (overall coordinates) from the
  // search point to the current best
  return currentBest->data;
}

void KDTree::pn(tnode* node)
{
  for (int i=0;i<dim;i++) {
    std::cout << node->data[i] << " ";
  }
  std::cout << std::endl;
}

float* KDTree::rNN(float* s_data)
{
  tnode* curBest = nullptr;
  curBest = recNN(s_data, head, 0);
  return curBest->data;
}

tnode* KDTree::recNN(float* s_data, tnode* tmp, int level)
{
  if (level == dim)
    level = 0;
  tnode* newbest = nullptr;
  if (tmp->data[level] < s_data[level]) // "new data" is bigger
  {
    if (tmp->rightL != nullptr)
      newbest = recNN(s_data, tmp->rightL, level++);
  } else {
    if (tmp->leftL != nullptr)
      newbest = recNN(s_data, tmp->leftL, level++);
  }
  if (newbest == nullptr)
    newbest = tmp;

  float distToBest = distS(newbest, s_data);
  float distToTmp = distS(tmp, s_data);
  if (distToTmp < distToBest) {
    newbest = tmp;
    distToBest = distToTmp;
  }
  pn(newbest);
  // the "big if", checks if there could be better on the other side of the axis
  if (distToBest > (tmp->data[level] - s_data[level]) * (tmp->data[level] - s_data[level])) {
    if (tmp->data[level] < s_data[level])
    {
      if (tmp->leftL != nullptr) // so we go to the opposite
        tmp = tmp->leftL;
    } else {
      if (tmp->rightL != nullptr) // because the "big if" told us to do so
        tmp = tmp->rightL;
    }
    tnode* another = recNN(s_data, tmp, level++); // we go to the other branch
    if (distS(another, s_data) < distToBest)
      newbest = another;
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
