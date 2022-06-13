#include <iostream>
using namespace std;
void binary_search(int array[],int item,int len){
	int low=0;
	int high=len;
	while(low<=high){
		int mid=(low+high)/2;
		int guess=array[mid];
		if(guess==item){
			cout<<"Element found at "<<mid<<" th index"<<endl;
			return ;
		}
		if(guess>item){
			high=mid-1;
		}
		else{
			low=mid+1;
		}
	}
	cout<<"Don't find the element"<<endl;
	return ;	
}
int main(){
	int array[]={1,3,5,7,9,100,150};
	int len=sizeof(array)/sizeof(int);
	binary_search(array,3,len);
	binary_search(array,150,len);
	binary_search(array,200,len);
	return 0;
}