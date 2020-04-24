// Krzysztof Wydrzynski - 4
import java.util.LinkedList;
import java.util.Scanner;

public class Source {
    public static Scanner in = new Scanner(System.in);

    public static void main (String[] args) {
        int width = in.nextInt();
        int height = in.nextInt();
        boolean[][] map = new boolean[width][height];
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                map[j][i] = in.nextInt() == 1;
            }
        }

        int howManyDataSets = in.nextInt();
        LinkedList<Character> path = new LinkedList<>();

        for (int i = 0; i < howManyDataSets; i++) {
            char whichAlgorithm = in.next().charAt(0);
            int startPointX = in.nextInt();
            int startPointY = in.nextInt();
            int endPointX = in.nextInt();
            int endPointY = in.nextInt();
            boolean fail = false;
            if (whichAlgorithm == 'r') { // rekurencyjnie
                RecursivePathfinder recursivePathfinder = new RecursivePathfinder(map, width, height);
                path = recursivePathfinder.findPath(startPointX, startPointY, endPointX, endPointY);
                System.out.print("r ");
                int size = path.size();
                for (int j = 0; j < size; j++) {
                    System.out.print(path.removeLast() + " ");
                }
            } else { // iteracyjnie
                IterativePathFinder iterativePathFinder = new IterativePathFinder(map, width, height);
                path = iterativePathFinder.findPath(startPointX, startPointY, endPointX, endPointY);
                System.out.print("i ");
                int size = path.size();
                for (int j = 0; j < size; j++) {
                    System.out.print(path.removeFirst() + " ");
                }
            }
            System.out.println();
        }


    }

}

class Labirynth {
    boolean[][] board_;
    int height_, width_;
    public Labirynth(boolean[][] board, int height, int width) {
        this.board_ = board;
        this.height_ = height;
        this.width_ = width;
    }
    public int getHeight() {
        return height_;
    }
    public int getWidth() {
        return width_;
    }
    public void print() {
        for(int w = 0; w < width_+2; w++ )
            System.out.print('_');
        System.out.println();
        for(int h = 0; h < height_; h++ ) {
            System.out.print('|');
            for(int w = 0; w < width_; w++ ) {
                System.out.print(board_[w][height_-h-1] ? (char) 35 : " ");
            }
            System.out.println("| " + (height_-h-1));
        }
        for(int w = 0; w < width_+2; w++ )
            System.out.print((char) 175);
        System.out.print("\n ");
        for(int w = 0; w < width_; w++ ) {
            System.out.print(w%10);
        }
        System.out.println();
    }
    public void printPosition(int x, int y) {
        for(int w = 0; w < width_+2; w++ )
            System.out.print('_');
        System.out.println();
        for(int h = 0; h < height_; h++ ) {
            System.out.print('|');
            for(int w = 0; w < width_; w++ ) {
                if (w==x && height_-h-1==y)
                    System.out.print(board_[w][height_-h-1] ? (char) 35 : "x");
                else
                    System.out.print(board_[w][height_-h-1] ? (char) 35 : " ");
            }
            System.out.println("| ");
        }
        for(int w = 0; w < width_+2; w++ )
            System.out.print((char) 175);
        System.out.println();
    }
}


class RecursivePathfinder {
    boolean[][] map_;
    boolean[][] visited;
    int width_;
    int height_;
    int xGoal, yGoal;
    LinkedList<Character> charList = new LinkedList<>();

    RecursivePathfinder(boolean[][] map, int width, int height) {
        this.map_ = map;
        this.width_ = width;
        this.height_ = height;
        this.visited = new boolean[width][height];
    }

    public LinkedList<Character> findPath(int startPointX, int startPointY, int endPointX, int endPointY) {
        LinkedList<Character> path = new LinkedList<>();
        if (startPointX == endPointX && startPointY == endPointY) return path;
        this.xGoal = endPointX;
        this.yGoal = endPointY;
        if (!makeMove(startPointX, startPointY)) {
            path.add('X');
            return path;
        } else {
            return charList;
        }
    }

    private boolean makeMove(int x, int y) {
        if (x == xGoal && y == yGoal) return true; // jestem na koncu
        if (x < 0 || x >= this.width_ || y < 0 || y >= this.height_) return false; // po za plansza
        if (map_[x][y] || visited[x][y]) return false; // sciana, lub bylem tam
        this.visited[x][y] = true;
        if (makeMove(x, y + 1)) {
            charList.add('N');
            return true;
        }
        if (makeMove(x, y - 1)) {
            charList.add('S');
            return true;
        }
        if (makeMove(x - 1, y)) {
            charList.add('W');
            return true;
        }
        if (makeMove(x + 1, y)) {
            charList.add('E');
            return true;
        }
//        makeMove(x, y);
//        this.visited[x][y] = false;
//        this.map_[x][y] = true;
        if (charList.isEmpty()) {
            return false;
        }
//        this.map_[x][y] = true;

        if (charList.peekLast() == 'N') y--;
        else if (charList.peekLast() == 'S') y++;
        else if (charList.peekLast() == 'W') x++;
        else if (charList.peekLast() == 'E') x--;
//        System.out.print("fsaafs");
        charList.removeLast();
        this.visited[x][y] = false;
        return makeMove(x, y);
//        return false;
    }
}

class IterativePathFinder {
    boolean[][] map_;
    boolean[][] visited;
    int width_;
    int height_;
    int xGoal, yGoal;
    LinkedList<Character> charList = new LinkedList<>();

    IterativePathFinder(boolean[][] map, int width, int height) {
        this.map_ = map;
        this.width_ = width;
        this.height_ = height;
        this.visited = new boolean[width][height];
    }

    public LinkedList<Character> findPath(int startPointX, int startPointY, int endPointX, int endPointY) {
        LinkedList<Character> path = new LinkedList<>();
        if (startPointX == endPointX && startPointY == endPointY) return path;
        this.xGoal = endPointX;
        this.yGoal = endPointY;
        if (!getPath(startPointX, startPointY)) {
            path.add('X');
            return path;
        } else {
            return charList;
        }
    }

    private boolean getPath(int x, int y) {
        while (true) {
            if (x == xGoal && y == yGoal) return true; // jestem na koncu
            this.visited[x][y] = true;
            if (y + 1 < this.height_ && !map_[x][y + 1] && !visited[x][y + 1]) { // polnoc
                charList.add('N');
                y++;
            } else if (y - 1 >= 0 && !map_[x][y - 1] && !visited[x][y - 1]) { // polodnie
                charList.add('S');
                y--;
            } else if (x - 1 >= 0 && !map_[x - 1][y] && !visited[x - 1][y]) { // zachod
                charList.add('W');
                x--;
            } else if (x + 1 < this.width_ && !map_[x + 1][y] && !visited[x + 1][y]) { // wschod
                charList.add('E');
                x++;
            } else {
                if (charList.isEmpty()) return false;
//                this.visited[x][y] = false;
//                this.map_[x][y] = true;
                if (charList.peekLast() == 'N') y--;
                else if (charList.peekLast() == 'S') y++;
                else if (charList.peekLast() == 'W') x++;
                else if (charList.peekLast() == 'E') x--;
                charList.removeLast();
            }
        }
    }
}