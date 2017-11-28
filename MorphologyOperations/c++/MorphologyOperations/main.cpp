#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
class MorphologyOperations {
 public:
  MorphologyOperations(const char*, const char*, const char*);
  MorphologyOperations(const char*, const char*, const char*, const char*,
                       const char*, const char*);

  void computeFrameSize(const int, const int);
  void loadImage();
  void loadStruct();
  void zeroFrameImage();
  void dilation();
  void erosion();
  void opening();
  void closing();

  void performOperation();

  void resetMorphAry();
  void prettyPrint(std::string, std::string);

  void outputResult(std::string);

 private:
     std::string operation;
  int numRowsImg, numColsImg;
  int counter;
  int sizeOfRowsWithFrame, sizeOfColsWithFrame;
  int numRowsStrctElem, numColsStrctElem;
  int rowOrigin, colOrigin;
  int rowFrameSize, colFrameSize;
  int minValImg, maxValImg;
  int minValStrctElem, maxValStrctElem;
  int** imgAry;
  int** morphAry;
  int** morphAry2;
  int** structElem;
  std::ifstream imgFileReader, strctElemFileReader;
  std::ofstream dilationOutputFileWriter, erosionOutputFileWriter,
      openingOutputFileWriter, closingOutputFileWriter;
  void prettyPrint(int**, int, int, std::string);
};

MorphologyOperations::MorphologyOperations(const char* imgFile,
                                           const char* strctElemFile,
                                           const char* dilationOutputFile,
                                           const char* erosionOutputFile,
                                           const char* openingOutputFile,
                                           const char* closingOutputFile) {
  imgFileReader.open(imgFile);
  strctElemFileReader.open(strctElemFile);
  dilationOutputFileWriter.open(dilationOutputFile);
  erosionOutputFileWriter.open(erosionOutputFile);
  openingOutputFileWriter.open(openingOutputFile);
  closingOutputFileWriter.open(closingOutputFile);

  for (int i = 0; i < 4; i++) {
    imgFileReader >> counter;
    switch (i) {
      case 0:
        numRowsImg = counter;
        break;
      case 1:
        numColsImg = counter;
        break;
      case 2:
        minValImg = counter;
        break;
      case 3:
        maxValImg = counter;
        break;
    }
  }

  for (int i = 0; i < 6; i++) {
    strctElemFileReader >> counter;
    switch (i) {
      case 0:
        numRowsStrctElem = counter;
        rowFrameSize = numRowsStrctElem;
        break;
      case 1:
        numColsStrctElem = counter;
        colFrameSize = numColsStrctElem;
        break;
      case 2:
        minValStrctElem = counter;
        break;
      case 3:
        maxValStrctElem = counter;
        break;
      case 4:
        rowOrigin = counter;
        break;
      case 5:
        colOrigin = counter;
        break;
    }
  }

  sizeOfRowsWithFrame = numRowsImg + rowFrameSize;

  sizeOfColsWithFrame = numColsImg + colFrameSize;

  imgAry = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    imgAry[i] = new int[sizeOfColsWithFrame];
  }

  morphAry = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    morphAry[i] = new int[sizeOfColsWithFrame];
  }

  morphAry2 = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    morphAry2[i] = new int[sizeOfColsWithFrame];
  }

  structElem = new int*[numRowsStrctElem];
  for (int i = 0; i < numRowsStrctElem; i++) {
    structElem[i] = new int[numColsStrctElem];
  }
}



MorphologyOperations::MorphologyOperations(const char* imgFile , const char* strctElemFile , const char* nameOfOperation) {
  imgFileReader.open(imgFile);
  strctElemFileReader.open(strctElemFile);
  operation = std::string(nameOfOperation);

  for (int i = 0; i < 4; i++) {
    imgFileReader >> counter;
    switch (i) {
      case 0:
        numRowsImg = counter;
        break;
      case 1:
        numColsImg = counter;
        break;
      case 2:
        minValImg = counter;
        break;
      case 3:
        maxValImg = counter;
        break;
    }
  }

  for (int i = 0; i < 6; i++) {
    strctElemFileReader >> counter;
    switch (i) {
      case 0:
        numRowsStrctElem = counter;
        rowFrameSize = numRowsStrctElem;
        break;
      case 1:
        numColsStrctElem = counter;
        colFrameSize = numColsStrctElem;
        break;
      case 2:
        minValStrctElem = counter;
        break;
      case 3:
        maxValStrctElem = counter;
        break;
      case 4:
        rowOrigin = counter;
        break;
      case 5:
        colOrigin = counter;
        break;
    }
  }

  sizeOfRowsWithFrame = numRowsImg + rowFrameSize;

  sizeOfColsWithFrame = numColsImg + colFrameSize;

  imgAry = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    imgAry[i] = new int[sizeOfColsWithFrame];
  }

  morphAry = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    morphAry[i] = new int[sizeOfColsWithFrame];
  }

  morphAry2 = new int*[sizeOfRowsWithFrame];
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    morphAry2[i] = new int[sizeOfColsWithFrame];
  }

  structElem = new int*[numRowsStrctElem];
  for (int i = 0; i < numRowsStrctElem; i++) {
    structElem[i] = new int[numColsStrctElem];
  }
}

