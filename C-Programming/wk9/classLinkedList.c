/**
 * Double linked list where the recursive data structure
 *  nodes holds reference to their parent, and their child.
 * 
 * Given quirks with sorting, list could start a root node
 *  which points to first elemment.
 *  
 * OrderIn has to be updated following a drop
 * 
 * Includes methods for:
 *  1). Initializing null node
 *  2). Adding a new integer to list.
 *  3). Sorting.
 *  4). Displaying list, or until element counter is reached.
 *  5). Dropping & Dedupping list.
 *  6). Generating dataset of random size.
 *  7). Whether list contains a value.
*/

// Imports
#include <stdio.h>
#include <time.h>

/**
 * Double linked list
*/
typedef struct list {
    int data;
    int orderIn;
    struct list* next;
    struct list* parent;
} list;


// Initialize node with value
list* initNode(int value) {
    list *node = malloc(sizeof(list));
    node -> data = value;
    node -> next = NULL;
    node-> orderIn = -1;
    node -> parent = NULL;
    return node;
}


// Return whether list is empty
int isEmpty(list *l) {
    return l -> orderIn >= 0;
}


// Return whether list has next element
int hasNext(list *l) {
    return l->next != NULL;
}


// Add a new value
void addNode(list *l, int value) {
    if ( !hasNext(l) ) {
        list *newNode = initNode(value);
        newNode-> orderIn = (l->orderIn)+1;
        l -> next = newNode;
        newNode-> parent = l;
    }
    else {
        addNode(l->next, value);
    }
}

// Return whether list has number
int contains(list *l, int value) {
    if ( l-> data == value ) {
        return 1;
    }
    else {
        if ( hasNext(l) ) {
            return contains(l-> next, value);
        }
        else {
            return 0;
        }
    }
}


// Swap the contents,
// but not pointers logic of two nodes
void swap(list *parent, list *child) {

    // Init temp var
    list* temp = initNode(parent->data);
    
    // Make parent the child
    parent->data = child->data;

    // Child the parent
    child->data = temp->data;
}


// Bubble sort list
void bubbleSort(list *l) {
    
    // Init sort logic based on side
    int sorted = l->next == NULL;

    // Init sorting vars
    int indexTrack = 0;
    int iters = 0;
    int counter = 0;
    list *currentNode = l;
    list *nextNode = l->next;

    // Sort until done
    while ( sorted == 0 ) {

        // Scan elements
        //printf("\n\n\nstarting an iteration");
        while ( hasNext(currentNode) ) {
            
            // Compare current & next
            //printf("\n'%d' > '%d' == '%d'", currentNode-> data, nextNode-> data, currentNode-> data > nextNode-> data);
            if ( currentNode-> data > nextNode-> data ) {
                swap(currentNode, nextNode);
                counter++;
            }

            // Progress through list
            currentNode = currentNode->next;
            nextNode = nextNode->next;
            indexTrack++;
        }

        // Reset counter
        //printf("\n\ncompleted an iteration, n swaps = '%d'", counter);
        if ( counter == 0 ) {
            printf("\nSorting completed after '%d' iterations", iters);
            sorted = 1;
        }
        counter = 0;
        currentNode = l;
        nextNode = l->next;
        iters++;
    }
}


// Print list
void printList(list *l) {
    if ( l != NULL  ) {
        printf("\n%d", l->data);
        l = l->next;
        printList(l);
    }
}

// Print list until orderIn has been reached
void printListLimit(list *l, int limit) {
    if ( l != NULL ) {
        if ( l-> orderIn <= limit ) {
            printf("\nElement '%d' is '%d", l->orderIn, l->data);
            l = l->next;
            printListLimit(l, limit);
        }
    }
}

// Generate a random dataset of required size
list* generateData(int nRecords) {
    list* output;
    output = initNode(rand()%49);
    output->orderIn = 0;
    for (int i = 1; i < nRecords; i++) {
        addNode(output, rand()%49);
    }
    return output;
}

