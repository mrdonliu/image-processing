//
//  main.cpp
//  ChainCode
//
//  Created by don liu on 10/22/17.
//  Copyright © 2017 don liu. All rights reserved.
//

#include <iostream>
using namespace std;
#include <fstream>
#include <string>
class Image{
    public:
        Image(char* infile, char* infile1 , char* outfile , char* outfile1);
        ~Image();
        void zeroFramed();
        void loadImage();

    private:
        int numRows, numCols, minVal, maxVal;
        int** imageAry;
        int** CCAry;
        ifstream infile, infile1;
    	ofstream outfile, outfile1;
    	
    
};


Image::Image(char* infilename, char* infilename1 , char* outfilename , char* outfilename1 ){
    infile.open(infilename);
    infile1.open(infilename1);
    outfile.open(outfilename);
    outfile1.open(outfilename1);
    imageAry = new int*[numRows+2];
    CCAry = new int*[numRows+2];
    
    int data;
    for(int i = 0; i < numRows; i++ ){
        imageAry[i] = new int[numCols+2];
        CCAry[i] = new int[numCols+2];
    }
    
    for(int i = 0 ; i < 4; i++ ){
    	infile >> data;
    	switch(i){
    		case 0:
    			numRows=data;
    			break;
    		case 1:
    			numCols=data;
    			break;
    		case 2:
    			minVal=data;
    			break;
    		case 3:
    			maxVal=data;
    			break;
		}
	}
	
	outfile << numRows << " " << numCols << " " << minVal << " " << maxVal;
	outfile1 << numRows << " " << numCols << " " << minVal << " " << maxVal;
	
	
//	int label, numbPixels, minBoundingRow, minBoundingCol, maxBoundingRow, maxBoundingCol;
//	while(!outfile1.eof()){
//		for(int i = 0 ; i < 6 ; i++){
//		infile1 >> data;
//		switch(i){
//				case 0:
//					label = data;
//					break;
//				case 1:
//					numbPixels = data;
//					break;	
//				case 2:
//					minBoundingRow = data;
//					break;
//				case 3:
//					minBoundingCol = data;
//					break;
//				case 4:
//					maxBoundingRow = data;
//					break;
//				case 5:
//					maxBoundingCol = data;
//					break;	
//			}
//		}
//		
//		
//	}
	
    
}

Image::~Image(){
	infile.close();
	infile1.close();
	outfile.close();
	outfile1.close();
}

void Image::zeroFramed(){
    for(int i = 0; i < numCols + 2 ; i++){
        imageAry[0][i] = 0;
        imageAry[numRows+1][i] = 0;
        CCAry[0][i] = 0;
        CCAry[numRows+1][i] = 0;
    }
    
    for(int i = 0; i < numRows + 2 ; i++){
        imageAry[i][0] = 0;
        imageAry[i][numCols+1] = 0;
        CCAry[i][0] = 0;
        CCAry[i][numCols+1] = 0;
        
    }
}

void Image::loadImage(){
	int data=0;
  

  for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      infile >> data;
      CCAry[i][x] = data;
      imageAry[i][x] = data;
    }
  }
}


class ConnectCC{
public:
    ConnectCC(int numPixel, int minRow, int minCol, int maxRow, int maxCol);
    void loadCC(int theLabel, int** ccAry, int** imageAry, int numRow, int numCol);
    void getBoundingBox(int& minRow, int& minCol , int& maxRow , int& maxCol);
    
private:
    int label, numbPixels;
	int minBoundingRow, minBoundingCol, maxBoundingRow, maxBoundingCol;
    
    
};

ConnectCC::ConnectCC(int numPixel, int minRow, int minCol, int maxRow, int maxCol){

	numbPixels = numPixel;
	minBoundingRow = minRow;
	minBoundingCol = minCol;
	maxBoundingRow = maxRow;
	maxBoundingCol = maxCol;
}
void ConnectCC::loadCC(int theLabel, int** ccAry, int** imageAry, int numRow, int numCol){
	
	label = theLabel;
	for(int i = 1; i <= numRow ; i++){
		for(int x = 1; x <= numCol ; x++ ){
			if(imageAry[i][x] == label){
				ccAry[i][x] = label;
			} else {
				ccAry[i][x] = 0;
			}
		}
	}
}

void ConnectCC::getBoundingBox(int& minRow, int& minCol , int& maxRow , int& maxCol){
	minRow = minBoundingRow;
	minCol = minBoundingCol;
	maxRow = maxBoundingRow;
	maxCol = maxBoundingCol;
}

class ChainCode{
public:
    ChainCode();
    void loadNeighborsCoord();
    void findNextP();
    void prettyPrint();
    void getChainCode();
    void getChainCode(ConnectCC cc , int** ccAry);
private:
    class Point{
    public:
        int row, col;
        Point(int therow, int thecol){
            row = therow;
            col = thecol;
        }
    };
    
    Point neighborCoord[8];
    Point currentP, nextP;
    int lastQ;
    int nextDirTable[8];
    int nextDir;
    int pChainDir;
    
};

void ChainCode::getChainCode(ConnectCC cc , int** ccAry){
	int minBoundingRow, minBoundingCol, maxBoundingRow, maxBoundingCol;
    
	cc.getBoundingBox(minBoundingRow, minBoundingCol, maxBoundingRow, maxBoundingCol);
	
	for(int i = minBoundingRow ; i <= maxBoundingRow ; i++){
		for(int x = minBoundingCol ; x <= maxBoundingCol ; x++ ){
			if(ccAry[i][x] > 0 ){
				
			}
		}
	}
}

int main(int argc,  char * argv[]) {
    
    Image img(argv[1] , argv[2] , argv[3] , argv[4] );
    
	
	
    
    
}
