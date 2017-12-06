#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
using namespace std;

//imagePP class
class imagePP{
    friend class BBBox;
private:
    int numRows , numCols , minVal , maxVal;
    int** imgAry;
    int* HPP , HPPbin , VPP , VPPbin;
    int threshVal;
    ifstream infile;
    ofstream outfile;
    
public:
    void loadImage();
    void computeHPP(BBBox::boxNode box);
    void computeVPP(BBBox::boxNode box);
    void threshold();
    void printPP();
    imagePP(char* imgFilename , int threshold , char* outfilename );
    
};

imagePP::imagePP(char* imgFilename , int threshold , char* outfilename ){
    infile.open(imgFilename);
    outfile.open(outfilename);
    int data =0;
    threshVal = threshold;
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

void::imagePP::loadImage() {
    int data=0;
    
    
    for (int i = 1; i < numRows + 1; i++) {
        for (int x = 1; x < numCols + 1; x++) {
            infile >> data;
            imgAry[i][x] = data;
        }
    }
}

//BBBox class

class BBBox{
    imagePP img;
    
    public:
    struct boxNode{
        int topLeftX , topLeftY , bottomRightX , bottomRightY;
        int type;
        ofstream* outfile;
        
        boxNode* nextBox;
        
        boxNode(ofstream* outFile){
            outfile = outFile;
            topLeftX = INT_MAX;
            topLeftY = INT_MAX;
            bottomRightX = 0;
            bottomRightY = 0;
        }
        
        void updateBox(int row , int col){
            if(row < topLeftX){
                topLeftX = row;
            }
            if(col < topLeftY){
                topLeftY = col;
            }
            if(row > bottomRightX ){
                bottomRightX = row;
            }
            if(col > bottomRightY){
                bottomRightY = col;
            }
            
        }
        
        void print(){
            *outfile << topLeftX << " "<< topLeftY << " "<< bottomRightX << " "<< bottomRightY << " ";
        }
        
    };
    
    class BoxList{
        boxNode* listHead;
        boxNode* last;
    };
    
        void insert(BoxList* boxList , boxNode* box);
        boxNode* findImageBox();
        
  ;
};

BBBox::boxNode* BBBox::findImageBox(){
    boxNode boxnode(&img.outfile);
    boxNode* box = &boxnode;
    for(int i = 0 ; i < img.numRows ; i++){
        for(int x = 0; x < img.numCols ; x++){
            int val =img.imgAry[i][x];
            if(val > 0){
                box->updateBox(i,x);
            }
        }
    }
    
    return box;
}





int main(int argc , char** argv)
{
    int threshold = atoi(argv[2]);
    imagePP img(argv[1] , threshold , argv[3] );
    img.loadImage();
    return 0;
}

