#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class PrettyPrint{
	private:
		int numRows , numCols , minVal , maxVal;
		ifstream infile;
		ofstream outfile;
		string outfilename;
	public:
		PrettyPrint(char* infilename);
		~PrettyPrint();
		void prettyPrint();
};

PrettyPrint::PrettyPrint(char* infilename){
	infile.open(infilename);
	int data;
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
  
  const char* s = infilename;
  string str(s);
  size_t lastindex = str.find_last_of("."); 
  string rawname = str.substr(0, lastindex); 
  outfilename = str + "_PP.txt";
  outfile.open(outfilename);
}

PrettyPrint::~PrettyPrint(){
	outfile.close();
	infile.close();
}

void PrettyPrint::prettyPrint(){
	int data;
	for( int i = 0 ; i<numRows ; i++){
		for( int x = 0; x < numCols; x++){
			infile >> data;
			if( data != 0 ){
				outfile << data;
			} else {
				outfile << ' ';
			}
			
			outfile << ' ';
		}
		outfile << endl;
	}
}

int main(int argc , char* argv[]){
	PrettyPrint prettyprint(argv[1]);
	prettyprint.prettyPrint();
}
