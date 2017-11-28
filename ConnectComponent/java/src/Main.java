import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

	private class Property {
		int label, numbPixels, minRow, minCol, maxRow, maxCol;

		void setLabel(int l) {
			label = l;
		}

		void incrementPixels() {
			numbPixels++;
		}

		void checkBounds(int i, int j) {
			if (i < minRow) {
				minRow = i;
			}
			if (i > maxRow) {
				maxRow = i;
			}

			if (j < minCol) {
				minCol = j;
			}
			if (j > maxCol) {
				maxCol = j;
			}

		}

		Property() {
			numbPixels = 0;
			maxRow = -1;
			maxCol = -1;
			minRow = 2147483647;
			minCol = 2147483647;
		}

		int getMaxRows() {
			return maxRow;
		}

		int getMinCols() {
			return minCol;
		}

		int getMaxCols() {
			return maxCol;
		}

		int getMinRows() {
			return minRow;
		}

		int getNumbPixels() {
			return numbPixels;
		}
	}

	int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel;
	int[][] zeroFramedAry;
	int[] neighborAry;
	int[] eqAry;
	Scanner infile;
	PrintWriter outfile, outfile2, outfile3;
	Property[] components;

	Main(String infilename, String outfilename, String outfilename2, String outfilename3) throws IOException {
		infile = new Scanner(new BufferedReader(new FileReader(infilename)));
		outfile = new PrintWriter(new BufferedWriter(new FileWriter(outfilename)));
		outfile2 = new PrintWriter(new BufferedWriter(new FileWriter(outfilename2)));
		outfile3 = new PrintWriter(new BufferedWriter(new FileWriter(outfilename3)));

		int data = 0;
		for (int i = 0; i < 4; i++) {
			data = infile.nextInt();
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
		zeroFramedAry = new int[numRows + 2][numCols + 2];

		eqAry = new int[(numRows * numCols) / 4];
		for (int i = 0; i < (numRows * numCols) / 4; i++) {
			eqAry[i] = i;
		}

		neighborAry = new int[9];
	}

	void zeroFrame() {
		for (int i = 0; i < numCols + 2; i++) {
			zeroFramedAry[0][i] = 0;
			zeroFramedAry[numRows + 1][i] = 0;

		}

		for (int i = 0; i < numRows + 2; i++) {
			zeroFramedAry[i][0] = 0;
			zeroFramedAry[i][numCols + 1] = 0;

		}
	}

	void loadImage() {
		int data = 0;

		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {
				data = infile.nextInt();
				zeroFramedAry[i][x] = data;
			}
		}
	}

	void loadNeighbors(int i, int j) {
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

	void connectCC_pass1() {
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {
				if (zeroFramedAry[i][x] > 0) {

					loadNeighbors(i, x);
					int topNeighbor = neighborAry[1];
					int leftNeighbor = neighborAry[3];
					if (topNeighbor == leftNeighbor) {
						if (topNeighbor == 0) {
							zeroFramedAry[i][x] = ++newLabel;
						} else {
							zeroFramedAry[i][x] = topNeighbor;
						}
					} else {
						if (topNeighbor == 0) {
							zeroFramedAry[i][x] = leftNeighbor;
						} else if (leftNeighbor == 0) {
							zeroFramedAry[i][x] = topNeighbor;

						} else {
							zeroFramedAry[i][x] = Math.min(topNeighbor, leftNeighbor);
							eqAry[topNeighbor] = zeroFramedAry[i][x];
							eqAry[leftNeighbor] = zeroFramedAry[i][x];

						}

					}
				}
			}
		}
	}

	void connectCC_pass2() {
		int temp;
		for (int i = numRows; i > 0; i--) {
			for (int x = numCols; x > 0; x--) {
				if (zeroFramedAry[i][x] > 0) {
					loadNeighbors(i, x);
					int rightNeighbor = neighborAry[5];
					int bottomNeighbor = neighborAry[7];
					if (rightNeighbor == bottomNeighbor && rightNeighbor == 0) {
						continue;
					} else if (rightNeighbor == 0 || bottomNeighbor == 0) {
						if (zeroFramedAry[i][x] == rightNeighbor || zeroFramedAry[i][x] == bottomNeighbor) {
							continue;
						}
					}

					if (rightNeighbor != bottomNeighbor) {
						if (rightNeighbor == 0) {
							temp = Math.min(bottomNeighbor, zeroFramedAry[i][x]);
							eqAry[bottomNeighbor] = temp;
							eqAry[zeroFramedAry[i][x]] = temp;
							zeroFramedAry[i][x] = temp;
						} else if (bottomNeighbor == 0) {
							temp = Math.min(rightNeighbor, zeroFramedAry[i][x]);
							eqAry[rightNeighbor] = temp;
							eqAry[zeroFramedAry[i][x]] = temp;
							zeroFramedAry[i][x] = temp;
						} else {
							temp = Math.min(rightNeighbor, bottomNeighbor);
							temp = Math.min(temp, zeroFramedAry[i][x]);
							eqAry[rightNeighbor] = temp;
							eqAry[zeroFramedAry[i][x]] = temp;
							eqAry[bottomNeighbor] = temp;
							zeroFramedAry[i][x] = temp;

						}
					} else {
						if (rightNeighbor != 0) {
							temp = Math.min(rightNeighbor, bottomNeighbor);
							temp = Math.min(temp, zeroFramedAry[i][x]);
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

	void connectCC_pass3() {
		components = new Property[newLabel + 1];
		for (int i = 1; i <= newLabel; i++) {
			components[i] = new Property();
			components[i].setLabel(i);
		}
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {
				if (zeroFramedAry[i][x] > 0) {
					zeroFramedAry[i][x] = eqAry[zeroFramedAry[i][x]];
					components[zeroFramedAry[i][x]].incrementPixels();
					components[zeroFramedAry[i][x]].checkBounds(i, x);

				}
			}
		}
	}

	void manageEqAry() {
		int trueLabel = 0;
		int index = 1;
		while (index <= newLabel) {
			if (eqAry[index] == index) {
				trueLabel++;
				eqAry[index] = trueLabel;
			} else {
				eqAry[index] = eqAry[eqAry[index]];
			}

			index++;
		}

		newLabel = trueLabel;
	}

	void printCcProperty() {
		outfile3.printf("%d %d %d %d", numRows, numCols, minVal, newLabel);
		outfile3.println();
		for (int i = 1; i <= newLabel; i++) {
			outfile3.println(i);
			outfile3.println(components[i].getNumbPixels());
			outfile3.printf("%d %d", components[i].getMinRows(), components[i].getMinCols());
			outfile3.println();
			outfile3.printf("%d %d", components[i].getMaxRows(), components[i].getMaxCols());
			outfile3.println();
			outfile3.println();
		}

	}

	void prettyPrint(int pass) {
		switch (pass) {
		case 1:
			outfile.println("Pass 1:");
			break;
		case 2:
			outfile.println("Pass 2:");
			break;
		case 3:
			outfile.println("Pass 3:");
			break;
		}

		for (int i = 0; i < numRows + 2; i++) {
			for (int x = 0; x < numCols + 2; x++) {

				if (zeroFramedAry[i][x] != 0) {
					outfile.print(zeroFramedAry[i][x]);

				} else {
					outfile.print(" ");
				}

				if (zeroFramedAry[i][x] < 10) {
					outfile.print(" ");
				} else {
					outfile.print(" ");
				}
			}
			outfile.println();
		}

		print("");

		outfile.println();
		outfile.println();
		outfile.println();

	}

	void print(String message) {
		outfile.println(message);
		outfile.println("eqAry: (Index:Value) ");

		for (int i = 0; i < (numRows * numCols) / 4; i++) {
			outfile.printf("%d : %d ", i, eqAry[i]);
			if (i % 10 == 0) {
				outfile.println();
			}
		}
	}

	void print2() {
		outfile2.printf("%d %d 0 %d ", numRows, numCols, newLabel);
		outfile2.println();
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols; x++) {
				outfile2.printf("%d ", zeroFramedAry[i][x]);
			}
			outfile2.println();
		}

		infile.close();
		outfile.close();
		outfile2.close();
		outfile3.close();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Main cc;
		try {
			cc = new Main(args[0], args[1], args[2], args[3]);
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
			System.exit(0);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
