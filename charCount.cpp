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
			delete countArray;
		};
		void incCharCount(unsigned int asciiChar){
			if(asciiChar < ASCII_MAX){
				countArray[asciiChar] += 1;
			}
		}
		int getCharCount(unsigned int asciiChar){
			if(asciiChar < ASCII_MAX){
				return countArray[asciiChar];
			}else{
				return 0;
			}
		}
};


int main(){
	LetterCounter charTracker;

	char inputFileName[50];

	printf("enter file name\n");
	scanf("%s", inputFileName);

	std::ifstream inputFile;
	inputFile.open(inputFileName);

	if(!inputFile.is_open()){
		printf("failed to open %s\n", inputFileName);
		return 1;
	}

	while(!inputFile.eof()){
		char rightNow = inputFile.get();
		charTracker.incCharCount(rightNow);
	}

	for(int i = 0; i <= 0x1ff; i++){
		if(charTracker.getCharCount(i) != 0)
			if(i == '\n'){
				printf("\\n appeared %d times\n", charTracker.getCharCount(i));
			}else{
				printf("'%c' appead %d times\n", i, charTracker.getCharCount(i));
			}
	}
	inputFile.close();

	return 0;
}
