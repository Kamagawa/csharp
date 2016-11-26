

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std; 
const int N_BINS = 7;

void swap(int * const a, int * const b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int ar[], int len, bool ascending = true) {
	int i, j, k;

	for (i = 1; i < len; i++) {
		k = i;
		for (j = i - 1; j > -1; j--) {
			if (ar[k] >= ar[j] ^ ascending) {
				swap(ar[k], ar[j]);
				k--;
			}
		}
	}
}

bool displayEndScreen(int histogram[], int colorOrder) 
{
	
	//color array
	string penColors[N_BINS] = {"invalid", "black: %d", "blue: %d",
	"green: %d", "yellow: %d", "red: %d", "white: %d" };
	
	//display first sorted list
	cout<<( "L Quit C Shrp R Sort")<<endl;
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			cout << penColors[i]<<" " << histogram[i]<<endl;
		}
	}
	else		//switch to other options based on users' spec
	{
		int tbSorted [N_BINS];
		int notTaken [N_BINS];
		int afterOrder[N_BINS];

		for (int u = 0; u < N_BINS ; u ++){
			tbSorted[u] = histogram[u];
			notTaken [u] = true;
			afterOrder[u] = 0;
		}

		if (colorOrder == 1){
			sort (tbSorted, N_BINS, colorOrder);	//ascending order
		} else{
			sort (tbSorted, N_BINS, false);		//desending order
		}

	
		
	
		int k = 0;
		//sort color and quantity
		for (int x = 0; x < N_BINS; x ++){
			for (int y = 0; y < N_BINS; y ++){
				if (tbSorted[x] == histogram [y] && notTaken [y]){
				
					
					cout << tbSorted[x] <<" "<< histogram [y] <<" "<<y <<endl;
					//cout <<" notTaken " << y <<": "<<notTaken[y]<<endl;
					afterOrder[k] = y;
					k++;
					notTaken [y] = false;
				}
			}
		}
		
		//display sorted result
		for (int i = 0; i <N_BINS; i++){
			cout<< "afterOrder: "<<afterOrder[i] <<endl;
			//cout<< (penColors[afterOrder[i]] )<<tbSorted[i] <<endl;
		}
	}
}


int main()
{
   int  array[N_BINS] = { 1, 2, 2, 2, 2, 3, 7};
   
   displayEndScreen(array, 1);
   printf("Hello, World!");
   return 0;
}
