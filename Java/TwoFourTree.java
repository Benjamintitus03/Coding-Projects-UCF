public class TwoFourTree {
    private class TwoFourTreeItem {
        int values = 1;
        int value1 = 0;
        int value2 = 0;
        int value3 = 0;
        boolean isLeaf = true;
        TwoFourTreeItem parent = null;
        TwoFourTreeItem leftChild = null;
        TwoFourTreeItem rightChild = null;
        TwoFourTreeItem centerChild = null;
        TwoFourTreeItem centerLeftChild = null;
        TwoFourTreeItem centerRightChild = null;

        public boolean isTwoNode() {
            return values == 1;
        }

        public boolean isThreeNode() {
            return values == 2;
        }

        public boolean isFourNode() {
            return values == 3;
        }

        public boolean isRoot() {
            return parent == null;
        }

        public TwoFourTreeItem(int value1) {
            this.value1 = value1;
            this.values = 1;
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

        private void printIndents(int indent) {
            for (int i = 0; i < indent; i++) System.out.printf(" ");
        }

        public void printInOrder(int indent) {
            if (!isLeaf) leftChild.printInOrder(indent + 1);
            printIndents(indent);
            System.out.printf("%d\n", value1);
            if (isThreeNode()) {
                if (!isLeaf) centerChild.printInOrder(indent + 1);
                printIndents(indent);
                System.out.printf("%d\n", value2);
            } else if (isFourNode()) {
                if (!isLeaf) centerLeftChild.printInOrder(indent + 1);
                printIndents(indent);
                System.out.printf("%d\n", value2);
                if (!isLeaf) centerRightChild.printInOrder(indent + 1);
                printIndents(indent);
                System.out.printf("%d\n", value3);
            }
            if (!isLeaf) rightChild.printInOrder(indent + 1);
        }
    }

    private TwoFourTreeItem root = null;

    public TwoFourTree() {
        root = null;
    }

    public boolean addValue(int value) {
        if (root == null) {
            root = new TwoFourTreeItem(value);
            return true;
        }
        TwoFourTreeItem node = root;
        while (!node.isLeaf) {
            if (node.isFourNode()) {
                split(node);
                node = node.parent;
            }
            if (value < node.value1) {
                node = node.leftChild;
            } else if (node.isThreeNode() && value < node.value2) {
                node = node.centerChild;
            } else {
                node = node.rightChild;
            }
        }
        insertIntoLeaf(node, value);
        return true;
    }

    private void split(TwoFourTreeItem node) {
        int midValue = node.value2;
        TwoFourTreeItem newLeft = new TwoFourTreeItem(node.value1);
        TwoFourTreeItem newRight = new TwoFourTreeItem(node.value3);

        if (node.isLeaf == false) {
            newLeft.isLeaf = false;
            newRight.isLeaf = false;
            newLeft.leftChild = node.leftChild;
            newLeft.rightChild = node.centerLeftChild;
            newRight.leftChild = node.centerRightChild;
            newRight.rightChild = node.rightChild;
        }

        if (node.isRoot()) {
            root = new TwoFourTreeItem(midValue);
            root.isLeaf = false;
            root.leftChild = newLeft;
            root.rightChild = newRight;
            newLeft.parent = root;
            newRight.parent = root;
        } else {
            insertIntoParent(node, midValue, newLeft, newRight);
        }
    }

    private void insertIntoParent(TwoFourTreeItem node, int value, TwoFourTreeItem leftChild, TwoFourTreeItem rightChild) {
        TwoFourTreeItem parent = node.parent;
        if (parent.isTwoNode()) {
            if (value < parent.value1) {
                parent.value2 = parent.value1;
                parent.value1 = value;
                parent.centerChild = parent.leftChild;
                parent.leftChild = leftChild;
                parent.rightChild = rightChild;
            } else {
                parent.value2 = value;
                parent.centerChild = rightChild;
                parent.leftChild = leftChild;
                parent.rightChild = rightChild;
            }
            parent.values++;
        } else if (parent.isThreeNode()) {
            split(parent);
            insertIntoParent(parent, value, leftChild, rightChild);
        }
    }

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

    public boolean hasValue(int value) {
        return find(root, value) != null;
    }

    private TwoFourTreeItem find(TwoFourTreeItem node, int value) {
        while (node != null) {
            if (value == node.value1 || (node.isThreeNode() && value == node.value2) || (node.isFourNode() && value == node.value3)) {
                return node;
            } else if (value < node.value1) {
                node = node.leftChild;
            } else if (node.isThreeNode() && value < node.value2) {
                node = node.centerChild;
            } else {
                node = node.rightChild;
            }
        }
        return null;
    }

    public boolean deleteValue(int value) {
        // Implement deletion logic here.
        return false;
    }

    public void printInOrder() {
        if (root != null) root.printInOrder(0);
    }
}
