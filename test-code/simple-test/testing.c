

#include <stdio.h>
#include <string.h>

const int N_BINS = 7;

bool displayEndScreen(int *histogram, int colorOrder) 
{
	
	//color array
	string penColors[N_BINS] = {"invalid", "black: %d", "blue: %d",
	"green: %d", "yellow: %d", "red: %d", "white: %d", };
	
	//display first sorted list
	displayString(0, "L Quit C Shrp R Sort");
	if (colorOrder == 0){
		for (int i = 0; i<N_BINS; i++){
			displayString(i + 1, penColors[i], histogram[i]);
		}
	}
	else		//switch to other options based on users' spec
	{
		int tbSorted [N_BINS];
		int *P_tbSorted = &tbSorted;
		int notTaken [N_BINS];

		for (int u = 0; u < N_BINS ; u ++){
			tbSorted[u] = histogram[u];
			notTaken [N_BINS] = true;
		}

		if (colorOrder == 1){
			sort (P_tbSorted, N_BINS, colorOrder);	//ascending order
		} else{
			sort (P_tbSorted, N_BINS, false);		//desending order
		}

		int afterOrder[N_BINS];
		
		//sort color and quantity
		for (int x = 0; x < N_BINS; x ++){
			for (int y = 0; y < N_BINS; y ++){
				if (tbSorted[x] == histogram [y] && notTaken[y] )
					afterOrder[x] = y;
					taken [y] = false;
			}
		}
		
		//display sorted result
		for (int i = 0; i <N_BINS; i++){
			displayString (i + 1, penColors[afterOrder[i]], tbSorted[i]);
		}
	}
}


int main()
{
   int [] array { 4, 5, 6, 7, 8, 9, 10}
   int *point = &array;
   
   displayEndScreen(point, 0);
   printf("Hello, World!");
   return 0;
}
