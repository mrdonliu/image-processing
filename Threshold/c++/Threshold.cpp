#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;
class Threshold {
 private:
  int numRows, numCols, minVal, maxVal, thresholdVal;
  string outfilename;
  ifstream infile;
  ofstream outfile;

 public:
  Threshold(char* infilename);
  void computeThreshold();
};

Threshold::Threshold(char* infilename) {
  infile.open(infilename);
  cout << "Please enter a threshold value: ";
  cin >> thresholdVal;
  outfilename = "thr_" + to_string(thresholdVal) + ".txt";
  outfile.open(outfilename);
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
}

void Threshold::computeThreshold() {
  outfile << numRows << ' ' << numCols << ' ' << minVal << ' ' << maxVal;
  outfile << endl;
  int data;
  for (int i = 0; i < numRows; i++) {
    for (int x = 0; x < numCols; x++) {
      infile >> data;
      data = data > thresholdVal ? 1 : 0;
      outfile << data << ' ';
    }

    outfile << endl;
  }

  outfile.close();
  infile.close();
}

int main(int argc, char* argv[]) {
  Threshold threshold(argv[1]);
  threshold.computeThreshold();
}


