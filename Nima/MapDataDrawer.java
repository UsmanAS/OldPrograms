import java.util.*;
import java.io.*;
import java.awt.*;

public class MapDataDrawer {

    private int[][] grid;
    private int[][] grayMap;
    int numberOfRows;
    int numberOfColumns;

    public MapDataDrawer(String filename) {
        //read the data from the file into the grid

        // open file
        File file = new File(filename);

        Scanner sc;
        try{
            sc = new Scanner(new File(filename));
        }

        catch (Exception e){
            System.out.println("File " + filename + " does not exist.");
            return;
        }

        //get first two ints for number of rows and columns
        numberOfRows = sc.nextInt();
        numberOfColumns = sc.nextInt();

        // set up the grid
        grid = new int[numberOfRows][numberOfColumns];

        // get value, put it in 2d array
        for(int i = 0; i < numberOfRows; i++){
            for(int j = 0; j < numberOfColumns; j++) {
                grid[i][j] = sc.nextInt();
            }
        }
    }

    /**
     * @return the min value in the entire grid
     */
    public int findMinValue(){
        int min = Integer.MAX_VALUE;

        for(int[] i : grid){
            for(int j : i){
                if(j < min)
                    min = j;
            }
        }
        return min;
    }

    /**
     * @return the max value in the entire grid
     */
    public int findMaxValue(){
        int max = Integer.MIN_VALUE;

        for(int[] i : grid){
            for(int j : i){
                if(j > max)
                    max = j;
            }
        }
        return max;
    }

    /**
     * @param col the column of the grid to check
     * @return the index of the row with the lowest value in the given col for the grid
     */
    public int indexOfMinInCol(int col) {

        int row = 0;
        int minElevation = Integer.MAX_VALUE;

        for(int i = 0; i < numberOfRows; i++){
            if(grid[i][col] < minElevation) {
                row = i;
                minElevation = grid[row][col];
            }
        }

        return row;
    }

    /**
     * Draws the grid using the given Graphics object.
     * Colors should be grayscale values 0-255, scaled based on min/max values in grid
     */
    public void drawMap(Graphics g) {
        int max = this.findMaxValue();
        int min = this.findMinValue();
        int colorValue = 0;
        int rowNumber = 0;
        int colNumber;

        for(int[] row : grid) {
            colNumber = 0;
            for (int col : row) {
                colorValue = convertToGrayscaleValue(row[colNumber], min, max);
                g.setColor(new Color(colorValue, colorValue, colorValue));
                g.fillRect(colNumber, rowNumber, 1, 1);
                colNumber++;
            }
            rowNumber++;
        }
    }

    /**
     * Find a path from West-to-East starting at given row.
     * Choose a foward step out of 3 possible forward locations, using greedy method described in assignment.
     *
     * @return the total change in elevation traveled from West-to-East
     */
    public int drawLowestElevPath(Graphics g, int row) {
        int col = 0;
        int currentElevation, northeastElevation, eastElevation, southeastElevation;
        int northeastElevationChange, eastElevationChange, southeastElevationChange;
        int totalChangeInElevation;

        totalChangeInElevation = 0;

        currentElevation = grid[row][col];
        g.fillRect(col, row, 1, 1);

        for(col = 1 ; col < numberOfColumns; col++){
            //look at next three possible moves
            if(row > 0)
                northeastElevation = grid[row-1][col];
            else
                northeastElevation = Integer.MAX_VALUE;

            eastElevation = grid[row][col];

            if(row < (numberOfRows - 1))
                southeastElevation = grid[row+1][col];
            else
                southeastElevation = Integer.MAX_VALUE;

            //determine elevation change
            northeastElevationChange = Math.abs(northeastElevation - currentElevation);
            eastElevationChange = Math.abs(eastElevation - currentElevation);
            southeastElevationChange = Math.abs(southeastElevation - currentElevation);

            if(northeastElevationChange <= southeastElevationChange && northeastElevationChange < eastElevationChange){
                row--;
                totalChangeInElevation = totalChangeInElevation + northeastElevationChange;
            }

            else if(eastElevationChange <= northeastElevationChange && eastElevationChange <= southeastElevationChange){
                totalChangeInElevation = totalChangeInElevation + eastElevationChange;
            }

            else if(southeastElevationChange < northeastElevationChange && southeastElevationChange < eastElevationChange){
                row++;
                totalChangeInElevation = totalChangeInElevation + southeastElevationChange;
            }
            currentElevation = grid[row][col];
            g.fillRect(col, row, 1, 1);

        }

        return totalChangeInElevation;
    }

    /**
     * @return the index of the starting row for the lowest-elevation-change path in the entire grid.
     */
    public int indexOfLowestElevPath(Graphics g) {
        int bestGreedyElevationChange = Integer.MAX_VALUE;
        int tmpGreedyElevationChange = 0;
        int bestRow = 0;

        for(int i = 0; i < numberOfRows; i++){
            tmpGreedyElevationChange = doNotDrawLowestElevPath(i);
            if(tmpGreedyElevationChange < bestGreedyElevationChange){
                bestGreedyElevationChange = tmpGreedyElevationChange;
                bestRow = i;
            }
        }

        return bestRow;
    }

    /**
     * @return the desired value for a grey/gray scale image
     */
    private int convertToGrayscaleValue(int value, int min, int max){
        double grayScaleValue = value - min;
        grayScaleValue = grayScaleValue / (max - min);
        grayScaleValue = grayScaleValue * 255;

        return (int)grayScaleValue;
    }

