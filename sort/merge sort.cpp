  #include <stdlib.h>
#include <stdio.h>
#include <string.h>

void merge(int a[], int start_idx, int m_idx, int end_idx) {
	int *tmp;
	int i, j, k;

	tmp	= (int*)malloc(sizeof(int)*(end_idx-start_idx+1));
	i = start_idx; j = m_idx; k = 0;
	while (i<m_idx || j<=end_idx) {
		if (i>=m_idx) {
			for (; j<=end_idx; j++) {
				tmp[k] = a[j];
				k++;
			}
		} else if (j>end_idx) {
			for (; i<m_idx; i++) {
				tmp[k] = a[i];
				k++;
			}
		} else if (a[i]<a[j]) {
			tmp[k] = a[i];
			k++;
			i++;
		} else {
			tmp[k] = a[j];
			k++;
			j++;
		}
	}
	
	memcpy(a+start_idx, tmp, sizeof(int)*(end_idx-start_idx+1));
	free(tmp);
}

void mergesort(int a[], int start_idx, int end_idx) {
	int m_idx;
	
	if (start_idx==end_idx) {
		return;
	}
	
	m_idx = (end_idx+start_idx+1)/2;
	mergesort(a, start_idx, m_idx-1);
	mergesort(a, m_idx, end_idx);
	printf("%d %d %d\n", start_idx, m_idx, end_idx);
	merge(a, start_idx, m_idx, end_idx); 
}

int main(int argc, char **argv) {
	int i;
	int a[] = {20, 6, 10, 40, 39};
	
	for (i=0; i<5; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	
	mergesort(a, 0, 4);
	printf("sorting result:");
	for (i=0; i<5; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}