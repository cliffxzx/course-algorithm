#include "stdio.h"
#include "stdlib.h"

void merge(int *container, int now_c, int *arr_n, int now_n, int *arr_m, int now_m) {
  while (now_n >= 0 && now_m >= 0)
    if (arr_n[now_n] > arr_m[now_m])
      container[now_c--] = arr_n[now_n--];
    else
      container[now_c--] = arr_m[now_m--];

  while (now_n >= 0)
    container[now_c--] = arr_n[now_n--];

  while (now_m >= 0)
    container[now_c--] = arr_m[now_m--];
}

int binary_search(int item, int *container, int size) {
  int left = 0, right = size - 1, mid;
  while (right >= left) {
    mid = (left + right) / 2;

    if (container[mid] > item)
      right = mid - 1;
    else if (container[mid] < item)
      left = mid + 1;
    else
      return mid;
  }

  return -1;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int *arr_n = malloc(sizeof(int) * n);
  int *arr_m = malloc(sizeof(int) * m);

  for (int i = 0; i < n; ++i)
    scanf("%d", arr_n + i);

  for (int i = 0; i < m; ++i)
    scanf("%d", arr_m + i);

  int nm_size = n + m;
  int *arr_nm = malloc(sizeof(int) * nm_size);

  merge(arr_nm, nm_size - 1, arr_n, n - 1, arr_m, m - 1);
  for (int i = 0; i < nm_size; ++i)
    printf("%d%c", arr_nm[i], i + 1 == nm_size ? '\n' : ' ');

  int x;
  scanf("%d", &x);
  int index = binary_search(x, arr_nm, nm_size);
  if (index >= 0)
    printf("%d\n", index);
  else
    printf("%s\n", "not found");

  free(arr_nm);
  free(arr_m);
  free(arr_n);
  return 0;
}