void MorphologyOperations::performOperation(){

    std::string lowerCaseOperation;
    for(int i = 0 ; i < operation.length() ; i++){
        lowerCaseOperation += tolower(operation[i]);
        std::cout  << lowerCaseOperation;
    }

    if(lowerCaseOperation == "d" ){
        dilation();
        prettyPrint("morphAry" , "Output from dilation");
    }
    else if(lowerCaseOperation == "e" ){
        erosion();
        prettyPrint("morphAry" , "Output from erosion");
    }
    else if(lowerCaseOperation == "o" ){
        opening();
        prettyPrint("morphAry" , "Output from opening");
    }
    else if(lowerCaseOperation == "c" ){
        closing();
        prettyPrint("morphAry" , "Output from closing");
    }
    else{
        std::cout << "Arguments can only be d for dilation , e for erosion , o for opening , and c for closing";
    }
  }

void MorphologyOperations::loadImage() {
  for (int i = rowFrameSize / 2; i < rowFrameSize / 2 + numRowsImg; i++) {
    for (int x = colFrameSize / 2; x < (colFrameSize / 2) + numColsImg; x++) {
      imgFileReader >> counter;
      imgAry[i][x] = counter;
    }
  }
}

void MorphologyOperations::loadStruct() {
  for (int i = 0; i < numRowsStrctElem; i++) {
    for (int x = 0; x < numColsStrctElem; x++) {
      strctElemFileReader >> counter;
      structElem[i][x] = counter;
    }
  }
}

void MorphologyOperations::zeroFrameImage() {
  for (int i = 0; i < rowFrameSize / 2; i++) {
    for (int x = 0; x < sizeOfColsWithFrame; x++) {
      imgAry[i][x] = 0;
    }
  }

  for (int i = rowFrameSize / 2 + numRowsImg; i < sizeOfRowsWithFrame; i++) {
    for (int x = 0; x < sizeOfColsWithFrame; x++) {
      imgAry[i][x] = 0;
    }
  }

  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    for (int x = 0; x < colFrameSize / 2; x++) {
      imgAry[i][x] = 0;
    }
  }

  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    for (int x = (colFrameSize / 2) + numColsImg; x < sizeOfColsWithFrame;
         x++) {
      imgAry[i][x] = 0;
    }
  }
}

void MorphologyOperations::dilation() {
  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (imgAry[i][x] > 0) {
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            morphAry[j][n] = 1;
          }
        }
      }
    }
  }
}

void MorphologyOperations::erosion() {
  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (imgAry[i][x] > 0) {
        bool allOnes = true;
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            if (imgAry[j][n] == 0) {
              morphAry[i][x] = 0;
              allOnes = false;
              j = (i - rowOrigin) + numRowsStrctElem;
              n = (x - colOrigin) + numColsStrctElem;
            }
          }
        }
        if (allOnes) {
          morphAry[i][x] = 1;
        }
      }
    }
  }
}

void MorphologyOperations::opening() {
  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (imgAry[i][x] > 0) {
        bool allOnes = true;
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            if (imgAry[j][n] == 0) {
              morphAry2[i][x] = 0;
              allOnes = false;
              j = (i - rowOrigin) + numRowsStrctElem;
              n = (x - colOrigin) + numColsStrctElem;
            }
          }
        }
        if (allOnes) {
          morphAry2[i][x] = 1;
        }
      }
    }
  }

  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (morphAry2[i][x] > 0) {
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            morphAry[j][n] = 1;
          }
        }
      }
    }
  }
}

