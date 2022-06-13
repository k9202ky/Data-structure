#include <stdio.h>

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void printArray(int arr[], int size){
	for(int i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int partition(int arr[], int low, int high){
	int pivot = arr[high];
	int i = low - 1;
	for(int j=low;j<high;j++){
		if(arr[j] <= pivot){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1],&arr[high]);
	return i+1;
}

void quicksort(int arr[], int low, int high){
	if(low < high){
		int pi =partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi+1, high);
	}
}

int main(){
	int data[] = {8, 7, 6, 1, 0, 9, 2};
	int n = sizeof(data)/sizeof(data[0]);
	printf("Unsorted array: ");
	printArray(data, n);
	quicksort(data, 0, n-1);
	printf("\n");
	printf("sorted array: ");
	printArray(data, n);
	return 0;
}