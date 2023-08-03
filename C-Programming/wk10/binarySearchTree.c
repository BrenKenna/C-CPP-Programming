/**
 * 
 * Numbers orientated Binary Search Tree (BST)
 * 
 * Trialing that the body of the tree is on the left of the root node.
 * 
 * With the view of allowing a "Table" to have its "Columns" indexed.
 *  Allowing another structure to have an array of named BSTs.
 *  But should really be its own structure, so that the size etc can
 *   be tracked
*/

// Imports
#include <stdio.h>
#include <time.h>
#define string char*


// Binary Search Tree: As one struct
typedef struct binarySearchTree {
    int data;
    struct binarySearchTree* left;
    struct binarySearchTree* right;
    struct binarySearchTree* parent;
    int isRoot;
    string memberOf;
} binarySearchTree;

// Broader aim
typedef struct indexCollection {
    binarySearchTree indexes[3];
} indexCollection;


/**
 * Initialize Tree Objects
*/

// Initialize tree
binarySearchTree* initTree() {
    binarySearchTree *tree = malloc(sizeof(binarySearchTree));
    tree-> data = NULL;
    tree-> left = NULL;
    tree-> right = NULL;
    tree-> parent = NULL;
    tree-> isRoot = 1;
    tree-> memberOf = "default_tree";
    return tree;
}

// Initialize node for tree
binarySearchTree* initNode(int value) {
    binarySearchTree *node = malloc(sizeof(binarySearchTree));
    node-> data = value;
    node-> left = NULL;
    node-> right = NULL;
    node-> parent = NULL;
    node-> isRoot = 0;
    node-> memberOf = "default_tree";
    return node;
}


// Initialize null node
binarySearchTree* initNullNode() {
    binarySearchTree *node = malloc(sizeof(binarySearchTree));
    node-> data = NULL;
    node-> left = NULL;
    node-> right = NULL;
    node-> parent = NULL;
    node-> isRoot = 0;
    return node;
}



/**
 * 
 * Basic Tree Methods
 * 
*/

// Check whether input is tail
//  <=0 no/root node
int isTail(binarySearchTree *tree) {
    if ( tree-> isRoot == 0 ) {
        if ( (tree-> left == NULL) && (tree-> right == NULL) ) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return -1;
    }
}

// Display where active node places on parent
string childPlacement(binarySearchTree *node) {

    //printf("\nDeterming placement");

    // Handle node being first
    //printf("\nFetching parent");
    binarySearchTree *parentNode = node-> parent;
    if ( parentNode-> data == NULL ) {
        return "ROOT";
    }

    // Check left if possible
    //printf("\nChecking left is present");
    if ( parentNode-> left != NULL ) {
        //printf("\nChecking left");
        if ( node -> data == parentNode-> left-> data ) {
            return "LEFT";
        }
    }
    
    // Check right if possible
    //printf("\nChecking right is present");
    if ( parentNode-> right != NULL ) {
        //printf("\nChecking right");
        if ( node -> data == parentNode-> right-> data ) {
            return "RIGHT";
        }
    }

    // Handle other
    else {
        return "NA";
    }
}


/**
 * 
 * Tree Manipulation Methods
 * 
*/

// Add new value to tree
//  No duplicates
void addNode(binarySearchTree *tree, int value) {

    // Handle root
    if ( tree-> isRoot ) {
        
        // If left is not null
        if ( tree-> left != NULL ) {
            binarySearchTree *treeNode = tree-> left;
            return addNode(treeNode, value);
        }

        // Otherwise add first element to tree
        else {
            binarySearchTree *firstTreeNode = initNode(value);
            printf("\nNew First Node value is '%d'", firstTreeNode-> data);
            tree->left = firstTreeNode;
            firstTreeNode-> parent = tree;
            return ;
        }
    }

    else {
        // Place left if smaller
        if (value < tree-> data) {

            // Set if left is null
            if (tree->left == NULL) {
                binarySearchTree *newLeft = initNode(value);
                printf("\nNew Left Node value is '%d'", newLeft-> data);
                tree->left = newLeft;
                newLeft->parent = tree;
                return ;
            }

            // Otherwise progress on left
            else {
                binarySearchTree *nextNode = tree->left;
                return addNode(nextNode, value);
            }
        }

        // Place right if bigger
        if (value > tree->data) {

            // Set if right is null
            if (tree->right == NULL) {
                binarySearchTree *newRight = initNode(value);
                printf("\nNew Right Node value is '%d'", newRight-> data);
                tree->right = newRight;
                newRight->parent = tree;
                return ;
            }

            // Otherwise progress on right
            else {
                binarySearchTree *nextNode = tree->right;
                return addNode(nextNode, value);
            }
        }
    }
    return ;
}


// Check if tree contains node
int contains(binarySearchTree *tree, int value) {
    
    // Move to tree body
    if ( tree-> isRoot == 1 ) {

        // Handle empty tree
        if ( tree-> left == NULL ) {
            return 0;
        }

        // Otherwise move
        else {
            //printf("\n\nMoving into tree");
            binarySearchTree *treeNode = tree-> left;
            return contains(treeNode, value);
        }
    }

    // Handle tree body
    else {

        // Handle found
        if ( value == tree-> data ) {
            return 1;
        }

        // Progress left
        if ( value < tree-> data ) {

            // Handle no data
            if ( tree-> left == NULL ) {
                return 0;
            }
            
            // Go to next
            else {
                binarySearchTree *nextNode = tree-> left;
                return contains(nextNode, value);
            }
        }

        // Progress right
        if ( value > tree-> data ) {

            // Handle no data
            if ( tree-> right == NULL ) {
                return 0;
            }
            
            // Go to next
            else {
                binarySearchTree *nextNode = tree-> right;
                return contains(nextNode, value);
            }
        }
    }
}


