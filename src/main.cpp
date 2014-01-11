
#include "kdtree.hpp"

int main()
{
  float dataa[18] = {0.0f, 0.0f, 0.9f,
                     0.2f, 1.0f, 1.0f,
                     0.3f, 0.4f, 1.0f,
                     0.5f, 0.1f, 0.8f,
                     0.4f, 0.2f, 0.3f,
                     0.8f, 1.0f, 0.0f,};
  KDTree tree(3, dataa, 18);

  return 1;
}
