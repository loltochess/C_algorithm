#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1004

int adj[MAX][MAX];
int visited[MAX];

int n, m, v;

void dfs(int idx)
{
	visited[idx] = 1;
	printf("%d ", idx);
	for (int i = 1; i <= n; i++)
	{
		if (adj[idx][i] && !visited[i])
		{
			dfs(i);
		}
	}
	return;
}

typedef struct _Queue
{
	int data[MAX];
	int front;
	int rear;
} Queue;

void queue_init(Queue* q)
{
	q->front = 0;
	q->rear = 0;
}

int queue_empty(Queue* q)
{
	return q->front == q->rear;
}

void queue_push(Queue* q, int x)
{
	q->data[q->rear++] = x;
	return;
}

int queue_pop(Queue* q)
{
	return q->data[q->front++];
}

void bfs(int idx)
{
	Queue q;
	queue_init(&q);
	
	queue_push(&q, idx);
	visited[idx] = 1;

	while (!queue_empty(&q))
	{
		int front_value = queue_pop(&q);
		printf("%d ", front_value);

		for (int i = 1; i <= n; i++)
		{
			if (adj[front_value][i] && !visited[i])
			{
				visited[i] = 1;
				queue_push(&q, i);
			}
		}
	}
}



int main()
{
	scanf("%d %d %d", &n, &m, &v);
	
	for (int i = 0; i < m; i++)
	{
		int _u, _v;
		scanf("%d %d", &_u, &_v);
		adj[_u][_v] = 1;
		adj[_v][_u] = 1;
	}
	
	// 1. dfs
	dfs(v);
	printf("\n");
	memset(visited, 0, sizeof(visited));
	// 2. bfs
	bfs(v);
	printf("\n");
	return 0;
}
