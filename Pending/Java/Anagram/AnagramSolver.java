/* CS 314 STUDENTS: FILL IN THIS HEADER.
 *
 * Student information for assignment:
 *
 *  On my honor, <NAME>, this programming assignment is my own work
 *  and I have not provided this code to any other student.
 *
 *  UTEID:
 *  email address:
 *  TA name:
 *  Number of slip days I am using:
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

// class LetterInventory {

//   private int[] inventory;
//   private int size;
//   private static final int ALPHABET_SIZE = 26;

//   public LetterInventory(String data) {
//     inventory = new int[ALPHABET_SIZE];
//     size = 0;
//     for (int i = 0; i < data.length(); i++) {
//       char ch = data.charAt(i);
//       if (Character.isLetter(ch)) {
//         ch = Character.toLowerCase(ch);
//         inventory[ch - 'a']++;
//         size++;
//       }
//     }
//   }

//   public int get(char letter) {
//     if (!Character.isLetter(letter)) {
//       throw new IllegalArgumentException();
//     }
//     letter = Character.toLowerCase(letter);
//     return inventory[letter - 'a'];
//   }

//   public int size() {
//     return size;
//   }

//   public boolean isEmpty() {
//     return size == 0;
//   }

//   public String toString() {
//     String result = "";
//     for (int i = 0; i < inventory.length; i++) {
//       for (int j = 0; j < inventory[i]; j++) {
//         result += (char) (i + 'a');
//       }
//     }
//     return result;
//   }

//   public LetterInventory add(LetterInventory other) {
//     if (other == null) {
//       throw new IllegalArgumentException();
//     }
//     LetterInventory result = new LetterInventory("");
//     for (int i = 0; i < inventory.length; i++) {
//       result.inventory[i] = inventory[i] + other.inventory[i];
//     }
//     result.size = size + other.size;
//     return result;
//   }

//   public LetterInventory subtract(LetterInventory other) {
//     if (other == null) {
//       throw new IllegalArgumentException();
//     }
//     LetterInventory result = new LetterInventory("");
//     for (int i = 0; i < inventory.length; i++) {
//       result.inventory[i] = inventory[i] - other.inventory[i];
//       if (result.inventory[i] < 0) {
//         return null;
//       }
//     }
//     result.size = size - other.size;
//     return result;
//   }

//   public boolean equals(Object other) {
//     if (other == null) {
//       return false;
//     }
//     if (other.getClass() != this.getClass()) {
//       return false;
//     }
//     LetterInventory otherInventory = (LetterInventory) other;
//     for (int i = 0; i < inventory.length; i++) {
//       if (inventory[i] != otherInventory.inventory[i]) {
//         return false;
//       }
//     }

//     return true;
//   }
// }

public class AnagramSolver {

  private Set<String> dictionary;

  /*
   * pre: list != null
   * @param list Contains the words to form anagrams from.
   */
  public AnagramSolver(Set<String> dictionary) {
    if (dictionary == null) {
      throw new IllegalArgumentException();
    }
    this.dictionary = dictionary;
  }

  /*
   * pre: maxWords >= 0, s != null, s contains at least one
   * English letter.
   * Return a list of anagrams that can be formed from s with
   * no more than maxWords, unless maxWords is 0 in which case
   * there is no limit on the number of words in the anagram
   */
  public List<List<String>> getAnagrams(String s, int maxWords) {
    if (s == null || maxWords < 0 || s.length() == 0) {
      throw new IllegalArgumentException();
    } else {
      LetterInventory inventory = new LetterInventory(s);
      List<List<String>> anagrams = new ArrayList<List<String>>();
      List<String> anagram = new ArrayList<String>();
      getAnagramsHelper(inventory, maxWords, anagrams, anagram);
      return anagrams;
    }
  }

  private void getAnagramsHelper(
    LetterInventory inventory,
    int maxWords,
    List<List<String>> anagrams,
    List<String> anagram
  ) {
    if (inventory.isEmpty()) {
      anagrams.add(new ArrayList<String>(anagram));
    } else {
      for (String word : dictionary) {
        if (maxWords == 0 || anagram.size() < maxWords) {
          LetterInventory wordInventory = new LetterInventory(word);
          if (inventory.subtract(wordInventory) != null) {
            anagram.add(word);
            getAnagramsHelper(
              inventory.subtract(wordInventory),
              maxWords,
              anagrams,
              anagram
            );
            anagram.remove(anagram.size() - 1);
          }
        }
      }
    }
  }
}
