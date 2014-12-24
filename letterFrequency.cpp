//#include <iostream>
#include <string.h>
#include <stdio.h>

class LetterCounter{
	private:
		int * countArray;
	public:
		LetterCounter(){
			//create an array with space for every ascii character
			countArray = new int[0xff];
			memset(countArray, 0, 0xff*sizeof(int));
		};
		~LetterCounter(){
			delete[] countArray;
		};
		void incCharCount(unsigned char asciiChar){
			countArray[asciiChar] += 1;
		}
		int getCharCount(unsigned char asciiChar){
			return countArray[asciiChar];
		}
};


int main(){
	LetterCounter frequency;
	frequency.incCharCount(0x30);
	
	for(int i = 0; i <= 0xff; i++){
	
		printf("Seen %c %d times\n", i, frequency.getCharCount((char)i));
	}



	return 0;
}
