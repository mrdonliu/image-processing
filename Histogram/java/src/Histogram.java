import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Histogram {
	private int numRows, numCols, minVal, maxVal;
	private int[] histogram;
	private Scanner scanner;
	private PrintWriter pw;

	public Histogram(String infilename, String outfilename) throws IOException {
		scanner = new Scanner(new BufferedReader(new FileReader(infilename)));
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

		histogram = new int[maxVal + 1];
		for (int i = 0; i < maxVal + 1; i++) {
			histogram[i] = 0;
		}

		for (int i = 0; scanner.hasNextInt(); i++) {
			data = scanner.nextInt();
			histogram[data]++;
		}

	}

	public void computeHistogram() {
		int occurence = 0;
		for (int i = 0; i < maxVal + 1; i++) {
			System.out.println(i);
			occurence = histogram[i] > 80 ? 80 : histogram[i];
			if (i < 10) {
				pw.print("( ");

			} else {
				pw.print("(");
			}

			pw.print(i + "):" + occurence);
			if (occurence < 10) {
				pw.print("  ");
			} else {
				pw.print(' ');
			}

			for (int x = 0; x < occurence; x++) {
				pw.print('+');
			}

			pw.println();
		}

		pw.close();
		scanner.close();
	}

	public static void main(String[] args) {
		try {
			Histogram histogram = new Histogram(args[0], args[1]);
			histogram.computeHistogram();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
