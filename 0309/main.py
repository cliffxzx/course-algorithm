def build_set(A):
  S = []
  A.sort()

  if len(A) > 0:
    S.append(A[0])

  for index in range(1, len(A)):
    if A[index] != A[index - 1]:
      S.append(A[index])

  return S


def binary_search(array, element):
  start, mid, end = 0, 0, len(array) - 1
  while start <= end:
    mid = (start + end) // 2

    if element < array[mid]:
        end = mid - 1
    elif element > array[mid]:
        start = mid + 1
    else:
        return True

  return False

def union(S1, S2):
  i = 0
  j = 0
  S3 = []

  while i < len(S1) and j < len(S2):
    if S1[i] < S2[j]:
      S3.append(S1[i])
      i += 1
    elif S1[i] > S2[j]:
      S3.append(S2[j])
      j += 1
    elif S1[i] == S2[j]:
      S3.append(S1[i])
      i += 1
      j += 1

  while i < len(S1):
    S3.append(S1[i])
    i += 1

  while j < len(S2):
    S3.append(S2[j])
    j += 1

  return S3


def intersection(S1, S2):
  i = 0
  j = 0
  S3 = []

  while i < len(S1) and j < len(S2):
    if S1[i] < S2[j]:
      i += 1
    elif S1[i] > S2[j]:
      j += 1
    elif S1[i] == S2[j]:
      S3.append(S1[i])
      i += 1

  return S3

def exist(S, element):
  return binary_search(S, element)

print(union(build_set([1, 4, 7, 3, 9, 7]), build_set([9, 5, 7, 4, 6, 11])))
print(intersection(build_set([1, 4, 7, 3, 9, 7]), build_set([9, 5, 7, 4, 6, 11])))
print(exist(build_set([1, 4, 7, 3, 9, 7]), 7))