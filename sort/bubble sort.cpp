#include <stdio.h>

void bubblesort(int array[], int size){
	for(int step=0;step<size-1;++step){
		int swapped = 0;
		for(int i=0;i<size-step-1;++i){
			if(array[i]>array[i+1]){
				int temp = array[i];
				array[i] = array[i+1];
				array[i+1] = temp;
				swapped = 1;
			}
		}
		if(swapped = 0){
			return;
		}
	}
}

void printArray(int array[], int size){
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

int main(){
	int a[] = {3, 4 ,-2, 0, 8, 9, 5};
	int n = sizeof(a)/sizeof(a[0]);
	printf("Unsorted array: ");
	printArray(a, n);
	bubblesort(a, n);
	printf("Sorted array: ");
	printArray(a, n);
	return 0;
}