void MorphologyOperations::closing() {
  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (imgAry[i][x] > 0) {
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            morphAry2[j][n] = 1;
          }
        }
      }
    }
  }

  for (int i = rowFrameSize / 2; i < sizeOfRowsWithFrame; i++) {
    for (int x = colFrameSize / 2; x < sizeOfColsWithFrame; x++) {
      if (morphAry2[i][x] > 0) {
        bool allOnes = true;
        for (int j = i - rowOrigin; j < (i - rowOrigin) + numRowsStrctElem;
             j++) {
          for (int n = x - colOrigin; n < (x - colOrigin) + numColsStrctElem;
               n++) {
            if (morphAry2[j][n] == 0) {
              morphAry[i][x] = 0;
              allOnes = false;
              j = (i - rowOrigin) + numRowsStrctElem;
              n = (x - colOrigin) + numColsStrctElem;
            }
          }
        }
        if (allOnes) {
          morphAry[i][x] = 1;
        }
      }
    }
  }
}

void MorphologyOperations::prettyPrint(int** ary, int numRows, int numCols,
                                       std::string msg) {
  std::cout << std::endl;
  std::cout << msg << ":" << std::endl << std::endl;
  for (int i = 0; i < numRows; i++) {
    for (int x = 0; x < numCols; x++) {
      if (ary[i][x] > 0) {
        std::cout << ary[i][x] << " ";
      } else {
        std::cout << "  ";
      }
    }

    std::cout << std::endl;
  }
}

void MorphologyOperations::prettyPrint(std::string aryName, std::string msg) {
  if (aryName == "imgAry") {
    prettyPrint(imgAry, sizeOfRowsWithFrame, sizeOfColsWithFrame, msg);
  } else if (aryName == "structAry") {
    prettyPrint(structElem, numRowsStrctElem, numColsStrctElem, msg);
  }
  if (aryName == "morphAry") {
    prettyPrint(morphAry, sizeOfRowsWithFrame, sizeOfColsWithFrame, msg);
  }
}

void MorphologyOperations::outputResult(std::string operation) {
  if (operation == "dilation") {
    for (int i = 0; i < sizeOfRowsWithFrame; i++) {
      for (int x = 0; x < sizeOfColsWithFrame; x++) {
        if (morphAry[i][x] > 0) {
          dilationOutputFileWriter << morphAry[i][x] << " ";
        } else {
          dilationOutputFileWriter << "  ";
        }
      }

      dilationOutputFileWriter << std::endl;
    }
  }
  if (operation == "erosion") {
    for (int i = 0; i < sizeOfRowsWithFrame; i++) {
      for (int x = 0; x < sizeOfColsWithFrame; x++) {
        if (morphAry[i][x] > 0) {
          erosionOutputFileWriter << morphAry[i][x] << " ";
        } else {
          erosionOutputFileWriter << "  ";
        }
      }

      erosionOutputFileWriter << std::endl;
    }
  }
  if (operation == "closing") {
    for (int i = 0; i < sizeOfRowsWithFrame; i++) {
      for (int x = 0; x < sizeOfColsWithFrame; x++) {
        if (morphAry[i][x] > 0) {
          closingOutputFileWriter << morphAry[i][x] << " ";
        } else {
          closingOutputFileWriter << "  ";
        }
      }

      closingOutputFileWriter << std::endl;
    }
  }
  if (operation == "opening") {
    for (int i = 0; i < sizeOfRowsWithFrame; i++) {
      for (int x = 0; x < sizeOfColsWithFrame; x++) {
        if (morphAry[i][x] > 0) {
          openingOutputFileWriter << morphAry[i][x] << " ";
        } else {
          openingOutputFileWriter << "  ";
        }
      }

      openingOutputFileWriter << std::endl;
    }
  }
}

void MorphologyOperations::resetMorphAry() {
  for (int i = 0; i < sizeOfRowsWithFrame; i++) {
    for (int x = 0; x < sizeOfColsWithFrame; x++) {
      morphAry[i][x] = 0;
      morphAry2[i][x] = 0;
    }
  }
}
int main(int argc, char** argv) {
  MorphologyOperations morphologyOperations(argv[1], argv[2], argv[3]);

morphologyOperations.resetMorphAry();
  morphologyOperations.loadImage();
  morphologyOperations.loadStruct();
  morphologyOperations.zeroFrameImage();

    morphologyOperations.performOperation();

}