    private int doNotDrawLowestElevPath(int row) {
        int col = 0;
        int currentElevation, northeastElevation, eastElevation, southeastElevation;
        int northeastElevationChange, eastElevationChange, southeastElevationChange;
        int totalChangeInElevation;

        totalChangeInElevation = 0;

        currentElevation = grid[row][col];

        for(col = 1 ; col < numberOfColumns; col++){
            //look at next three possible moves
            if(row > 0)
                northeastElevation = grid[row-1][col];
            else
                northeastElevation = Integer.MAX_VALUE;

            eastElevation = grid[row][col];

            if(row < (numberOfRows - 1))
                southeastElevation = grid[row+1][col];
            else
                southeastElevation = Integer.MAX_VALUE;

            //determine elevation change
            northeastElevationChange = Math.abs(northeastElevation - currentElevation);
            eastElevationChange = Math.abs(eastElevation - currentElevation);
            southeastElevationChange = Math.abs(southeastElevation - currentElevation);

            if(northeastElevationChange <= southeastElevationChange && northeastElevationChange < eastElevationChange){
                row--;
                totalChangeInElevation = totalChangeInElevation + northeastElevationChange;
            }

            else if(eastElevationChange <= northeastElevationChange && eastElevationChange <= southeastElevationChange){
                totalChangeInElevation = totalChangeInElevation + eastElevationChange;
            }

            else if(southeastElevationChange < northeastElevationChange && southeastElevationChange < eastElevationChange){
                row++;
                totalChangeInElevation = totalChangeInElevation + southeastElevationChange;
            }
            currentElevation = grid[row][col];

        }

        return totalChangeInElevation;
    }


    /**
     * @return the index of the starting row for the lowest-elevation-change path in the entire grid.
     */
    public int indexOfLowestElevPathBackwards(Graphics g) {
        int bestGreedyElevationChange = Integer.MAX_VALUE;
        int tmpGreedyElevationChange = 0;
        int bestRow = 0;

        for(int i = 0; i < numberOfRows; i++){
            tmpGreedyElevationChange = doNotDrawLowestElevPathBackwards(i);
            if(tmpGreedyElevationChange < bestGreedyElevationChange){
                bestGreedyElevationChange = tmpGreedyElevationChange;
                bestRow = i;
            }
        }

        return bestRow;
    }

    /**
     * Find a path from West-to-East starting at given row.
     * Choose a foward step out of 3 possible forward locations, using greedy method described in assignment.
     *
     * @return the total change in elevation traveled from West-to-East
     */
    public int drawLowestElevPathBackwards(Graphics g, int row) {
        int col = numberOfColumns - 1;
        int currentElevation, northwestElevation, westElevation, southwestElevation;
        int northwestElevationChange, westElevationChange, southwestElevationChange;
        int totalChangeInElevation;

        totalChangeInElevation = 0;

        currentElevation = grid[row][col];
        g.fillRect(col, row, 1, 1);

        for(col = col - 1 ; col > 0; col--){
            //look at next three possible moves
            if(row > 0)
                northwestElevation = grid[row-1][col];
            else
                northwestElevation = Integer.MAX_VALUE;

            westElevation = grid[row][col];

            if(row < (numberOfRows - 1))
                southwestElevation = grid[row+1][col];
            else
                southwestElevation = Integer.MAX_VALUE;

            //determine elevation change
            northwestElevationChange = Math.abs(northwestElevation - currentElevation);
            westElevationChange = Math.abs(westElevation - currentElevation);
            southwestElevationChange = Math.abs(southwestElevation - currentElevation);

            if(northwestElevationChange <= southwestElevationChange && northwestElevationChange < westElevationChange){
                row--;
                totalChangeInElevation = totalChangeInElevation + northwestElevationChange;
            }

            else if(westElevationChange <= northwestElevationChange && westElevationChange <= southwestElevationChange){
                totalChangeInElevation = totalChangeInElevation + westElevationChange;
            }

            else if(southwestElevationChange < northwestElevationChange && southwestElevationChange < westElevationChange){
                row++;
                totalChangeInElevation = totalChangeInElevation + southwestElevationChange;
            }
            currentElevation = grid[row][col];
            g.fillRect(col, row, 1, 1);

        }

        return totalChangeInElevation;
    }

    private int doNotDrawLowestElevPathBackwards(int row) {
        int col = numberOfColumns - 1;
        int currentElevation, northwestElevation, westElevation, southwestElevation;
        int northwestElevationChange, westElevationChange, southwestElevationChange;
        int totalChangeInElevation;

        totalChangeInElevation = 0;

        currentElevation = grid[row][col];

        for(col = col - 1 ; col > 0; col--){
            //look at next three possible moves
            if(row > 0)
                northwestElevation = grid[row-1][col];
            else
                northwestElevation = Integer.MAX_VALUE;

            westElevation = grid[row][col];

            if(row < (numberOfRows - 1))
                southwestElevation = grid[row+1][col];
            else
                southwestElevation = Integer.MAX_VALUE;

            //determine elevation change
            northwestElevationChange = Math.abs(northwestElevation - currentElevation);
            westElevationChange = Math.abs(westElevation - currentElevation);
            southwestElevationChange = Math.abs(southwestElevation - currentElevation);

            if(northwestElevationChange <= southwestElevationChange && northwestElevationChange < westElevationChange){
                row--;
                totalChangeInElevation = totalChangeInElevation + northwestElevationChange;
            }

            else if(westElevationChange <= northwestElevationChange && westElevationChange <= southwestElevationChange){
                totalChangeInElevation = totalChangeInElevation + westElevationChange;
            }

            else if(southwestElevationChange < northwestElevationChange && southwestElevationChange < westElevationChange){
                row++;
                totalChangeInElevation = totalChangeInElevation + southwestElevationChange;
            }
            currentElevation = grid[row][col];

        }

        return totalChangeInElevation;
    }
}