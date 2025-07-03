#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_V 20001
#define INF INT_MAX

typedef struct Node
{
  int to, weight;
  struct Node* next;
} Node;

Node* adj[MAX_V];

void add_edge(int from, int to, int weight)
{
  Node* new_node = malloc(sizeof(Node));
  new_node->to = to;
  new_node->weight = weight;
  new_node->next = adj[from];
  adj[from] = new_node;
}

typedef struct
{
  int node;
  int dist;
} PQNode;

typedef struct
{
  PQNode data[MAX_V];
  int size;
} MinHeap;

void heap_init(MinHeap* h)
{
  h->size = 0;
}

void heap_push(MinHeap*h, PQNode val)
{
  int i = ++(h->size);

  while (i != 1 && h->data[i/2].dist > val.dist)
  {
    h->data[i] = h->data[i/2];
    i /= 2;
  }
  h->data[i] = val;
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

    if (tmp.dist >= h->data[child].dist) break;

    h->data[parent] = h->data[child];
    parent = child;
    child *= 2;
  }
  h->data[parent] = tmp;
  return min;
}

int heap_empty(MinHeap* h)
{
  return h->size == 0;
}

// dijkstra
int dist[MAX_V];
int visited[MAX_V];

void dijkstra(int start, int V)
{
  MinHeap pq;
  heap_init(&pq);

  for (int i = 1; i <= V; i++) dist[i] = INF;
  dist[start] = 0;

  heap_push(&pq, (PQNode){.node = start, .dist = 0});

  while (!heap_empty(&pq))
  {
    PQNode currentNode = heap_pop(&pq);
    int here = currentNode.node;
    int here_dist = currentNode.dist;

    if (here_dist != dist[here]) continue;

    Node* p = adj[here];
    while (p)
    {
      int next = p->to;
      int next_dist = p->weight;

      if (dist[next] > dist[here] + next_dist)
      {
        dist[next] = dist[here] + next_dist;
        heap_push(&pq, (PQNode){.node = next, .dist = dist[next]});
      }

      p = p->next;
    }
  }
}

int main() {
  int V, E, K;
  scanf("%d %d %d", &V, &E, &K);

  for (int i = 0; i < E; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    add_edge(u, v, w);
  }

  dijkstra(K, V);

  for (int i = 1; i <= V; i++) {
    if (dist[i] == INF)
      printf("INF\n");
    else
      printf("%d\n", dist[i]);
  }

  return 0;
}