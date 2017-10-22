//
//  main.cpp
//  ChainCode
//
//  Created by don liu on 10/22/17.
//  Copyright © 2017 don liu. All rights reserved.
//

#include <iostream>
using namespace std;

class Image{
    public:
        Image(int rows, int cols, int min, int max);
        void zeroFramed();
        void loadImage();

    private:
        int numRows, numCols, minVal, maxVal;
        int** imageAry;
        int** CCAry;
    
};


Image::Image(int rows, int cols, int min, int max){
    numRows = rows;
    numCols = cols;
    minVal = min;
    maxVal = max;
    imageAry = new int*[numRows+2];
    CCAry = new int*[numRows+2];
    
    for(int i = 0; i < numRows; i++ ){
        imageAry[i] = new int[numCols+2];
        CCAry[i] = new int[numCols+2];
    }

    
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

class ConnectCC{
public:
    ConnectCC();
    void loadCC();
    
private:
    int label, numbPixels, numRows, numCols, minRow, minCol;
    
    
};

class ChainCode{
public:
    ChainCode();
    void loadNeighborsCoord();
    void findNextP();
    void prettyPrint();
    void getChainCode();
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


int main(int argc, const char * argv[]) {
    ifstream infile;
    ofstream outfile;
    
    
}
