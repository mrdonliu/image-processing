#include <fstream>
#include <iostream>
#include <string>
using namespace std;
struct Property{
			int label, numbPixels, minRow, minCol, maxRow, maxCol;
			void setLabel(int l);
			void incrementPixels();
			void checkBounds(int i , int j );
			Property();
			int getMaxRows();
			int getMinCols();
			int getMaxCols();
			int getMinRows();
			int getNumbPixels();
		};
		
class ConnectComponent{
	private:
		int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel;
		int** zeroFramedAry;
		int neighborAry[9];
		int* eqAry;
		ifstream infile;
		ofstream outfile , outfile2 , outfile3;
		Property* components;
		
		
		public:
			ConnectComponent(char* infilename , char* outfilename, char* outfilename2 , char* outfilename3);
			~ConnectComponent();
			void zeroFrame();
			void loadImage();
			void loadNeighbors(int i, int j);
			void connectCC_pass1();
			void connectCC_pass2();
			void connectCC_pass3();
			void updateEqAry();
			void manageEqAry();
			void printCcProperty();
			void prettyPrint(int pass);
			void print(string message);
			void print2();
};

ConnectComponent::ConnectComponent(char* infilename , char* outfilename , char* outfilename2 , char* outfilename3){
	infile.open(infilename);
	outfile.open(outfilename);
	outfile2.open(outfilename2);
	outfile3.open(outfilename3);
	int data =0;
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
  newLabel = 0;
  zeroFramedAry = new int*[numRows+2];
  for(int i = 0; i < numRows+2; i++){
  	zeroFramedAry[i] = new int[numCols+2];
  }
  
  eqAry = new int[(numRows*numCols )/ 4];
  for(int i = 0 ; i < (numRows*numCols )/ 4 ; i++ ){
  	eqAry[i] = i;
  }
  
}

ConnectComponent::~ConnectComponent(){
		for(int i = 0 ; i < numRows  +2 ; i++ ){
			delete[] zeroFramedAry[i];
		}
		delete[] zeroFramedAry;
		
		delete[] eqAry;
		delete[] components;
		infile.close();
		outfile.close();
		outfile2.close();
}

void ConnectComponent::loadImage() {
  int data=0;
  

  for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      infile >> data;
      zeroFramedAry[i][x] = data;
    }
  }
}


Property::Property(){
	numbPixels = 0;
	maxRow = -1;
	maxCol = -1;
	minRow = 2147483647;
	minCol = 2147483647;
}
int Property::getNumbPixels(){
	return numbPixels;
}
void Property::setLabel(int l){
	label = l;
	}
void Property::incrementPixels(){
	numbPixels++;
}

int Property::getMaxRows(){
	return maxRow;
}

int Property::getMinRows(){
	return minRow;
}
int Property::getMaxCols(){
	return maxCol;
}

int Property::getMinCols(){
	return minCol;
}
void Property::checkBounds(int i , int j ){
	if( i < minRow ){
		minRow = i;
	}
	if( i > maxRow ){
		maxRow = i;
	}
	
	if( j < minCol ){
		minCol = j;
	}
	if(j > maxCol ){
		maxCol = j;
	}
}
void ConnectComponent::loadNeighbors(int i, int j){
int leftMostI = i - 1;
  int leftMostJ = j - 1;
  int currentIndex = 0;
  for (int x = leftMostI; x < leftMostI + 3; x++) {
    for (int y = leftMostJ; y < leftMostJ + 3; y++) {
      neighborAry[currentIndex] = zeroFramedAry[x][y];
      currentIndex++;
    }
  }
  
}

void ConnectComponent::connectCC_pass1(){
	for(int i = 1; i < numRows + 1 ; i++){
		for(int x = 1; x < numCols + 1 ; x++ ){
			if(zeroFramedAry[i][x] > 0){
			
			loadNeighbors(i,x);
			int topNeighbor = neighborAry[1];
			int leftNeighbor = neighborAry[3];
			if(topNeighbor == leftNeighbor){
				if(topNeighbor == 0){
					zeroFramedAry[i][x] = ++newLabel;
				} else {
					zeroFramedAry[i][x] = topNeighbor;
				}
			} else{
				if(topNeighbor == 0 ){
					zeroFramedAry[i][x] = leftNeighbor;
				}
				else if(leftNeighbor == 0){
					zeroFramedAry[i][x] = topNeighbor;

				} else{
					zeroFramedAry[i][x] = min(topNeighbor,leftNeighbor);
					eqAry[topNeighbor] = zeroFramedAry[i][x];
					eqAry[leftNeighbor] = zeroFramedAry[i][x];
					
				}
				
			}
		}
	}
	}
	

}

