/*  Student information for assignment:
 *
 *  On <MY|OUR> honor, <NAME1> and <NAME2),
 *  this programming assignment is <MY|OUR> own work
 *  and <I|WE> have not provided this code to any other student.
 *
 *  Number of slip days used:
 *
 *  Student 1 (Student whose Canvas account is being used)
 *  UTEID:
 *  email address:
 *  Grader name:
 *  Section number:
 *
 *  Student 2
 *  UTEID:
 *  email address:
 *
 */

//imports

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Various recursive methods to be implemented.
 * Given shell file for CS314 assignment.
 */
public class Recursive {

  /**
   * Problem 1: convert a base 10 int to binary recursively.
   *   <br>pre: n != Integer.MIN_VALUE<br>
   *   <br>post: Returns a String that represents N in binary.
   *   All chars in returned String are '1's or '0's.
   *   Most significant digit is at position 0
   *   @param n the base 10 int to convert to base 2
   *   @return a String that is a binary representation of the parameter n
   */

  //  This should also solve for negative values
  public static String getBinary(int n) {
    if (n == Integer.MIN_VALUE) {
      throw new IllegalArgumentException(
        "Failed precondition: " +
        "getBinary. n cannot equal " +
        "Integer.MIN_VALUE. n: " +
        n
      );
    }
    else{
      if (n < 0) {
        return "-" + getBinary(-n);
      }
      else if (n == 0) {
        return "0";
      }
      else if (n == 1) {
        return "1";
      }
      else {
        return getBinary(n / 2) + n % 2;
      }
    }
  }

