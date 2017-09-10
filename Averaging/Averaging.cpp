#include <fstream>
#include <iostream>
using namespace std;

class Averaging {
 private:
  int numRows, numCols, minVal, maxVal, newMin, newMax;
  int** mirrorFramedAry;
  int** tempAry;
  int neighborAry[9];
  ifstream infile;
  ofstream outfile;

 public:
  Averaging(char* infilename, char* outfilename);
  void mirrorFramed();
  void loadImage();
  void loadNeighbors(int i, int j);
  void print();
  void avg3x3();
};

Averaging::Averaging(char* infilename, char* outfilename) {
  infile.open(infilename);
  outfile.open(outfilename);
  int data;
  newMin = minVal;
  newMax = maxVal;
  for (int i = 0; i < 4; i++) {
    infile >> data;
    switch (i) {
      case 0:
        numRows = data;
        break;
      case 1:
        numCols = data;
        break;
      case 2:
        minVal = data;
        break;
      case 3:
        maxVal = data;
        break;
    }
  }
}
void Averaging::print() {
  for (int i = 0; i < numRows + 2; i++) {
    for (int x = 0; x < numCols + 2; x++) {	
    	if(tempAry[i][x] < 10 ){
    		cout<< "  ";
		} else{
			cout<< " ";
		}
      cout <<tempAry[i][x];
    }
    cout << endl;
  }
  
  for(int i = 0 ; i < 6 ; i++ ){
  	cout<< endl;
  }
}

void ::Averaging::avg3x3() {
  for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      loadNeighbors(i, x);
      int sum = 0;
      for(int y = 0 ; y<9;y++){
      	sum+=neighborAry[y];
	  }
      tempAry[i][x] = sum / 9;
      if (tempAry[i][x] < newMin) {
        newMin = tempAry[i][x];
      } else if (tempAry[i][x] > newMax) {
        newMax = tempAry[i][x];
      }
    }
  }
  
  outfile << numRows << " " << numCols << " " << newMin << " " << newMax;
  outfile << endl;
  for(int i = 1; i < numRows + 1 ; i++){
  	for(int x = 1 ; x < numCols + 1 ; x++){
  		outfile << tempAry[i][x] << " ";
	  }
	  outfile << endl;
  }
}

void Averaging::loadImage() {
  int data;
  mirrorFramedAry = new int*[numRows + 2];
  for (int i = 0; i < numRows + 2; i++) {
    mirrorFramedAry[i] = new int[numCols + 2];
  }

  tempAry = new int*[numRows + 2];
  for (int i = 0; i < numRows + 2; i++) {
    tempAry[i] = new int[numCols + 2];
  }

  for (int i = 0; i < numRows + 2; i++) {
    for (int x = 0; x < numCols + 2; x++) {
      mirrorFramedAry[i][x] = 0;
      tempAry[i][x] = 0;
    }
  }
  for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      infile >> data;
      mirrorFramedAry[i][x] = data;
    }
  }
}

void Averaging::mirrorFramed() {
  for (int i = 1; i < numCols + 1; i++) {
    mirrorFramedAry[0][i] = mirrorFramedAry[1][i];
    mirrorFramedAry[numRows + 1][i] = mirrorFramedAry[numRows][i];
  }

  for (int i = 0; i < numRows + 2; i++) {
    mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
    mirrorFramedAry[i][numCols + 1] = mirrorFramedAry[i][numCols];
  }

  print();
}

void Averaging::loadNeighbors(int i, int j) {
  int leftMostI = i - 1;
  int leftMostJ = j - 1;
  int currentIndex = 0;
  for (int x = leftMostI; x < leftMostI + 3; x++) {
    for (int y = leftMostJ; y < leftMostJ + 3; y++) {
      neighborAry[currentIndex] = mirrorFramedAry[x][y];
      currentIndex++;
    }
  }
}

int main(int argc, char* argv[]) {
  Averaging averaging(argv[1], argv[2]);
  averaging.loadImage();
  averaging.mirrorFramed();
  averaging.avg3x3();
  averaging.print();
}
