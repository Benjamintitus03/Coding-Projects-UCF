public class TwoFourTree {
    // Node class representing individual elements in the 2-3-4 tree.
    private class TwoFourTreeItem {
        int values = 1; // Number of values stored in the node
        int value1 = 0, value2 = 0, value3 = 0; // Data values for 2-node, 3-node, and 4-node
        boolean isLeaf = true; // True if the node is a leaf
        TwoFourTreeItem parent = null; // Parent node
        // Child pointers for tree traversal
        TwoFourTreeItem leftChild = null, rightChild = null, centerChild = null, centerLeftChild = null, centerRightChild = null;

        // Check if node is a 2-node
        public boolean isTwoNode() {
            return values == 1;
        }

        // Check if node is a 3-node
        public boolean isThreeNode() {
            return values == 2;
        }

        // Check if node is a 4-node
        public boolean isFourNode() {
            return values == 3;
        }

        // Check if the node is the root
        public boolean isRoot() {
            return parent == null;
        }

        // Constructors for node initialization
        public TwoFourTreeItem(int value1) {
            this.value1 = value1;
        }

        public TwoFourTreeItem(int value1, int value2) {
            this.value1 = value1;
            this.value2 = value2;
            this.values = 2;
        }

        public TwoFourTreeItem(int value1, int value2, int value3) {
            this.value1 = value1;
            this.value2 = value2;
            this.value3 = value3;
            this.values = 3;
        }

        // Print the subtree rooted at this node in in-order traversal
        public void printInOrder(int indent) {
            if (!isLeaf) leftChild.printInOrder(indent + 1);
            System.out.printf("%" + (indent * 2) + "s%d\n", "", value1);
            if (isThreeNode()) {
                if (!isLeaf) centerChild.printInOrder(indent + 1);
                System.out.printf("%" + (indent * 2) + "s%d\n", "", value2);
            } else if (isFourNode()) {
                if (!isLeaf) centerLeftChild.printInOrder(indent + 1);
                System.out.printf("%" + (indent * 2) + "s%d\n", "", value2);
                if (!isLeaf) centerRightChild.printInOrder(indent + 1);
                System.out.printf("%" + (indent * 2) + "s%d\n", "", value3);
            }
            if (!isLeaf) rightChild.printInOrder(indent + 1);
        }
    }

    private TwoFourTreeItem root = null;

    // Constructor for an empty tree
    public TwoFourTree() {
        root = null;
    }

    // Add a value to the tree
    public boolean addValue(int value) {
        if (root == null) {
            // Initialize root if the tree is empty
            root = new TwoFourTreeItem(value);
            return true;
        }
        TwoFourTreeItem node = root;
        while (!node.isLeaf) {
            if (node.isFourNode()) {
                split(node); // Split the 4-node
                node = node.parent; // Move up after splitting
            }
            // Navigate to the correct child based on value
            if (value < node.value1) {
                node = node.leftChild;
            } else if (node.isThreeNode() && value < node.value2) {
                node = node.centerChild;
            } else {
                node = node.rightChild;
            }
        }
        // Insert value into the appropriate leaf node
        if (find(root, value) != null) {
            // If duplicates are not allowed
            return false;
        }
        insertIntoLeaf(node, value);
        return true;
    }
    
    private void insertIntoParent(TwoFourTreeItem node, int value, TwoFourTreeItem leftChild, TwoFourTreeItem rightChild) {
        TwoFourTreeItem parent = node.parent;
    
        if (parent.isTwoNode()) {
            // Case: Parent is a 2-node
            if (value < parent.value1) {
                // Insert into the first position
                parent.value2 = parent.value1;
                parent.value1 = value;
    
                parent.rightChild = parent.centerChild;
                parent.leftChild = leftChild;
                parent.centerChild = rightChild;
            } else {
                // Insert into the second position
                parent.value2 = value;
    
                parent.centerChild = leftChild;
                parent.rightChild = rightChild;
            }
            parent.values++; // Update the number of values in the parent
            leftChild.parent = parent;
            rightChild.parent = parent;
        } else if (parent.isThreeNode()) {
            // Case: Parent is a 3-node (requires split)
            split(parent);
            insertIntoParent(parent, value, leftChild, rightChild);
        }
    }
    

    //Split a 4-node into two nodes
    private void split(TwoFourTreeItem node) {
        int midValue = node.value2; // Middle value becomes the parent
        TwoFourTreeItem newLeft = new TwoFourTreeItem(node.value1);
        TwoFourTreeItem newRight = new TwoFourTreeItem(node.value3);

        if (!node.isLeaf) {
            newLeft.isLeaf = false;
            newRight.isLeaf = false;
            newLeft.leftChild = node.leftChild;
            newLeft.rightChild = node.centerLeftChild;
            newRight.leftChild = node.centerRightChild;
            newRight.rightChild = node.rightChild;
        }

        if (node.isRoot()) {
            // If splitting the root, create a new root
            root = new TwoFourTreeItem(midValue);
            root.isLeaf = false;
            root.leftChild = newLeft;
            root.rightChild = newRight;
            newLeft.parent = root;
            newRight.parent = root;
        } else {
            // Insert the middle value into the parent
            insertIntoParent(node, midValue, newLeft, newRight);
        }
    }

    // Insert a value into a leaf node
    private void insertIntoLeaf(TwoFourTreeItem node, int value) {
        if (node.isTwoNode()) {
            if (value < node.value1) {
                node.value2 = node.value1;
                node.value1 = value;
            } else {
                node.value2 = value;
            }
            node.values++;
        } else if (node.isThreeNode()) {
            if (value < node.value1) {
                node.value3 = node.value2;
                node.value2 = node.value1;
                node.value1 = value;
            } else if (value < node.value2) {
                node.value3 = node.value2;
                node.value2 = value;
            } else {
                node.value3 = value;
            }
            node.values++;
        }
    }

    // Find a value in the tree
    public boolean hasValue(int value) {
        return find(root, value) != null;
    }

    private TwoFourTreeItem find(TwoFourTreeItem node, int value) {
        while (node != null) {
            if (value == node.value1 || (node.isThreeNode() && value == node.value2) || (node.isFourNode() && value == node.value3)) {
                return node; // Value found
            } else if (value < node.value1) {
                node = node.leftChild;
            } else if (node.isThreeNode() && value < node.value2) {
                node = node.centerChild;
            } else {
                node = node.rightChild;
            }
        }
        return null; // Value not found
    }

    public boolean deleteValue(int value) {
        TwoFourTreeItem node = find(root, value);
        if (node == null) {
            return false; // Value not found
        }
    
        if (node.isLeaf) {
            removeFromLeaf(node, value);
        } else {
            removeFromInternal(node, value);
        }
    
        if (root.values == 0) {
            root = root.leftChild; // Adjust root if it becomes empty
        }
        return true;
    }
    
    // Remove value from a leaf node
    private void removeFromLeaf(TwoFourTreeItem node, int value) {
        if (node.isTwoNode()) {
            handleUnderflow(node);
        } else if (node.isThreeNode()) {
            if (value == node.value1) {
                node.value1 = node.value2;
            }
            node.value2 = 0;
            node.values--;
        } else if (node.isFourNode()) {
            if (value == node.value1) {
                node.value1 = node.value2;
                node.value2 = node.value3;
            } else if (value == node.value2) {
                node.value2 = node.value3;
            }
            node.value3 = 0;
            node.values--;
        }
    }
    
    // Remove value from an internal node
    private void removeFromInternal(TwoFourTreeItem node, int value) {
        TwoFourTreeItem replacementNode;
        if (value == node.value1) {
            replacementNode = findPredecessor(node.leftChild);
            node.value1 = replacementNode.value1;
        } else if (node.isThreeNode() && value == node.value2) {
            replacementNode = findPredecessor(node.centerChild);
            node.value2 = replacementNode.value1;
        } else {
            replacementNode = findPredecessor(node.rightChild);
            node.value3 = replacementNode.value1;
        }
        removeFromLeaf(replacementNode, replacementNode.value1);
    }
    
    // Handle underflow for a node with fewer than 2 keys
    private void handleUnderflow(TwoFourTreeItem node) {
        TwoFourTreeItem parent = node.parent;
        if (parent == null) {
            return; // Root case handled separately
        }
    
        TwoFourTreeItem sibling = getSibling(node);
    
        if (sibling != null && sibling.values > 1) {
            borrowFromSibling(node, sibling, parent);
        } else {
            mergeWithSibling(node, sibling, parent);
        }
    }
    
    // Helper to find in-order predecessor
    private TwoFourTreeItem findPredecessor(TwoFourTreeItem node) {
        while (!node.isLeaf) {
            node = node.rightChild;
        }
        return node;
    }
    
    // Borrow a value from a sibling
    private void borrowFromSibling(TwoFourTreeItem node, TwoFourTreeItem sibling, TwoFourTreeItem parent) {
        // Implement borrowing logic (adjust pointers/values)
    }
    
    // Merge node with its sibling
    private void mergeWithSibling(TwoFourTreeItem node, TwoFourTreeItem sibling, TwoFourTreeItem parent) {
        // Implement merging logic (combine values and children)
    }
    
    // Get sibling of a node
    private TwoFourTreeItem getSibling(TwoFourTreeItem node) {
        TwoFourTreeItem parent = node.parent;
        if (parent.leftChild == node) {
            return parent.centerChild != null ? parent.centerChild : parent.rightChild;
        } else if (parent.centerChild == node) {
            return parent.rightChild != null ? parent.rightChild : parent.leftChild;
        } else {
            return parent.centerChild != null ? parent.centerChild : parent.leftChild;
        }
    }
    
    // Print the tree in in-order traversal
    public void printInOrder() {
        if (root != null) root.printInOrder(0);
    }
}
