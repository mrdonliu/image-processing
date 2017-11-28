#include <iostream>
#include <fstream>

class MorphologyOperations{
	public:
		MorphologyOperations(const char* , const char* );
		MorphologyOperations(const char* , const char* , const char*,
							 const char* , const char* , const char*);
		void computeFrameSize();
		void loadImage();
		void loadStruct();
		void zeroFrameImage();
		void dilation(const int , const int);
		void erosion(const int , const int);
		void opening(const int , const int);
		void closing(const int , const int);
		void prettyPrint();
		void outputResult();
	private:
		int numRowsImg , numColsImg;
		int numRowsStrctElem , numColsStrctElem;
		int rowOrigin , colOrigin;
		int rowFrameSize , colFrameSize;
		int** imgAry;
		int** morphAry;
		int** structElem;
		ifstream imgFileReader , strctElemFileReader;
		ofstream dilationOutputFileWriter , erosionOutputFileWriter , openingOutputFileWriter , closingnOutputFileWriter;
		
		
		
};

MorphologyOperations::MorphologyOperations(const char* imgFile , const char* strctElemFile , const char* dilationOutputFile ,
							 			   const char* erosionOutputFile, const char* openingOutputFile, const char* closingnOutputFile){
							 	imgFileReader.open(imgFile);
							 	strctElemFileReader.open(strctElemFile);
							 	dilationOutputFileWriter.open(dilationOutputFile);
							 	
							 }

int main(int argc , char** argv){
	
}
