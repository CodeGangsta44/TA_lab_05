#include <iostream>
#include <fstream>
#include "limits.h"

using namespace std;

void swap(int* a, int* b){ // функція для обміну елементів масиву місцями
  int swap = *a;
  *a = *b;
  *b = swap;
}

void heapify_for_max(int* heap, int index, int len){
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int dominant = index;
  if (left < len && heap[left] > heap[index]) dominant = left;
  if (right < len && heap[right] > heap[dominant]) dominant = right;
  if (dominant != index){
    swap (&heap[index], &heap[dominant]);
    heapify_for_max(heap, dominant, len);
  }
}

void heapify_for_min(int* heap, int index, int len){
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int recisive = index;
  if (left < len && heap[left] < heap[index]) recisive = left;
  if (right < len && heap[right] < heap[recisive]) recisive = right;
  if (recisive != index){
    swap (&heap[index], &heap[recisive]);
    heapify_for_min(heap, recisive, len);
  }
}

void sift_up_for_max(int* heap, int index){
  while(heap[index] > heap[(index - 1) / 2] && index > 0){
    swap(&heap[index], &heap[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

void sift_up_for_min(int* heap, int index){
  while(heap[index] < heap[(index - 1) / 2] && index > 0){
    swap(&heap[index], &heap[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

int main(int argc, char* argv[]){

  ifstream fin(argv[1]);
  ofstream fout("ip71_dovhopoliuk_05_output.txt");
  int N;
  fin >> N;

  int *heap_low = new int[N + 1]; // max-heap
  int *heap_high = new int[N + 1]; // min-heap

  for (int i = 0; i <= N; i++){
    heap_low[i] = INT_MIN;
    heap_high[i] = INT_MAX;
  }

  int input;

  fin >> input;

  heap_low[0] = input;

  int len_min = 1;
  int len_max = 0;


  for (int i = 1; i < N; i++){

    fin >> input;

    if (len_max > len_min){
      fout << heap_high[0] << endl;
    }
    if (len_max < len_min){
      fout << heap_low[0] << endl;
    }
    if (len_min == len_max){
      fout << heap_low[0] << " " << heap_high[0] << endl;
    }

    if (input > heap_low[0]){
      heap_high[len_max] = input;
      len_max++;
      sift_up_for_min(heap_high, len_max - 1);
    } else {
      heap_low[len_min] = input;
      len_min++;
      sift_up_for_max(heap_low, len_min - 1);
    }
    if (len_min - len_max == 2){
      heap_high[len_max] = heap_low[0];
      len_min--;
      len_max++;
      heap_low[0] = heap_low[len_min];
      sift_up_for_min(heap_high, len_max - 1);
      heapify_for_max(heap_low, 0, len_min);
    }
    if (len_max - len_min == 2){
      heap_low[len_min] = heap_high[0];
      len_min++;
      len_max--;
      heap_high[0] = heap_high[len_min];
      sift_up_for_max(heap_low, len_min - 1);
      heapify_for_min(heap_high, 0, len_max);
    }
  }


  if (len_max > len_min){
    fout << heap_high[0] << endl;
  }
  if (len_max < len_min){
    fout << heap_low[0] << endl;
  }
  if (len_min == len_max){
    fout << heap_low[0] << " " << heap_high[0] << endl;
  }
}
