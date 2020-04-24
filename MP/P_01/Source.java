// Wydrzynski Krzysztof - 4
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);

    public static int[] kadane (int[] dataSet, int dataSetSize) {
        int sum = -1;
        int bestSum = -1;
        int columnStart = 0;
        int bestColumnStart = 0;
        int columnEnd;
        int bestColumnEnd = 0;
        int size = 0;
        int bestSize = 0;

        for (int i = 0; i < dataSetSize; i++) {
            columnEnd = i;
            if (sum <= 0) {
                sum = dataSet[i];
                columnStart = columnEnd;
                size = 1;
            } else {
                sum += dataSet[i];
                size++;
            }

            if ((bestSum < sum) || (bestSum == sum && size < bestSize)) {
                bestSize = size;
                bestSum = sum;
                bestColumnStart = columnStart;
                bestColumnEnd = columnEnd;
            }
        }

        return new int[]{bestSum, bestColumnStart, bestColumnEnd};
    }

    public static void main(String[] args) {
        int numberOfDataSets = in.nextInt();
        for (int i = 0; i < numberOfDataSets; i++) {
            int rows = in.nextInt();
            int columns = in.nextInt();
            int[][] dataSet = new int[rows][columns];

            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < columns; k++) {
                    dataSet[j][k] = in.nextInt();
                }
            }

            int sum = 0;
            int bestSum = -1;
            int rowStart = 0;
            int bestRowStart = 0;
            int rowEnd = 0;
            int bestRowEnd = 0;
            int rowSize = 0;
            int bestRowSize = 0;
            int columnStart = 0;
            int bestColumnStart = -1;
            int columnEnd = 0;
            int bestColumnEnd = 0;
            int columnSize = 0;
            int bestColumnSize = 0;


            int[] dataSetTemp = new int[columns];

            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < columns; k++) dataSetTemp[k] = 0;
                for (int k = j; k < rows; k++) {
                    for (int m = 0; m < columns; m++) {
                        dataSetTemp[m] += dataSet[k][m];
                    }

                    int[] dataSetTempKadane = new int[3];

                    rowEnd = k;

                    dataSetTempKadane = kadane(dataSetTemp, columns);

                    sum = dataSetTempKadane[0];
                    columnStart = dataSetTempKadane[1];
                    columnEnd = dataSetTempKadane[2];
                    columnSize = columnEnd - columnStart;

                    if (k == j) {
                        rowStart = rowEnd;
                    }

//                    for (int m = 0; m < columns; m++) {
//                        System.out.print(dataSetTemp[m] + " ");
//                    }


                    rowSize = rowEnd - rowStart;

//                    System.out.print("  k: " + k + " j: " + j + " sum: " + sum + " bestSum: " + bestSum + " columnSize: " + columnSize + " bestColumnSize: " + bestColumnSize + " rowSize: " + rowSize + " bestRowSize: " + bestRowSize + " j: " + j + " k: " + k);


                    if ((bestSum < sum) || (bestSum == sum && rowSize < bestRowSize)) {
                        if (columnSize < bestColumnSize || rowSize < bestRowSize || bestSum < sum) {
                            bestSum = sum;

//                            System.out.print(" true ");

//                        System.out.println("k: " + k + " j: " + j);

                            bestRowSize = rowSize;

                            bestRowEnd = rowEnd;
                            bestRowStart = rowStart;

                            bestColumnStart = columnStart;
                            bestColumnEnd = columnEnd;
                            bestColumnSize = columnSize;

                        }
                    }
//                    System.out.println("");
                }
            }
            if (bestSum < 0) {
                System.out.println("empty");
            } else {
                System.out.println("max_sum = " + bestSum + ", a[" + bestRowStart + ".." + bestRowEnd + "][" + bestColumnStart + ".." + bestColumnEnd + "]");
            }
        }

    }

}

