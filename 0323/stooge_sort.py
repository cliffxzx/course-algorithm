def stooge_sort(arr, i, j):
  if arr[i] > arr[j]:
    arr[i], arr[j] = arr[j], arr[i]

  if i + 1 >= j:
    return

  k = int((j - i + 1) / 3)
  stooge_sort(arr, i, j - k)
  stooge_sort(arr, i + k, j)
  stooge_sort(arr, i, j - k)


arr = [8, 4, 3, 2, 7, 6, 5, 1]
stooge_sort(arr, 0, len(arr) - 1)
print(arr)