#include <fstream>
using namespace std;
class Histogram {
 private:
  int numRows, numCols, minVal, maxVal;
  int* histogram;
  ifstream infile;
  ofstream outfile;

 public:
  Histogram(char* infilename, char* outfilename);
  ~Histogram();
  void computeHistogram();
};

Histogram::Histogram(char* infilename, char* outfilename) {
  infile.open(infilename);
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
  histogram = new int[maxVal + 1];

  for (int i = 0; i < maxVal + 1; i++) {
    histogram[i] = 0;
  }

  for (int i = 0; !infile.eof(); i++) {
    infile >> data;
    histogram[data]++;
  }
}

void Histogram::computeHistogram() {
  int occurence = 0;
  for (int i = 0; i < maxVal + 1; i++) {
    if (i < 10) {
      outfile << "( " << i << ")";
    } else {
      outfile << "(" << i << ")";
    }

    occurence = histogram[i] > 80 ? 80 : histogram[i];
    outfile << ':' << occurence;
    if (occurence < 10) {
      outfile << "  ";
    } else {
      outfile << ' ';
    }
    for (int i = 0; i < occurence; i++) {
      outfile << "+";
    }
    outfile << endl;
  }

  outfile.flush();
}

Histogram::~Histogram() {
  infile.close();
  outfile.close();
  delete[] histogram;
}

int main(int argc, char* argv[]) {
  Histogram histogram(argv[1], argv[2]);
  histogram.computeHistogram();
}
