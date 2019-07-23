#include <iostream>
 
//Write an array's contents to the console
void PrintArray(int *array, int arraySize) {
  for (int i = 0; i < arraySize; ++i) {
        std::cout << array[i] << " " << std::flush; //std::flush prints straight away, rather than waiting for the buffer
  }
  std::cout << std::endl;   //std::endl = /n
}

//Perform a BubbleSort
void BubbleSort(int *array, int arraySize) {
  bool swapped = true;
  int j = 0;
  int temp;
 
  while (swapped) {   //repeat until no numbers need to be swapped
    swapped = false;
    j++;

    for (int i = 0; i < arraySize - j; ++i) {
      if (array[i] > array[i + 1]) {  //If an element is greater than the following element...
        temp = array[i];              //Store current value so it isn't overwritten
        array[i] = array[i + 1];      //Swap the value
        array[i + 1] = temp;          
        swapped = true;
      }
    }
  }
}

//Perform an Insertion Sort
void InsertionSort(int arr[], int arraySize){
  if(arraySize > 1){
    int size = arraySize;
    //Start at position 1 
    //At iteration i, the leftmost i elements are in sorted order.
    for(int i = 1; i < size; ++i){
      int j = i - 1;
      int key = arr[i];     //all elements to left of key are sorted
      while(j >= 0 && arr[j] > key){
        arr[j+1] = arr[j];  //move each element to the left until it is in the correct place
        --j;
      }
      arr[j+1] = key;
    }
  }
}

//*** SWAP INLINE FUNCTION ***
inline void Swap(int &a, int &b){   //inline functions - compiler replaces the function call statement with the function code itself
  int k = a;
  a = b;
  b = k;
}

//*** Selection Sort ***
void SelectionSort(int arr[], int arraySize){
  for(int i = 0; i < arraySize - 1; ++i){
    int min = i;

    for(int j = i+1; j < arraySize; ++j) { //Repeatedly searches for the largest value in a section of the data                                
        if(arr[j] < arr[min]) {
            min = j;    
        }
    }

    Swap(arr[min], arr[i]);             //Moves that value into its correct position in a sorted section of the list
  }
}

//*** Quick Sort ***
//return a random number
inline int rand(int p, int q){
    int size = q - p + 1;

    return (p + rand() % size);
}
int Partition(int arr[], int lo, int hi){
    
    int t = rand(lo, hi);
    Swap(arr[t], arr[hi]);
 
    int index = lo - 1;
    int key = arr[hi];
    for(int i = lo ; i < hi; i++){
        if(arr[i] <= key)   //if element is smaller than pivot
            Swap(arr[++index], arr[i]);  //swap
    }
    Swap(arr[++index], arr[hi]);
    return index;
}
void QuickSortHelper(int arr[], int lo, int hi){
    if(lo < hi){
        int index = Partition(arr, lo, hi); //Partition array into higher and lower arrays depending on a pivot
        QuickSortHelper(arr, lo, index-1);
        QuickSortHelper(arr, index+1, hi);
    }
}
 
void QuickSort(int arr[], int arr_size){
    QuickSortHelper(arr, 0, arr_size-1);
}

//*** Merge Sort ***
void Merger(int arr[], int lo, int  mi, int hi){
    int *temp = new int[hi-lo+1];//temporary merger array
    int i = lo, j = mi + 1;//i is for left-hand,j is for right-hand
    int k = 0;//k is for the temporary array
    while(i <= mi && j <=hi){
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    //rest elements of left-half
    while(i <= mi)
        temp[k++] = arr[i++];
    //rest elements of right-half
    while(j <= hi)
        temp[k++] = arr[j++];
    //copy the mergered temporary array to the original array
    for(k = 0, i = lo; i <= hi; ++i, ++k)
        arr[i] = temp[k];
 
    delete []temp;
}
void MergeSortHelper(int arr[], int lo, int hi){
    int mid;
    if(lo < hi){
        mid = (lo + hi) >> 1;
        MergeSortHelper(arr, lo, mid);
        MergeSortHelper(arr, mid+1, hi);
        Merger(arr, lo, mid, hi);
    }
}
void MergeSort(int arr[], int arraySize){
    MergeSortHelper(arr, 0, arraySize-1);
}

int main() {
  int array[] = {32, 40, 25, 94, 234, 1, 524, 656, 19, 1843};
  int arraySize = sizeof(array)/sizeof(array[0]);   //Get array size (total array size in bytes / size of one array element)
 
  std::cout << "Before Sort :" << std::endl;
  PrintArray(array, arraySize);
 
  //*** Uncomment which sort you wish to perform: ***
  //BubbleSort(array, arraySize);
  //InsertionSort(array, arraySize);
  //SelectionSort(array, arraySize);
  //QuickSort(array, arraySize);
  MergeSort(array, arraySize);

  std::cout << "After Sort :" << std::endl;
  PrintArray(array, arraySize);
  
  return (0);
}