// Get matching node or null
binarySearchTree* getNode(binarySearchTree *tree, int value) {

    // Move to tree body
    if ( tree-> isRoot ) {

        // Handle empty tree
        if ( tree-> left == NULL ) {
            binarySearchTree *output = initNullNode();
            return output;
        }

        // Otherwise move
        else {
            binarySearchTree *treeNode = tree-> left;
            return getNode(treeNode, value);
        }
    }

    // Handle tree body
    else {

        // Return node if found
        if ( value == tree-> data ) {
            return tree;
        }

        // Handle left
        if ( value < tree-> data ) {

            // Handle no data, last left
            if ( tree-> left == NULL ) {
                binarySearchTree *output = initNullNode();
                return output;
            }
            
            // Go to next on the left
            else {
                binarySearchTree *nextNode = tree-> left;
                return getNode(nextNode, value);
            }
        }

        // Handle right
        if ( value > tree-> data ) {

            // Handle no data, last right
            if ( tree-> right == NULL ) {
                binarySearchTree *output = initNullNode();
                return output;
            }
            
            // Go to next on the right
            else {
                binarySearchTree *nextNode = tree-> right;
                return getNode(nextNode, value);
            }
        }
    }
}


/**
 * 
 * Generate random int BST of required size
 * 
*/
binarySearchTree* generateTree(int nRecords) {

    // Initialize tree
    printf("\n\nRoot node initialized");
    binarySearchTree *output = initTree();

    // Add required records
    for ( int i = 0; i < nRecords; i++ ) {
        int value = rand() % 300;
        addNode(output, value);
    }

    // Return tree
    printf("\nTree has been configured\n\n");
    return output;
}


/**
 * 
 * Helper methods for printing
 * 
*/

// Print values surrounding node
void printValidValues(binarySearchTree *tree) {

    //printf("\n\nPrinting values surrounding node\n");
    if (tree == NULL) {
        printf("Null node\n");
    }

    if ( !(tree-> isRoot) ) {

        // Print node value
        //printf("\n\nChecking if node has value");
        if ( tree-> data != NULL ) {
            printf("Node value is '%d'\n", tree-> data);
        }

        // Print parent value if not null
        //printf("\n\nChecking if parent has value");
        if ( tree-> parent != NULL ) {
            printf("Parent value is '%d'\n", tree-> parent-> data);
        }
        else {
            printf("Node has no non-root parent, first node in tree\n");
        }

        // Print left value if not null
        //printf("\n\nChecking if left child node has value");
        if ( tree-> left != NULL ) {
            printf("Left value is '%d'\n", tree-> left-> data);
        }
        else {
            printf("Node has no left child node\n");
        }

        // Print right value if not null
        //printf("\n\nChecking if right child node has value");
        if ( tree-> right != NULL ) {
            printf("Right value is '%d'\n", tree-> right-> data);
        }
        else {
            printf("Node has no right child node\n");
        }
    }
    else {
        printf("Node is root node\n");
    }
    //printf("\n\nNode print complete\n\n");
    return;
}


/**
 * 
 * Main program
 * 
*/
int main() {

    // Init seed & vars
    srand(time(0));
    binarySearchTree* myTree;

    // Generate tree
    printf("\nGenerating binary search tree of 100 elements:");
    myTree = generateTree(100);
    printf("\n\nDisplaying values surround root node:\n");
    printValidValues(myTree);
    printf("Root node value is '%d'", myTree-> data);

    // Test tree
    printf("\n\nDisplaying first element of tree:");
    binarySearchTree* node;
    node = myTree-> left;
    printf(
        "\nValue of the first element is '%d'\n",
        node-> data
    );

    // Test node print
    printf("\n\nDisplaying the values surrounding first node:");
    printf("\nNode:\n");
    printValidValues(node);
    printf("Left Node:\t");
    printValidValues(node-> left);
    printf("Right Node:\t");
    printValidValues(node-> right);

    // Test contains
    printf("\n\nCheck if tree contains the number 10:");
    int hasValue;
    hasValue = contains(myTree, 10);
    printf("\nTree contains 10 = '%d'\n", hasValue);

    // Test get
    printf("\n\nTesting retrevial of a node whose value is first nodes right:");
    int value = node-> right-> data;
    node = getNode(myTree, value);
    if ( node->data == NULL ) {
        printf("\nQuery result is null");
    }
    else {

        // Display data
        printf(
            "\nQuery result for '%d' is not null with value '%d', parent value is '%d'",
            value, node-> data, node-> parent-> data
        );
        printf("\n\nDisplaying the values surrounding this node:\n");
        printValidValues(node);

        // Test getting placement
        printf("\nPlacement this of node on its parent is ");
        string nodePlacement = childPlacement(node);
        printf("'%s'\n", nodePlacement);
    }


    // Test get
    printf("\n\nTesting retrevial of a node whose value is first nodes left:");
    value = node-> left-> data;
    node = getNode(myTree, value);
    if ( node->data == NULL ) {
        printf("\nQuery result is null");
    }
    else {

        // Display data
        printf(
            "\nQuery result for '%d' is not null with value '%d', parent value is '%d'",
            value, node-> data, node-> parent-> data
        );
        printf("\n\nDisplaying the values surrounding this node:\n");
        printValidValues(node);

        // Test getting placement
        printf("\nPlacement this of node on its parent is ");
        string nodePlacement = childPlacement(node);
        printf("'%s'\n", nodePlacement);
    }

    // Log completion
    printf("\n\n");
    return 0;
}