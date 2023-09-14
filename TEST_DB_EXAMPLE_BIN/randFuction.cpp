#include<iostream>
#include<cstdlib>

using namespace std;



bool check(int n,int array[]){
	
	for(int i = 0; i < 30;i++){
		if(array[i] == n)
		    return false;
	}
	return true;
	
}

int main(){
	
	int no[30];
	
	int min = 4000;
	int max = 4999;
	
	
	for(int i=1; i<=10; i++){
		 
		 int n = (rand() % (max-min+1))+ min;
		 
		 if(check(n,no)){
		 	no[i] = n;
		 	cout<<no[i]<<endl;
		 }else{
		 	i--;
		 }
			 
}
	   
	return 0;
}
