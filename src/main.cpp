#include <iostream>
#include "kdtree.hpp"

int main(int argc, char** argv)
{
  float dataa[12] = {0.5f, 0.0f,
                     0.1f, 0.1f,
                     0.9f, 0.1f,
                     0.2f, 0.2f,
                     0.8f, 0.8f,
                     0.7f, 0.51f};
  KDTree tree(2, dataa, 12);
  tree.print();

  float find[2] = {0.49f,0.8f};
  float* result = tree.NN(find);
  std::cout << "searching nearestneighbour for ";
  for (int i=0;i<2;i++) {
    std::cout << find[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Got result: ";
  for (int i=0;i<2;i++) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;
#if WIN32
  std::cin.get();
#endif
  return 1;
}
