#include <stdio.h>

#define MAX_SIZE 1000

int segmentTree[MAX_SIZE];

void buildSegmentTree(int arr[], int node, int start, int end)
{
  if (start == end)
  {
    segmentTree[node] = arr[start];
    return;
  }

  int mid = (start + end) / 2;
  buildSegmentTree(arr, node * 2, start, mid);
  buildSegmentTree(arr, node * 2 + 1, mid + 1, end);
  segmentTree[node] = segmentTree[node * 2] + segmentTree[node * 2 + 1];
  return;
}

int query(int node, int start, int end, int l, int r)
{
  if (start > r || end < l)
  {
    return 0;
  }

  if (start >= l && end <= r)
  {
    return segmentTree[node];
  }

  int mid = (start + end) / 2;
  
  int left_val = query(2 * node, start, mid, l, r);
  int right_val = query(2 * node + 1, mid + 1, end, l, r);
  return left_val + right_val;
}

void update(int node, int start, int end, int idx, int val)
{
  if (start == end)
  {
    segmentTree[node] = val;
    return;
  }

  int mid = (start + end) / 2;
  if (idx <= mid)
  {
    update(2 * node, start, mid, idx, val);
  }
  else
  {
    update(2 * node + 1, mid + 1, end, idx, val);
  }
  segmentTree[node] = segmentTree[2 * node] + segmentTree[2 * node + 1];
}

int main()
{
  int arr[] = {1, 3, 5 ,7, 9, 11};
  int n = sizeof(arr) / sizeof(int);

  buildSegmentTree(arr, 1, 0, n - 1);
  printf("Sum of [1, 3] : %d\n", query(1, 0, n - 1, 1, 3));

  update(1, 0, n - 1, 2, 10);
  printf("Sum of [1, 3] after update [2] : %d\n", query(1, 0, n - 1, 1, 3));
  return 0;
}
