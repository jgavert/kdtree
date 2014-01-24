
#include "kdtree.hpp"
#include <iostream>

int main()
{
  float dataa[12] = {0.0f, 0.0f,
                     0.2f, 1.0f,
                     0.3f, 0.4f,
                     0.5f, 0.1f,
                     0.4f, 0.2f,
                     0.8f, 1.0f};
  KDTree tree(2, dataa, 12);
  float find[2] = {0.21f,0.95f};
  float* result = tree.rNN(find);
  for (int i=0;i<2;i++) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;

  return 1;
}
