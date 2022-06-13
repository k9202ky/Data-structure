#include <stdio.h>

void printArray(int array[], int size){
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

void insertionsort(int array[], int size){
	for(int step=1;step<size;step++){
		int key = array[step];
		int j = step - 1;
		while(key<array[j] && j>=0){
			array[j+1] = array[j];
			--j;
		}
		array[j+1] = key;
	}
}

int main(){
	int array[] = {6, 1, 4, 0, 2};
	int size = sizeof(array)/sizeof(array[0]);
	printf("Unsorted array: ");
	printArray(array, size);
	insertionsort(array, size);
	printf("Sorted array: ");
	printArray(array, size);
	return 0;
}