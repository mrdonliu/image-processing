import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Threshold {
	private int numRows, numCols, minVal, maxVal;
	private Scanner scanner, inputScanner;
	private PrintWriter pw;
	private String outfilename;
	private int thresholdVal;

	public Threshold(String infilename) throws IOException {
		scanner = new Scanner(new BufferedReader(new FileReader(infilename)));
		System.out.println("Please enter the value for threshold: ");
		inputScanner = new Scanner(System.in);
		thresholdVal = inputScanner.nextInt();
		outfilename = "thr" + thresholdVal + ".txt";
		pw = new PrintWriter(new BufferedWriter(new FileWriter(outfilename)));
		int data;
		for (int i = 0; i < 4; i++) {
			data = scanner.nextInt();
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

		inputScanner.close();

	}

	public void computeThreshold() {
		pw.printf("%d %d %d %d", numRows, numCols, minVal, maxVal);
		pw.println();
		int data;
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numCols; x++) {
				data = scanner.nextInt();
				data = data > thresholdVal ? 1 : 0;
				pw.print(data);
				pw.print(" ");
			}
			pw.println();
		}

		pw.close();
		scanner.close();
	}

	public static void main(String[] args) {
		try {
			Threshold threshold = new Threshold(args[0]);
			threshold.computeThreshold();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
