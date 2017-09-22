#include <fstream>
#include <iostream>
using namespace std;
struct Property{
			int label, numbPixels, minRow, minCol, maxRow, maxCol;
			void setLabel(int l);
			void incrementPixels();
			void checkBounds(int i , int j );
			Property();
		};
		
class ConnectComponent{
	private:
		int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel;
		int** zeroFramedAry;
		int neighborAry[9];
		int* eqAry;
		ifstream infile;
		ofstream outfile;
		Property* components;
		
		
		public:
			ConnectComponent(char* infilename , char* outfilename);
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
			void prettyPrint();
			void print();
};

ConnectComponent::ConnectComponent(char* infilename , char* outfilename){
	infile.open(infilename);
	outfile.open(outfilename);
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
}

void ConnectComponent::loadImage() {
  int data=0;
  

  for (int i = 1; i < numRows + 1; i++) {
    for (int x = 1; x < numCols + 1; x++) {
      infile >> data;
      //zeroFramedAry[i][x] = data;
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

void Property::setLabel(int l){
	label = l;
	}
void Property::incrementPixels(){
	numbPixels++;
}

void Property::checkBounds(int i , int j ){
	if( i < minRow ){
		minRow = i;
	}
	else if( i > maxRow ){
		i = maxRow;
	}
	
	if( j < minCol ){
		minCol = j;
	}
	else if(j > maxCol ){
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
	
	for(int x = 0; x < (numRows*numCols)/4;x++){
		cout<< x << ":" << eqAry[x] << endl;
	}
	
	manageEqAry();
}
void ConnectComponent::connectCC_pass3(){
	components = new Property[newLabel];
	for(int i = 1 ; i <= newLabel ; i++ ){
		components[i].setLabel(1);
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
	outfile << numRows << " " << numCols << " " << minVal << " " << maxVal;
	
}

void ConnectComponent::print(){
	for(int i = 0 ; i < numRows + 2; i++){
		for(int x = 0; x < numCols + 2; x++){
			cout << zeroFramedAry[i][x];
			if( zeroFramedAry[i][x] < 10 ){
				cout << "  ";
			} else{
				cout << " ";
			}
		}
		cout<<endl;
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


void ConnectComponent::prettyPrint(){

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
}

int main(int argc , char* argv[]){
	
	ConnectComponent cc(argv[1] , argv[2]);
	cc.loadImage();
//	cc.zeroFrame();
//	cc.connectCC_pass1();
//	cc.connectCC_pass2();
//	cc.connectCC_pass3();
//	cc.prettyPrint();
//	cc.print();
//	cc.printCcProperty();
	
}