  /**
   * Problem 2: reverse a String recursively.<br>
   *   pre: stringToRev != null<br>
   *   post: returns a String that is the reverse of stringToRev
   *   @param stringToRev the String to reverse.
   *   @return a String with the characters in stringToRev
   *   in reverse order.
   */
  public static String revString(String stringToRev) {
    if (stringToRev == null) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "revString. parameter may not be null."
      );
    } else if (stringToRev.length() == 0) {
      return "";
    } else {
      return (
        stringToRev.charAt(stringToRev.length() - 1) +
        revString(stringToRev.substring(0, stringToRev.length() - 1))
      );
    }
  }

  /**
   * Problem 3: Returns the number of elements in data
   * that are followed directly by value that is
   * double that element.
   * pre: data != null
   * post: return the number of elements in data
   * that are followed immediately by double the value
   * @param data The array to search.
   * @return The number of elements in data that
   * are followed immediately by a value that is double the element.
   */
  public static int nextIsDouble(int[] data) {
    if (data == null) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "nextIsDouble. parameter may not be null."
      );
    }

    return countNextDoubles(data, 0);
  }

  // CS314 students, add your nextIsDouble helper method here
  private static int countNextDoubles(int[] data, int index) {
    if (index >= data.length - 1) {
      return 0;
    }

    int count = 0;
    if (data[index + 1] == data[index] * 2) {
      count = 1;
    }

    return count + countNextDoubles(data, index + 1);
  }

  /**  Problem 4: Find all combinations of mnemonics
   * for the given number.<br>
   *   pre: number != null, number.length() > 0,
   *   all characters in number are digits<br>
   *   post: see tips section of assignment handout
   *   @param number The number to find mnemonics for
   *   @return An ArrayList<String> with all possible mnemonics
   *   for the given number
   */
  public static ArrayList<String> listMnemonics(String number) {
    if (number == null || number.length() == 0 || !allDigits(number)) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "listMnemonics"
      );
    }
    ArrayList<String> mnemonics = new ArrayList<>();
    recursiveMnemonics(mnemonics, "", number);
    return mnemonics;
  }

  /*
   * Helper method for listMnemonics
   * mnemonics stores completed mnemonics
   * mneominicSoFar is a partial (possibly complete) mnemonic
   * digitsLeft are the digits that have not been used
   * from the original number.
   */
  private static void recursiveMnemonics(
    ArrayList<String> mnemonics,
    String mnemonicSoFar,
    String digitsLeft
  ) {
    if (digitsLeft.length() == 0) {
      mnemonics.add(mnemonicSoFar);
    } else {
      String letters = digitLetters(digitsLeft.charAt(0));
      for (int i = 0; i < letters.length(); i++) {
        recursiveMnemonics(
          mnemonics,
          mnemonicSoFar + letters.charAt(i),
          digitsLeft.substring(1)
        );
      }
    }
  }

  /* Static code blocks are run once when this class is loaded.
   * Here we create an unmoddifiable list to use with the phone
   * mnemonics method.
   */
  private static final List<String> LETTERS_FOR_NUMBER;

  static {
    String[] letters = {
      "0",
      "1",
      "ABC",
      "DEF",
      "GHI",
      "JKL",
      "MNO",
      "PQRS",
      "TUV",
      "WXYZ",
    };
    ArrayList<String> lettersAsList = new ArrayList<>();
    for (String s : letters) {
      lettersAsList.add(s);
    }
    LETTERS_FOR_NUMBER = Collections.unmodifiableList(lettersAsList);
  }

  // used by method digitLetters

  /* helper method for recursiveMnemonics
   * pre: ch is a digit '0' through '9'
   * post: return the characters associated with
   * this digit on a phone keypad
   */
  private static String digitLetters(char ch) {
    if (ch < '0' || ch > '9') {
      throw new IllegalArgumentException(
        "parameter " + "ch must be a digit, 0 to 9. Given value = " + ch
      );
    }
    int index = ch - '0';
    return LETTERS_FOR_NUMBER.get(index);
  }

  /* helper method for listMnemonics
   * pre: s != null
   * post: return true if every character in s is
   * a digit ('0' through '9')
   */
  private static boolean allDigits(String s) {
    if (s == null) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "allDigits. String s cannot be null."
      );
    }
    boolean allDigits = true;
    int i = 0;
    while (i < s.length() && allDigits) {
      allDigits = s.charAt(i) >= '0' && s.charAt(i) <= '9';
      i++;
    }
    return allDigits;
  }

  /**
   * Problem 5: Draw a Sierpinski Carpet.
   * @param size the size in pixels of the window
   * @param limit the smallest size of a square in the carpet.
   */
  public static void drawCarpet(int size, int limit) {
    DrawingPanel p = new DrawingPanel(size, size);
    Graphics g = p.getGraphics();
    g.setColor(Color.BLACK);
    g.fillRect(0, 0, size, size);
    g.setColor(Color.WHITE);
    drawSquares(g, size, limit, 0, 0);
  }

  /* Helper method for drawCarpet
   * Draw the individual squares of the carpet.
   * @param g The Graphics object to use to fill rectangles
   * @param size the size of the current square
   * @param limit the smallest allowable size of squares
   * @param x the x coordinate of the upper left corner of the current square
   * @param y the y coordinate of the upper left corner of the current square
   */
  private static void drawSquares(
    Graphics g,
    int size,
    int limit,
    double x,
    double y
  ) {
    if (size > limit) {
      int newSize = size / 3;
      drawSquares(g, newSize, limit, x, y);
      drawSquares(g, newSize, limit, x + newSize, y);
      drawSquares(g, newSize, limit, x + 2 * newSize, y);
      drawSquares(g, newSize, limit, x, y + newSize);
      drawSquares(g, newSize, limit, x + 2 * newSize, y + newSize);
      drawSquares(g, newSize, limit, x, y + 2 * newSize);
      drawSquares(g, newSize, limit, x + newSize, y + 2 * newSize);
      drawSquares(g, newSize, limit, x + 2 * newSize, y + 2 * newSize);
    } else {
      g.fillRect((int) x, (int) y, size, size);
    }
  }

  /**
   * Problem 6: Determine if water at a given point
   * on a map can flow off the map.
   * <br>pre: map != null, map.length > 0,
   * map is a rectangular matrix, 0 <= row < map.length,
   * 0 <= col < map[0].length
   * <br>post: return true if a drop of water starting at the location
   * specified by row, column can reach the edge of the map,
   * false otherwise.
   * @param map The elevations of a section of a map.
   * @param row The starting row of a drop of water.
   * @param col The starting column of a drop of water.
   * @return return true if a drop of water starting at the location
   * specified by row, column can reach the edge of the map, false otherwise.
   */
  public static boolean canFlowOffMap(int[][] map, int row, int col) {
    if (
      map == null ||
      map.length == 0 ||
      !isRectangular(map) ||
      !inbounds(row, col, map)
    ) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "canFlowOffMap"
      );
    } else {
      return canFlowOfMap(map, row, col, map[row][col]);
    }
  }

  private static boolean canFlowOfMap(
    int[][] map,
    int row,
    int col,
    int height
  ) {
    if (
      row == 0 || row == map.length - 1 || col == 0 || col == map[0].length - 1
    ) {
      return true;
    } else {
      int min = Integer.MAX_VALUE;
      int minRow = 0;
      int minCol = 0;
      if (inbounds(row - 1, col, map) && map[row - 1][col] < min) {
        min = map[row - 1][col];
        minRow = row - 1;
        minCol = col;
      }
      if (inbounds(row + 1, col, map) && map[row + 1][col] < min) {
        min = map[row + 1][col];
        minRow = row + 1;
        minCol = col;
      }
      if (inbounds(row, col - 1, map) && map[row][col - 1] < min) {
        min = map[row][col - 1];
        minRow = row;
        minCol = col - 1;
      }
      if (inbounds(row, col + 1, map) && map[row][col + 1] < min) {
        min = map[row][col + 1];
        minRow = row;
        minCol = col + 1;
      }
      if (min < height) {
        return canFlowOfMap(map, minRow, minCol, min);
      } else {
        return false;
      }
    }
  }

  /* helper method for canFlowOfMap - CS314 students you should not have to
   * call this method,
   * pre: mat != null,
   */
  private static boolean inbounds(int r, int c, int[][] mat) {
    if (mat == null) {
      throw new IllegalArgumentException(
        "Failed precondition: " + "inbounds. The 2d array mat may not be null."
      );
    }
    return (
      r >= 0 && r < mat.length && mat[r] != null && c >= 0 && c < mat[r].length
    );
  }

  /*
   * helper method for canFlowOfMap - CS314 students you should not have to
   * call this method,
   * pre: mat != null, mat.length > 0
   * post: return true if mat is rectangular
   */
  private static boolean isRectangular(int[][] mat) {
    if (mat == null || mat.length == 0) {
      throw new IllegalArgumentException(
        "Failed precondition: " +
        "inbounds. The 2d array mat may not be null " +
        "and must have at least 1 row."
      );
    }
    boolean correct = true;
    final int numCols = mat[0].length;
    int row = 0;
    while (correct && row < mat.length) {
      correct = (mat[row] != null) && (mat[row].length == numCols);
      row++;
    }
    return correct;
  }

  /**
   * Problem 7: Find the minimum difference possible between teams
   * based on ability scores. The number of teams may be greater than 2.
   * The goal is to minimize the difference between the team with the
   * maximum total ability and the team with the minimum total ability.
   * <br> pre: numTeams >= 2, abilities != null, abilities.length >= numTeams
   * <br> post: return the minimum possible difference between the team
   * with the maximum total ability and the team with the minimum total
   * ability.
   * @param numTeams the number of teams to form.
   * Every team must have at least one member
   * @param abilities the ability scores of the people to distribute
   * @return return the minimum possible difference between the team
   * with the maximum total ability and the team with the minimum total
   * ability. The return value will be greater than or equal to 0.
   */
  public static int minDifference(int numTeams, int[] abilities) {
    int[] teamSums = new int[numTeams];
    int minDifference = findMinDifference(abilities, 0, teamSums);
    return minDifference;
  }

  private static int findMinDifference(
    int[] abilities,
    int index,
    int[] teamSums
  ) {
    if (index == abilities.length) {
      int maxSum = Integer.MIN_VALUE;
      int minSum = Integer.MAX_VALUE;
      for (int sum : teamSums) {
        maxSum = Math.max(maxSum, sum);
        minSum = Math.min(minSum, sum);
      }
      return maxSum - minSum;
    }

    int minDiff = Integer.MAX_VALUE;
    for (int i = 0; i < teamSums.length; i++) {
      teamSums[i] += abilities[index];
      int diff = findMinDifference(abilities, index + 1, teamSums);
      minDiff = Math.min(minDiff, diff);
      teamSums[i] -= abilities[index];
    }

    return minDiff;
  }

  /**
   * Problem 8: Maze solver.
   * <br>pre: board != null
   * <br>pre: board is a rectangular matrix
   * <br>pre: board only contains characters 'S', 'E', '$', 'G', 'Y', and '*'
   * <br>pre: there is a single 'S' character present
   * <br>post: rawMaze is not altered as a result of this method.
   * Return 2 if it is possible to escape the maze after
   * collecting all the coins.
   * Return 1 if it is possible to escape the maze
   * but without collecting all the coins.
   * Return 0 if it is not possible
   * to escape the maze. More details in the assignment handout.
   * @param rawMaze represents the maze we want to escape.
   * rawMaze is not altered as a result of this method.
   * @return per the post condition
   */

  public static int canEscapeMaze(char[][] rawMaze) {
    // Check preconditions
    if (rawMaze == null || rawMaze.length == 0 || rawMaze[0].length == 0) {
      throw new IllegalArgumentException("Maze cannot be null or empty.");
    }
    int numRows = rawMaze.length;
    int numCols = rawMaze[0].length;
    int numCoins = 0;
    int startRow = -1;
    int startCol = -1;

    // Find the number of coins and the starting position
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        char c = rawMaze[i][j];
        if (c == 'S') {
          if (startRow != -1 || startCol != -1) {
            throw new IllegalArgumentException(
              "Maze cannot have multiple starting positions."
            );
          }
          startRow = i;
          startCol = j;
        } else if (c == '$') {
          numCoins++;
        } else if (c != 'E' && c != 'G' && c != 'Y' && c != '*') {
          throw new IllegalArgumentException(
            "Maze contains invalid characters."
          );
        }
      }
    }

    // Run the maze solver
    // boolean[][] visited = new boolean[numRows][numCols];
    return runMazeSolver(rawMaze, numCoins, startRow, startCol, numRows, numCols);
  }

  private static int runMazeSolver(char[][] maze, int numCoins, int row, int col, int numRows, int numCols) {
    if(row >= numRows || row < 0 || col >= numCols || col < 0 || maze[row][col] == '*') {
      return 0;
    }
    if(maze[row][col] == 'E') {
      if(numCoins == 0) {
        return 2;
      } else {
        return 1;
      }
    }
    char val = maze[row][col];
    if(maze[row][col] == '$') {
      numCoins--;
      maze[row][col] = 'Y';
    } else if(maze[row][col] == 'S') {
      maze[row][col] = 'G';
    }else if(maze[row][col] == 'G') {
      maze[row][col] = 'Y';
    } else if (maze[row][col] == 'Y') {
      maze[row][col] = '*';
    }
    int right = runMazeSolver(maze, numCoins, row, col + 1, numRows, numCols);
    int down = runMazeSolver(maze, numCoins, row + 1, col, numRows, numCols);
    int left = runMazeSolver(maze, numCoins, row, col - 1, numRows, numCols);
    int up = runMazeSolver(maze, numCoins, row - 1, col, numRows, numCols);
    maze[row][col] = val;

    return Math.max(left, Math.max(down, Math.max(up, right)));
  }
}

