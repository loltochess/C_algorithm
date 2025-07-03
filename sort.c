#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  int score;
} Student;

int compare(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int compareStudent(const void* a, const void* b) {
  Student* s1 = (Student*)a;
  Student* s2 = (Student*)b;

  if (s1->score == s2->score) {
    return s1->id - s2->id;
  }
  return s1->score - s2->score;
}

int main() {
  int arr[] = {5, 4, 3, 2, 1};
  qsort(arr, 5, sizeof(int), compare);
  for (int i = 0; i < 5; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");

  Student s1 = {10, 20};
  Student s2 = {1, 20};

  Student students[] = {s1, s2};

  qsort(students, 2, sizeof(Student), compareStudent);

  for (int i = 0; i < 2; i++) {
    printf("%d and %d, ", students[i].id, students[i].score);
  }
  printf("\n");

  return 0;
}