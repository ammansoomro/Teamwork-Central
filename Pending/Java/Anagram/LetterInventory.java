public class LetterInventory {
    private int[] inventory;
    private int size;
    private static final int ALPHABET_SIZE = 26;
    
    public LetterInventory(String data) {
        inventory = new int[ALPHABET_SIZE];
        size = 0;
        for (int i = 0; i < data.length(); i++) {
            char ch = data.charAt(i);
            if (Character.isLetter(ch)) {
                ch = Character.toLowerCase(ch);
                inventory[ch - 'a']++;
                size++;
            }
        }
    }
    
    public int get(char letter) {
        if (!Character.isLetter(letter)) {
            throw new IllegalArgumentException();
        }
        letter = Character.toLowerCase(letter);
        return inventory[letter - 'a'];
    }
    
    public int size() {
        return size;
    }
    
    public boolean isEmpty() {
        return size == 0;
    }
    
    public String toString() {
        String result = "";
        for (int i = 0; i < inventory.length; i++) {
            for (int j = 0; j < inventory[i]; j++) {
                result += (char) (i + 'a');
            }
        }
        return result;
    }
    
    public LetterInventory add(LetterInventory other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        LetterInventory result = new LetterInventory("");
        for (int i = 0; i < inventory.length; i++) {
            result.inventory[i] = inventory[i] + other.inventory[i];
        }
        result.size = size + other.size;
        return result;
    }
    
    public LetterInventory subtract(LetterInventory other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        LetterInventory result = new LetterInventory("");
        for (int i = 0; i < inventory.length; i++) {
            result.inventory[i] = inventory[i] - other.inventory[i];
            if (result.inventory[i] < 0) {
                return null;
            }
        }
        result.size = size - other.size;
        return result;
    }
    
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        }
        if (other.getClass() != this.getClass()) {
            return false;
        }
        LetterInventory otherInventory = (LetterInventory) other;
        for (int i = 0; i < inventory.length; i++) {
            if (inventory[i] != otherInventory.inventory[i]) {
                return false;
            }
        }

        return true;
    }

}
