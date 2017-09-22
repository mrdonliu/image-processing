import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {

	private int numRows, numCols, minVal, maxVal, newMin, newMax;
	private int[][] mirrorFramedAry;
	private int[][] tempAry;
	private int[] neighborAry;
	private PrintWriter pw;
	private Scanner sc;

	public Main(String infilename, String outfilename) throws IOException {
		sc = new Scanner(new BufferedReader(new FileReader(infilename)));
		pw = new PrintWriter(new BufferedWriter(new FileWriter(outfilename)));
		int data;
		for (int i = 0; i < 4; i++) {
			data = sc.nextInt();
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

		mirrorFramedAry = new int[numRows + 2][numCols + 2];
		tempAry = new int[numRows + 2][numCols + 2];
		neighborAry = new int[9];
		newMin = minVal;
		newMax = maxVal;
	}

	public void mirrorFramed() {
		for (int i = 1; i < numCols + 1; i++) {
			mirrorFramedAry[0][i] = mirrorFramedAry[1][i];
			mirrorFramedAry[numRows + 1][i] = mirrorFramedAry[numRows][i];

		}

		for (int i = 0; i < numRows + 2; i++) {
			mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
			mirrorFramedAry[i][numCols + 1] = mirrorFramedAry[i][numCols];

		}

	}

	public void loadImage() {
		int data;
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {
				data = sc.nextInt();
				tempAry[i][x] = data;
				mirrorFramedAry[i][x] = data;

			}
		}
	}

	public void loadNeighbors(int i, int j) {
		int leftMostI = i - 1;
		int leftMostJ = j - 1;

		int counter = 0;
		for (int x = leftMostI; x < leftMostI + 3; x++) {
			for (int y = leftMostJ; y < leftMostJ + 3; y++) {
				neighborAry[counter] = mirrorFramedAry[x][y];
				counter++;

			}
		}
	}

	void print() {
		for (int i = 0; i < numRows + 2; i++) {
			for (int x = 0; x < numCols + 2; x++) {
				System.out.print(mirrorFramedAry[i][x] + " ");

			}

			System.out.println();
		}
	}

	public void median3x3() {
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {
				loadNeighbors(i, x);
				Arrays.sort(neighborAry);
				tempAry[i][x] = neighborAry[4];
				if (tempAry[i][x] > newMax) {
					newMax = tempAry[i][x];
				}
				if (tempAry[i][x] < newMin) {
					newMin = tempAry[i][x];
				}
			}

		}

		pw.printf("%d %d %d %d", numRows, numCols, newMin, newMax);
		pw.println();
		for (int i = 1; i < numRows + 1; i++) {
			for (int x = 1; x < numCols + 1; x++) {

				pw.print(tempAry[i][x]);
				pw.print(" ");

			}

			pw.println();
		}

		sc.close();
		pw.close();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Main mf = new Main(args[0], args[1]);
			mf.loadImage();
			mf.mirrorFramed();

			mf.median3x3();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
