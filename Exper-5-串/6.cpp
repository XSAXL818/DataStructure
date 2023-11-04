#include<iostream>
using namespace std;

class Func{
	private:
		int arr[100];
		int len;
	public:
		Func() = default;
		
	void assign( int arr[100], int len ){
		int i;
		this->len = len;
		for( i = 0; i < len; i++ ){
			this->arr[i] = arr[i];
		}
	}
	
	int getMax(){
		int max = -9999;
		int i;
		for( i = 0; i < len; i++ ){
			if( arr[i] > max ){
				max = arr[i];
			}
		}
		return max;
	}
	
	void printMax(){
		cout << "最大值为" << this->getMax() << "\n";
	}
};

int main(){
	
	Func func = Func();
	int arr[10] = { 1, 84, 23, 56, 98, 67, 87, 56, 87, 23 };
	func.assign( arr, 10 );
	int max = func.getMax();
	cout << "max=" << max << "\n";
	func.printMax();
	
	return 0;
}