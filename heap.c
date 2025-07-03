#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_MAX 100000

typedef struct
{
  int node;
  int dist;
} PQNode;

typedef struct
{
  PQNode data[HEAP_MAX];
  int size;
} MinHeap;

void heap_init(MinHeap* h)
{
  h->size = 0;
}

void heap_push(MinHeap* h, PQNode pqNode)
{
  int i = ++(h->size);

  while (i != 1 && h->data[i/2].dist > pqNode.dist)
  {
    h->data[i] = h->data[i/2];
    i /= 2;
  }
  h->data[i] = pqNode;
}

PQNode heap_pop(MinHeap* h)
{
  if (h->size == 0) return (PQNode){.node = -1, .dist = -1};

  PQNode min = h->data[1];

  PQNode tmp = h->data[(h->size)--];
  
  int parent = 1;
  int child = 2;

  while (child <= h->size)
  {
    if (child + 1 <= h->size && h->data[child + 1].dist < h->data[child].dist)
    {
      child++;
    }

    if (tmp.dist <= h->data[child].dist) break;

    h->data[parent] = h->data[child];
    parent = child;
    child *= 2;
  }
  h->data[parent] = tmp;
  return min;
}

int main() {
  MinHeap pq;
  heap_init(&pq);

  heap_push(&pq, (PQNode){.node = 2, .dist = 10});
  heap_push(&pq, (PQNode){.node = 1, .dist = 5});
  heap_push(&pq, (PQNode){.node = 3, .dist = 7});

  while (pq.size) {
    PQNode top = heap_pop(&pq);
    printf("node: %d, dist: %d\n", top.node, top.dist);
  }
  return 0;
}