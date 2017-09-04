import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class PrettyPrint {
	private int numRows, numCols, minVal, maxVal;
	private Scanner scanner;
	private PrintWriter pw;

	public PrettyPrint(String infilename) throws IOException {
		scanner = new Scanner(new BufferedReader(new FileReader(infilename)));
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

		String outfilename = infilename.substring(0, infilename.lastIndexOf('.')) + "_PP.txt";
		pw = new PrintWriter(new BufferedWriter(new FileWriter(outfilename)));

	}

	public void prettyPrint() {
		int data;
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numCols; x++) {
				data = scanner.nextInt();
				if (data == 0) {
					pw.print(' ');
				} else {
					pw.print(data);
				}

				pw.print(' ');
			}
			pw.println();
		}

		scanner.close();
		pw.close();
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		try {
			PrettyPrint pp = new PrettyPrint(args[0]);
			pp.prettyPrint();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
