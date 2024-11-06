import java.util.Stack;

public class WordScramble {

    public static String encode(String input) {
        Stack<StringBuilder> groupStack = new Stack<>();
        Stack<Character> vowelStack = new Stack<>();
        StringBuilder currentGroup = new StringBuilder();

        for (char ch : input.toCharArray()) {
            if (ch == '1') {
                // Start a new group by pushing the current group to the stack
                groupStack.push(currentGroup);
                currentGroup = new StringBuilder(); // Reset current group
            } else if (ch == '2') {
                // End of a group: insert the vowel at the center if available and if currentGroup has characters
                if (!vowelStack.isEmpty() && currentGroup.length() > 0) {
                    char vowel = vowelStack.pop();
                    int middle = currentGroup.length() / 2;
                    currentGroup.insert(middle, vowel); // Insert vowel in the center
                }

                // Append current group to the outer group
                if (!groupStack.isEmpty()) {
                    StringBuilder outerGroup = groupStack.pop();
                    outerGroup.append(currentGroup);
                    currentGroup = outerGroup;
                }
            } else if ("aeiou".indexOf(ch) >= 0) {
                // If it's a vowel, push it to the vowel stack
                vowelStack.push(ch);
            } else {
                // If it's a consonant, add it to the current group
                currentGroup.append(ch);
            }
        }

        // Return the final assembled result
        return currentGroup.toString();
    }

    public static void main(String[] args) {
        System.out.println(encode("1top2"));           // Expected Output: tpo
        System.out.println(encode("11top2e1cat22"));   // Expected Output: tpoctae
        System.out.println(encode("111tom2op2it2"));   // Expected Output: tmopoti
        System.out.println(encode("11top2i1tom22"));   // Expected Output: tpotmoi
    }
}