void ConnectComponent::connectCC_pass2(){
	int temp;
	for(int i = numRows ; i > 0; i--){
		for(int x = numCols; x > 0 ; x-- ){
			if(zeroFramedAry[i][x] > 0){
			loadNeighbors(i,x);
			int rightNeighbor = neighborAry[5];
			int bottomNeighbor = neighborAry[7];
			if(rightNeighbor == bottomNeighbor && rightNeighbor== 0){
				continue;
			}
			else if(rightNeighbor == 0 || bottomNeighbor == 0){
				if(zeroFramedAry[i][x] == rightNeighbor || zeroFramedAry[i][x] == bottomNeighbor){
					continue;
				}
			}
			
			if( rightNeighbor != bottomNeighbor){
				if(rightNeighbor == 0){
					temp = min(bottomNeighbor, zeroFramedAry[i][x]);
					eqAry[bottomNeighbor] = temp;
					eqAry[zeroFramedAry[i][x]] = temp;
					zeroFramedAry[i][x] = temp;
				} 
				else if( bottomNeighbor == 0 ){
					temp = min(rightNeighbor, zeroFramedAry[i][x]);
					eqAry[rightNeighbor] = temp;
					eqAry[zeroFramedAry[i][x]] = temp;
					zeroFramedAry[i][x] = temp;
				} else{
					temp = min(rightNeighbor, bottomNeighbor);
					temp = min(temp, zeroFramedAry[i][x]);
					eqAry[rightNeighbor] = temp;
					eqAry[zeroFramedAry[i][x]] = temp;
					eqAry[bottomNeighbor] = temp;
					zeroFramedAry[i][x] = temp;
					
					
					
				}
			} else{
				if(rightNeighbor != 0 ){
					temp = min(rightNeighbor, bottomNeighbor);
					temp = min(temp, zeroFramedAry[i][x]);
					eqAry[rightNeighbor] = temp;
					eqAry[zeroFramedAry[i][x]] = temp;
					eqAry[bottomNeighbor] = temp;
					zeroFramedAry[i][x] = temp;
				}
			}
		}
		}
	}
	
}
void ConnectComponent::connectCC_pass3(){
	components = new Property[newLabel+1];
	for(int i = 1 ; i <= newLabel ; i++ ){
		components[i].setLabel(i);
	}
	for(int i = 1; i < numRows + 1 ; i++){
		for(int x = 1 ; x < numCols + 1 ; x++){
			if(zeroFramedAry[i][x] > 0){
				zeroFramedAry[i][x] = eqAry[zeroFramedAry[i][x]];
   			    components[zeroFramedAry[i][x]].incrementPixels();
				components[zeroFramedAry[i][x]].checkBounds(i,x);


				
			}
		}
	}	
	

}
void ConnectComponent::updateEqAry(){
	
}
void ConnectComponent::manageEqAry(){
	int trueLabel = 0;
	int index = 1;
	while( index <= newLabel ){
		if(eqAry[index] == index){
			trueLabel++;
			eqAry[index] = trueLabel;
		} else {
			eqAry[index] = eqAry[eqAry[index]];
		}
		
		index++;
	}
	
	newLabel = trueLabel;
	cout << "newLabel is " << newLabel;
	
}
void ConnectComponent::printCcProperty(){
	outfile3 << numRows << " " << numCols << " " << minVal << " " << maxVal;
	outfile3 << newLabel << endl;
	for(int i = 1 ; i <= newLabel ; i++ ){
		outfile3 << i << endl;
		outfile3 << components[i].getNumbPixels() << endl;
		outfile3 << components[i].getMinRows() << " " << components[i].getMinCols() << endl;
		outfile3 << components[i].getMaxRows() << " " << components[i].getMaxCols() << endl;
		outfile3 << endl;
	}
	
}

void ConnectComponent::print(string message){
	outfile << message << endl;
	outfile << "eqAry: (Index:Value) " << endl;
	
	for(int i = 0; i < (numRows*numCols )/ 4 ; i++ ){
		outfile << i << ":" << eqAry[i] << "  ";
		if(i%10 == 0){
			outfile<<endl;
		}
	}

}

void ConnectComponent::zeroFrame(){
	for(int i = 0; i < numCols + 2 ; i++){
		zeroFramedAry[0][i] = 0;
		zeroFramedAry[numRows+1][i] = 0;

	}
	
	for(int i = 0; i < numRows + 2 ; i++){
		zeroFramedAry[i][0] = 0;
		zeroFramedAry[i][numCols+1] = 0;

	}
}


void ConnectComponent::prettyPrint(int pass ){
	
	switch(pass){
		case 1: 
		outfile << "Pass 1:" << endl;
		break;
		case 2: 
		outfile << "Pass 2:" << endl;
		break;
		case 3: 
		outfile << "Pass 3:" << endl;
		break;
	}

	for( int i = 0 ; i<numRows+2 ; i++){
		for( int x = 0; x < numCols+2; x++){
			
			if( zeroFramedAry[i][x] != 0 ){
				outfile << zeroFramedAry[i][x];

			} else {
				outfile << ' ';
			}
			
			
			if(zeroFramedAry[i][x] < 10 ){
					outfile << "  ";
				} else {
					outfile << " ";
				}
		}
		outfile << endl;
	}
	
	print("");
	
	outfile << endl << endl << endl;
}

void ConnectComponent::print2(){
	outfile2 << numRows << " " << numCols << " " << 0 << " " << newLabel;
	outfile2 << endl;
	for(int i = 1 ; i < numRows + 1 ; i++ ){
		for( int x = 1 ; x < numCols ; x++ ){
			outfile2 << zeroFramedAry[i][x] << " ";
		}
		outfile2 << endl;
	} 
}
int main(int argc , char* argv[]){
	
	ConnectComponent cc(argv[1] , argv[2] , argv[3] , argv[4]);
	cc.loadImage();
	cc.zeroFrame();
	cc.connectCC_pass1();
	cc.prettyPrint(1);
	cc.connectCC_pass2();
	cc.prettyPrint(2);
	cc.manageEqAry();
	cc.print("After managing eqAry");
	cc.connectCC_pass3();
	cc.prettyPrint(3);
	cc.printCcProperty();
	cc.print2();
	
}
