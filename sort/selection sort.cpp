#include <stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionsort(int array[], int size){
	for(int step=0;step<size-1;step++){
		int min_idx = step;
		for(int i=step+1;i<size;i++){
			if(array[i]<array[min_idx]){
				min_idx = i;
			}
		}
		swap(&array[min_idx], &array[step]);
	}
}

void printArray(int array[], int size){
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

int main(){
	int array[] = {20, 12, 10, 15, 2};
	int size = sizeof(array)/sizeof(array[0]);
	printf("Unsorted array: ");
	printArray(array, size);
	selectionsort(array, size);
	printf("Sorted array: ");
	printArray(array, size);
	return 0;
}