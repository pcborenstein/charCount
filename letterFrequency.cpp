//#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>

#define ASCII_MAX 0Xff

class LetterCounter{
	private:
		int * countArray;
	public:
		LetterCounter(){
			//create an array with space for every ascii character
			countArray = new int[ASCII_MAX];
			memset(countArray, 0, ASCII_MAX*sizeof(int));
		};
		~LetterCounter(){
			delete[] countArray;
		};
		void incCharCount(int asciiChar){
			if(asciiChar < ASCII_MAX){
				countArray[asciiChar] += 1;
			}
		}
		int getCharCount(int asciiChar){
			if(asciiChar < ASCII_MAX){
				return countArray[asciiChar];
			}else{
				return 0;
			}
		}
};


int main(){
	LetterCounter frequency;

	frequency.incCharCount(0x30);

	char inputFileName[50];

	printf("enter file name\n");
	scanf("%s", inputFileName);
	
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	if(!inputFile.is_open()){
		printf("failed to open %s\n", inputFileName);
		return 1;
	}


	for(int i = 0; i <= 0x1ff; i++){
		if(frequency.getCharCount(i) != 0)
			printf("Seen %c %d times\n", i, frequency.getCharCount(i));
	}


	return 0;
}
