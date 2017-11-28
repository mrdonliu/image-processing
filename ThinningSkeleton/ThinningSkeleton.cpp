#include <iostream>
#include <fstream>
using namespace std;


class ThinningSkeleton{
	private:
		int numRows, numCols, minVal, maxVal;
		int cycleCount;
		bool changeFlag;
		int** firstAry;
		int** secondAry;
		ifstream imageReader;
		ofstream fileWriter1, fileWriter2;
		int tempData;
	public:
		ThinningSkeleton(char* imageFile , char* outputFile1 , char* outputFile2);
		~ThinningSkeleton();
		void zeroFramed(int** ary);
		void loadImage();
		void copyAry();
		void doThinning(int row , int col);
		void northThinning();
		void southThinning();
		void eastThinning();
		void westThinning();
		void prettyPrint();
		void performThinning();
};

ThinningSkeleton::ThinningSkeleton(char* imageFile , char* outputFile1 , char* outputFile2){
	imageReader.open(imageFile);
	fileWriter1.open(outputFile1);
	fileWriter2.open(outputFile2);
	for(int i = 0 ; i < 4 ; i++){
		imageReader >> tempData;
		switch(i){
			case 0:
				numRows = tempData;
				break;
			case 1:
				numCols = tempData;
				break;
			case 2:
				minVal = tempData;
				break;
			case 3:
				maxVal = tempData;
				break;
		}
	}
	firstAry = new int*[numRows+2];
	secondAry = new int*[numRows+2];
	for(int i = 0 ; i < numRows + 2 ; i++){
		firstAry[i] = new int[numCols + 2];
		secondAry[i] = new int[numCols + 2];
	}
	zeroFramed(firstAry);
	zeroFramed(secondAry);
	loadImage();
	cycleCount = 0;
	prettyPrint();
}

ThinningSkeleton::~ThinningSkeleton(){
	imageReader.close();
	fileWriter1.close();
	fileWriter2.close();
}
void ThinningSkeleton::zeroFramed(int** ary){
	for( int i = 0 ; i < numRows + 2 ; i++ ){
		ary[i][0] = 0;
		ary[i][numCols+1] = 0;
	}
	for( int i = 1 ; i < numCols + 1 ; i++ ){
		ary[0][i] = 0;
		ary[numRows + 1][i] = 0;
	}
}

void ThinningSkeleton::loadImage(){
	for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      imageReader >> tempData;
      firstAry[i][x] = tempData;
      secondAry[i][x] = tempData;
    }
  }
}
void ThinningSkeleton::copyAry(){
	for(int i = 0; i < numRows + 2 ; i++){
		for(int x = 0; x < numCols + 2 ; x++){
			firstAry[i][x] = secondAry[i][x];
	}
	}
}
void ThinningSkeleton::doThinning(int row , int col){
	int numOfNeighbors = 0;
	if(!changeFlag) changeFlag = true;
	for(int x = row - 1 ; x < row + 2 ; x++){
		for(int y = col - 1 ; y < col + 2 ; y++){
			numOfNeighbors += firstAry[x][y];
	}
}
	if(numOfNeighbors < 5) {
		secondAry[row][col] = 1;
		return;
	}
	int topNeighbor = firstAry[row-1][col];
	int bottomNeighbor = firstAry[row+1][col];
	int leftNeighbor = firstAry[row][col-1];
	int rightNeighbor = firstAry[row][col+1];
	int topLeftCorner = firstAry[row-1][col-1];
	int topRightCorner= firstAry[row-1][col+1];
	int bottomLeftCorner= firstAry[row+1][col-1];
	int bottomRightCorner= firstAry[row+1][col+1];
	if((topNeighbor && bottomNeighbor) == 0 || (leftNeighbor && rightNeighbor )== 0){
		secondAry[row][col] = 1;
		return;
	}
	if((topNeighbor && leftNeighbor )== 0   && topLeftCorner|| (topNeighbor && rightNeighbor )== 0 && topRightCorner){
		secondAry[row][col] = 1;
		return;
	}
	if((bottomNeighbor && leftNeighbor )== 0 && bottomLeftCorner|| (bottomNeighbor && rightNeighbor )== 0 && bottomRightCorner){
		secondAry[row][col] = 1;
		return;
	}
	
	secondAry[row][col] = 0;
	
}

void ThinningSkeleton::northThinning(){
	for(int i = 1 ; i < numRows + 1 ; i++){
		for(int x = 1 ; x < numCols + 1 ; x++){
		if(firstAry[i][x] == 1 && firstAry[i-1][x] == 0){
			doThinning(i,x);
		}
	}
	}
}
void ThinningSkeleton::southThinning(){
	for(int i = 1 ; i < numRows + 1 ; i++){
		for(int x = 1 ; x < numCols + 1 ; x++){
		if(firstAry[i][x] == 1 && firstAry[i+1][x] == 0){
			doThinning(i,x);
		}
	}
	}
}
void ThinningSkeleton::westThinning(){
	for(int i = 1 ; i < numRows + 1 ; i++){
		for(int x = 1 ; x < numCols + 1 ; x++){
		if(firstAry[i][x] == 1 && firstAry[i][x-1] == 0){
			doThinning(i,x);
		}
	}
	}
}
void ThinningSkeleton::eastThinning(){
	for(int i = 1 ; i < numRows + 1 ; i++){
		for(int x = 1 ; x < numCols + 1 ; x++){
		if(firstAry[i][x] == 1 && firstAry[i][x+1] == 0){
			doThinning(i,x);
		}
	}
	}
}


void ThinningSkeleton::performThinning(){
	changeFlag = true;
	
	while(changeFlag){
		changeFlag = false;
		cycleCount++;
		northThinning();
		copyAry();
		southThinning();
		copyAry();
		westThinning();
		copyAry();
		eastThinning();
		copyAry();
		
		if(cycleCount % 2 == 0) prettyPrint();
		if(cycleCount % 100 == 0) break;
	
		
	}
	
	cout << "Cycle count is " + cycleCount;
}
void ThinningSkeleton::prettyPrint(){
	for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
    	if(firstAry[i][x] == 0 ){
    		fileWriter2 << " ";
		} else {
			fileWriter2 << firstAry[i][x];
		}
      
    }
    fileWriter2 << endl;
  }
}
int main(int argc , char** argv){
	ThinningSkeleton thinningSkeleton(argv[1] , argv[2] , argv[3]);
	thinningSkeleton.performThinning();
}
