import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Scanner;

public class ChainCode{
    private int numRows, numCols, minVal, maxVal;
    int lastQ = 4;
    int nextDir;
	int nextQ;
    Scanner sc;
    PrintWriter pw;
    int[] nextDirTable;
    int[][] imgAry;
    Point startP , currentP, nextP;
    
    private class Point {
    	private int row, col, label;
    	public int getRow() {
			return row;
		}
		public int getCol() {
			return col;
		}
		public int getLabel() {
			return label;
		}
		public void setLabel(int label) {
			this.label = label;
		}
		private Point[] neighborAry;
		public Point[] getNeighborAry() {
			return neighborAry;
		}
    	public Point(int row , int col, int label) {
    		this.label = label;
    		this.row = row;
    		this.col = col;
    	}
    	public void loadNeighbors() {
    		neighborAry[0] = new Point(row , col+1, imgAry[row][col+1]);
    		neighborAry[1] = new Point(row-1 , col+1, imgAry[row-1][col+1]);
    		neighborAry[2] = new Point(row-1 , col, imgAry[row-1][col]);
    		neighborAry[3] = new Point(row-1 , col-1, imgAry[row-1][col-1]);
    		neighborAry[4] = new Point(row , col-1, imgAry[row][col-1]);
    		neighborAry[5] = new Point(row+1 , col-1, imgAry[row+1][col-1]);
    		neighborAry[6] = new Point(row+1 , col, imgAry[row+1][col]);
    		neighborAry[7] = new Point(row+1 , col+1, imgAry[row+1][col+1]);
    	}
		
		public boolean equals(Point p) {
			if(row == p.row || col == p.col) {
				return true;
			}
			return false;
		}
    }
    public ChainCode(String imageFile , String outputFile) throws FileNotFoundException {
    	sc = new Scanner( new BufferedReader( new FileReader( imageFile )));
    	int temp;
    	for(int i = 0 ; i < 4; i++ ){
        	temp = sc.nextInt();
        	switch(i){
        		case 0:
        			numRows=temp;
        			break;
        		case 1:
        			numCols=temp;
        			break;
        		case 2:
        			minVal=temp;
        			break;
        		case 3:
        			maxVal=temp;
        			break;
    		}
    	}
    	
    	imgAry = new int[numRows+2][numCols+2];
    	for( int i = 1 ; i < numRows + 1 ; i++ ) {
    		for( int x = 1 ; x < numCols + 1 ; x++ ) {
    			imgAry[i][x] = sc.nextInt();
    		}
    	}
    	
    	zeroFramed();
    	nextDirTable = new int[8];
    	nextDirTable[0] = 6;
    	nextDirTable[1] = 0;
    	nextDirTable[2] = 0;
    	nextDirTable[3] = 2;
    	nextDirTable[4] = 2;
    	nextDirTable[5] = 4;
    	nextDirTable[6] = 4;
    	nextDirTable[7] = 2;
    }
    
    void zeroFramed(){
        for(int i = 0; i < numCols + 2 ; i++){
            imgAry[0][i] = 0;
            imgAry[numRows+1][i] = 0;
        }
        
        for(int i = 0; i < numRows + 2 ; i++){
            imgAry[i][0] = 0;
            imgAry[i][numCols+1] = 0;
        }
    }
    
    public void performChainCode() {
    	int firstRow = 0;
    	int firstCol = 0;
    	for( int i = 1 ; i < numRows + 1 ; i++ ) {
    		for( int x = 1 ; x < numCols + 1 ; x++ ) {
    			if(imgAry[i][x] > 0) {
    				firstRow = i;
    				firstCol = x;
    				startP = new Point(i,x,imgAry[i][x]);
    				currentP = new Point(i,x,imgAry[i][x]);
    				
    				i = numRows + 1;
    				x = numCols + 1;
    			}
    		}
    	}
    	
    	for( int i = firstRow ; i < numRows + 1 ; i++ ) {
    		for( int x = firstCol ; x < numCols + 1 ; x++ ) {
    			if(imgAry[firstRow][firstCol] > 0) {
    				nextQ = (lastQ + 1) % 8;
    				nextDir = findNextP(currentP, nextQ, nextP);
    				currentP.setLabel(currentP.getLabel() * -1);
    			}
    		}
    	}
    	
    	
    	
    	
    }

	public int findNextP(Point currentP, int nextQ, Point nextP) {
		// TODO Auto-generated method stub
		currentP.loadNeighbors();
		Point[] neighborAry = currentP.getNeighborAry();
		for(int i = nextQ ; i < 8 ; i++) {
			if(neighborAry[i].getLabel()== currentP.getLabel()) {
				nextP = neighborAry[i];
				return i;
			}
		}
		
		for(int i = 0 ; i <= nextQ ; i++) {
			if(neighborAry[i].getLabel() == currentP.getLabel()) {
				nextP = neighborAry[i];
				return i;
			}
		}
		
		return -1;
	}
}

