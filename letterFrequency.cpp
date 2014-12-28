//#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>

#define ASCII_MAX 0xFF
#define ASCIIUpperLowerOffset 0x20 //Add this to go from upper to lower, subtract to go from lower to upper
#define AlphASCIILowerOffset 0x61

//Frequency of English language letters from A->Z
double frequencyTable[26] = {0.0817, 0.0150, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007};

class LetterCounter{
	private:
		int * countArray;
		double * frequencyArray;
		int totalCharCount;
	public:
		LetterCounter(){
			//create an array with space for every ascii character
			countArray = new int[ASCII_MAX];
			memset(countArray, 0, ASCII_MAX*sizeof(int));  //look up what this call does
			frequencyArray = new double[ASCII_MAX];
			memset(countArray, 0, ASCII_MAX*sizeof(double));
			totalCharCount = 0;
		};

		~LetterCounter(){
			delete countArray;
			delete frequencyArray;
		};

		//Build the character count array
		void buildCharCountArray(char * inputFileName){
			std::ifstream inputFile;
			inputFile.open(inputFileName);
			if(!inputFile.is_open()){
				printf("failed to open %s\n", inputFileName);
			}
			while(!inputFile.eof()){
				char rightNow = inputFile.get();
				incCharCount(rightNow);
			}
			inputFile.close();
			buildCharFreqArray();
		}

		//Increment the char count
		void incCharCount(unsigned int asciiChar){
			if(asciiChar < ASCII_MAX){
				countArray[asciiChar] += 1;
			}
		}

		//Pull and value from the built array
		int getCharCount(unsigned int asciiChar){
			if(asciiChar < ASCII_MAX){
				return countArray[asciiChar];
			}else{
				return 0;
			}
		}

		//Get the total number of "letter" char only to do frequency analysis
		int getTotalCharCount(){
			totalCharCount = 0;
			for(int i = 97; i <= 122; i++){
				totalCharCount += getCharCount(i);
			}
			return totalCharCount;
		}

		//Ouput the files frequency table
		void getFileFreqTable(){
			for(int i = 0; i < 26; i++){
				printf("Letter '%c' has a frequency percentage of %0.4f\n", i + AlphASCIILowerOffset, frequencyArray[i]);
			}
		}

		//Build file frequency array
		void buildCharFreqArray(){
			for(int i = 0x61; i <= 0x7A; i++){
				frequencyArray[i - AlphASCIILowerOffset] = double(getCharCount(i)) / getTotalCharCount();
			}

		}

		//Decode the charaters to figure out what they could be
		void decodeLetters(double precision){
			for(int i = 0x61; i <= 0x7A; i++){
				for(int j = 0; j < 26; j++){
					if((frequencyArray[i] >= (frequencyTable[j] - precision)) && (frequencyArray[i] <= (frequencyTable[j] + precision))){
						printf("The letter in the file %c could be %c\n", i, (j+AlphASCIILowerOffset));
					}
				}
			}
		}

		//Arrange the letters in frequency order
		void arrangeByFrequency(){
			printf("The file letters arranged in frequency order are:\n");
			int currentLetter = 0;
			double currentLetterFrequency = 0;
			int orderedArray[26];
			double tempFrequencyArray[26];
			for(int i = 0; i < 26; i++){
				tempFrequencyArray[i] = frequencyArray[i];
			}
			for(int i = 0; i < 26; i++){
				for(int j = 0; j < 26; j++){
					if(currentLetterFrequency < tempFrequencyArray[j]){
						currentLetter = j;
						currentLetterFrequency = tempFrequencyArray[j];
					}
				}
				currentLetterFrequency = 0;
				orderedArray[i] = currentLetter + AlphASCIILowerOffset;
				tempFrequencyArray[currentLetter] = 0;
			}
			for(int i = 0; i < 26; i++){
				printf("The letter is %c\n", orderedArray[i]);
			}
		}
};


int main(){
	LetterCounter frequency;

	char inputFileName[50];

	printf("Enter file name: ");
	scanf("%s", inputFileName);

	frequency.buildCharCountArray(inputFileName);

	printf("Total number of ASCII characters between a and z is %d\n", frequency.getTotalCharCount());

	frequency.getFileFreqTable();

	frequency.decodeLetters(0.0050);

	frequency.arrangeByFrequency();

	return 0;
}