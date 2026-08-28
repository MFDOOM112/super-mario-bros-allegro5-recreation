//PRÁCTICA: FUNCIONES
#include <iostream>
using namespace std;
int numero(){
	int n;
	cout<<"Digite un numero: ";
	cin>>n;
	return n;
}
int main(){
	int n = numero();
	while(n%2==0){
		n = numero();
	}
	int m[n][n];
	for(int i = 0; i<n; i++){
		for(int j =0; j<n; j++){
			if(j==n/2){
				m[i][j] = 2;
			}else if(i==n/2){
				m[i][j] = 2;
			}else if(i<=(n-1)/2 && j<=(n-1)/2){
				m[i][j] = 1;
			}else if(i<=(n-1)/2&&j>(n-1)/2){
				m[i][j] = 3;
			}else if(i>=(n-1)/2&&j<=(n-1)/2){
				m[i][j] = 4;
			}else{
				m[i][j] = 5;
			}
			cout<<m[i][j]<<" | ";
		}
		cout<<endl;
	}
	return 0;
}