// Make Parent node point to inputs Next/child
void skipNode(list *l) {

    // Pass on no next
    if ( l-> next != NULL ) {

        // Handle null parent
        list *childNode = l->next;
        if ( l-> parent == NULL ) {

            // Init vars
            list *currentNode = l;
            printf(
                "\nCurrent Node Data = '%d' at '%d', Next Node Data = '%d' at '%d'",
                currentNode->data, currentNode->orderIn, childNode->data, childNode->orderIn
            );

            // Make child parent
            currentNode = childNode;

            // 
            l = currentNode;
            printf(
                "\nCurrent Node Data = '%d' at '%d', Next Node Data = '%d' at '%d'",
                currentNode->data, currentNode->orderIn, currentNode->next->data, currentNode->next->orderIn
            );
        }

        // Otherwise body of list
        else {

            // Init vars
            //printf("\nBody drop");
            list *parentNode = l->parent;

            // Make parent.next, childNode
            parentNode->next = childNode;
            childNode->parent = parentNode;
        }

        // Decrement order
        childNode-> orderIn--;
        // childNode->next->orderIn--;
    }
}


// Drop nodes from list mathing value
//  Want the Parent to skip the child
void dropByValue(list* l, int value) {

    // Do if not null
    if ( l != NULL ) {
        
        // Check if node matches
        list* currentNode = l;
        if ( currentNode->data == value ) {
            skipNode(currentNode);
        }

        // Go to next
        currentNode = currentNode->next;
        dropByValue(currentNode, value);
    }
}

// Dedup
void deDup(list* l) {

    // Do if not null
    if ( l != NULL ) {
        
        // Check if node matches
        list* currentNode = l;
        if ( currentNode->next != NULL ) {
            list* nextNode = currentNode-> next;
            if ( currentNode-> data == nextNode-> data ) {
                skipNode(currentNode);
            }

            // Go to next
            currentNode = currentNode-> next;
            deDup(currentNode);
        }
    }
}

/**
 * Main program
*/
int main() {

    // Initialize list
    srand(time(0));
    list intList;
    list* head;
    
    // Add head node
    printf("\nCreating blank node");
    head = initNode(10);
    printf("\nVerifying next is null '%d', and is empty '%d'\n", isEmpty(head));
    addNode(head, 600); 

    // Add new
    printf("\n\nAdding new values:");
    addNode(head, -1); addNode(head, 8); addNode(head, -3);
    addNode(head, 40); addNode(head, 15); addNode(head, 100);
    addNode(head, -150);
    printf("\n\nDisplaying list:");
    printList(head);

    // List contains int
    int hasVal;
    printf("\n\nChecking contains operations");
    hasVal = contains(head, 40);
    printf("\nHas 40 = %d", hasVal);
    hasVal = contains(head, 3000);
    printf("\nHas 3000 = %d", hasVal);

    // Swap first two elements
    printf("\n\nRecursively Bubble sorting list:");
    bubbleSort(head);
    printf("\n\nDisplaying list after sort:");
    printList(head);


    // Generate random data
    printf("\n\nGenerating random dataset");
    head = generateData(200);
    bubbleSort(head);
    printf("\n\nDisplaying list after sort: N = 20 Elements");
    printListLimit(head, 20);


    // Drop value of head node: Deups
    printf("\n\nTest dropping the first value of list");
    int valToDrop = head->data;
    dropByValue(head, valToDrop);
    printf("\n\nDisplaying list after drop");
    printListLimit(head, 35);


    // Drop value in body node: As expected
    printf("\n\nTest dropping the another value");
    valToDrop = 3;
    dropByValue(head, valToDrop);
    printf("\n\nDisplaying list after drop");
    printListLimit(head, 35);

    // Drop value of head node
    printf("\n\nTesting dedupping");
    deDup(head);
    printf("\n\nDisplaying list after dedup");
    printListLimit(head, 40);

    // Log completion
    printf("\n\n");
    return 0;
}