// Author: shiyi
#ifndef SEARCH_H
#define SEARCH_H
#endif

// Sequential search (ordered array)
int SeqSearch(int array[], int k, int length) {
  /**
   * Sequential search is a simple brute force search, good for small arrays,
   * and slow for large ones.
   */
  if (length < 2)
    return -1;
  else {
    for (int i = 0; i < length; i++) {
      if (array[i] == k)
        return i;
    }
  }
  return 0;
}

// Binary search (unordered array)
int BinarySearch(int array[], int k, int length) {
  /**
   * Binary search is fast and has no array requirements.
   */
  int first = 0, end = length - 1;
  while (first <= end) { // if array length < 1, not run!
    int mid = first + (end - first) / 2; // Access to the median

    if (array[mid] > k)
      end = mid - 1;
    else if (array[mid] < k)
      first = mid + 1;
    else
      return mid;
  }
  return 0;
}
