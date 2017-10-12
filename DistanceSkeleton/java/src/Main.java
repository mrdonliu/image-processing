import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

	int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel , newMinVal , newMaxVal;
	int[][] zeroFramedAry;
	int[] neighborAry;
	int[][] skeletonAry;
	Scanner infile;
	PrintWriter outfile, outfile2, outfile3;

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
		skeletonAry = new int[numRows + 2][numCols + 2];


		neighborAry = new int[9];
		loadImage();
		
		newMinVal = Integer.MAX_VALUE;
		newMaxVal = Integer.MIN_VALUE;
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
	
	void firstPassDistance() {
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for(int x = 1; x < numCols + 1 ; x++ ) {
				if(zeroFramedAry[i][x] > 0 ) {
					loadNeighbors(i,x);
					int min = Integer.MAX_VALUE;
					for(int j = 0 ; j < 4 ; j++ ) {
						min = Math.min(min, neighborAry[j]);
					}
					
					zeroFramedAry[i][x] = min + 1;
				} 
			}
		}
	}
	
	void secondPassDistance() {
		for(int i = numRows ; i > 0 ; i-- ) {
			for(int x = numCols; x > 0 ; x-- ) {
				if(zeroFramedAry[i][x] > 0 ) {
					loadNeighbors(i,x);
					int min = Integer.MAX_VALUE;
					for(int j = 5 ; j < 9 ; j++ ) {
						min = Math.min(min, neighborAry[j]);
					}
					
					min = Math.min(min + 1, zeroFramedAry[i][x]);
					zeroFramedAry[i][x] = min;
				}
			}
		}
		
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for( int x = 1 ; x < numCols + 1 ; x++ )
				if(zeroFramedAry[i][x] < newMinVal ) {
					newMinVal = zeroFramedAry[i][x];
				} 
				else if(zeroFramedAry[i][x] > newMaxVal) {
					newMaxVal = zeroFramedAry[i][x];
				}
					
				
		}
		
		outfile.printf("%d %d %d %d", numRows, numCols, newMinVal, newMaxVal);
		outfile.println();
		outfile.println();
		
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for( int x = 1 ; x < numCols + 1 ; x++ ) {
				if(zeroFramedAry[i][x] < 10 ) {
					outfile.print(" ");
				}
					outfile.print(zeroFramedAry[i][x]);
					outfile.print(" ");
		}
			outfile.println();
		}
	}

	
	void prettyPrintDistance(String msg , int pass) {
		PrintWriter printer;
		switch(pass) {
		case 1:
			printer = outfile3;
			break;
		case 2:
			printer = outfile3;
			break;
		case 3:
			printer = outfile3;
			break;
		default:
			printer = outfile;
			break;
		}
		printer.print(msg);
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for(int x = 1; x < numCols + 1 ; x++ ) {
				if(zeroFramedAry[i][x] == 0 ) {
					printer.print("  ");
				} else {
					if( zeroFramedAry[i][x] < 10 ) {
						printer.print(" " + zeroFramedAry[i][x]);
					} else {
						printer.print(zeroFramedAry[i][x]);
					}
				}
			}
			
			printer.println();
		}
		
		printer.println();
		printer.println();

		printer.println();
	}
	
	void closeBuffers() {
		infile.close();
		outfile.close();
		outfile2.close();
		outfile3.close();
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

	}
	
	void computeSkeleton() {
		outfile2.printf("%d %d %d %d", numRows, numCols, newMinVal, newMaxVal);
		outfile2.println();
		outfile2.println();
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for( int x = 1 ; x < numCols + 1 ; x++ ) {
				loadNeighbors(i,x);
				int max = Integer.MIN_VALUE;
				for(int j = 1 ; j < 9 ; j+=2) {
					if(neighborAry[j] > max ) {
						max = neighborAry[j];
					}
				}
				if(zeroFramedAry[i][x] >= max ) {
					if(zeroFramedAry[i][x] < 10) {
						outfile2.print(" ");
					}
					outfile2.print(zeroFramedAry[i][x]);
					skeletonAry[i][x] = zeroFramedAry[i][x];
					outfile2.print(" ");
		} else {
			outfile2.print(" ");
			outfile2.print(0);
			skeletonAry[i][x] = 0;
			outfile2.print(" ");
		}
		}
			outfile2.println();
		}
	}
	
	void prettyPrintSkeleton() {
		outfile3.println("Distance pass 3");
		for(int i = 1 ; i < numRows + 1 ; i++ ) {
			for(int x = 1; x < numCols + 1 ; x++ ) {
				if(skeletonAry[i][x] == 0 ) {
					outfile3.print("  ");
				} else {
					if( zeroFramedAry[i][x] < 10 ) {
						outfile3.print(" " + zeroFramedAry[i][x]);
					} else {
						outfile3.print(zeroFramedAry[i][x]);
					}
				}
			}
			
			outfile3.println();
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Main cc;
		try {
			cc = new Main(args[0],args[1],args[2],args[3]);
			cc.firstPassDistance();
			cc.prettyPrintDistance("Distance pass 1 \n " , 1);
			cc.secondPassDistance();
			cc.prettyPrintDistance("Distance pass 2 \n " , 2);
			cc.computeSkeleton();
			cc.prettyPrintSkeleton();
			cc.closeBuffers();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

	}

}
