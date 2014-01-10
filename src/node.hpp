#ifndef _NODE_
#define _NODE_

typedef struct tnode
{
  float* data;
  struct tnode* parent;
  struct tnode* leftL;
  struct tnode* rightL;
} tnode;

#endif
