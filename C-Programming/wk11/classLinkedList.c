/**
 * Double linked list where the recursive data structure
 *  nodes holds reference to their parent, and their child.
 * 
 *  
 * OrderIn included for testing purposed
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

// Initialize a null node
list* initNullNode() {
    list *node = malloc(sizeof(list));
    node -> data = NULL;
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

// Return first node matching value
list* getNode(list *l, int value) {

    // Check if current node matches query
    if ( l-> data == value ) {
        return l;
    }

    // Otherwise handle moving to next node
    else {
        
        // Progress through list
        if ( hasNext(l) ) {
            return getNode(l-> next, value);
        }

        // Otherwise return a null node, because no match was found
        else {
            return NULL;
        }
    }
}

// Delete provided node from tree
void delete(list *elm, list **sameNode) {

    // Init and set
    list *parentNode, *childNode;
    parentNode = elm -> parent;
    childNode = elm-> next;

    // Check if element is the head node
    if ( parentNode == NULL ) {

        // Then set the child as new head
        *sameNode = childNode;
        (*sameNode)-> parent = NULL;
    }

    // Otherwise
    else {

        // Handle when child is null, end of list
        if ( childNode == NULL ) {
            printf("\nDeletion of child node");
            (*sameNode)-> parent-> next = NULL;
        }

        // Body deletion
        else {
            // Then have the parent of this node,
            //  point to this nodes child instead
            (*sameNode)-> parent-> next = childNode;
            (*sameNode)-> next-> parent = (*sameNode)-> parent;
        }
    }

    // Free the memory allocation of this element
    free(elm);
}

// Delete all nodes matching input value
int dropByValue(list *l, int query) {

    // Init vars
    printf("\n\nInitializing vars for dropping all nodes matching query '%d'\n", query);
    int output = 0;
    list* matchingNode;

    // Get node, and handle results
    printf("\nQuerying node"); printf("\n");
    matchingNode = getNode(l, query);
    if ( matchingNode == NULL ) {
        printf("\nQuery not present in list N records dropped = '%d'", output);
        return output;
    }

    // Delete until gone
    while( matchingNode != NULL ) {

        // Delete this node
        delete(matchingNode, &matchingNode);

        // Get next
        matchingNode = getNode(l, query);

        // Increment
        output++;
    }

    // Log completion
    printf("\nSuccessfully deleted N = '%d' records", output);
    return output;
}


// Delete elements of list matching query, 
// but from the second occurrence instead of first
int deDup(list *l, int query) {

    // Init vars
    printf("\n\nInitializing vars for dedupping all nodes matching query '%d'\n", query);
    int output = 0;
    list *matchingNode;

    // Get node, and handle results
    printf("\nQuerying node"); printf("\n");
    matchingNode = getNode(l, query);
    if ( matchingNode == NULL ) {
        printf("\nQuery not present in list N records dropped = '%d'", output);
        return output;
    }

    // Delete until all next replicates are gone
    list *nextMatchingNode;
    nextMatchingNode = getNode(matchingNode-> next, query);
    while( nextMatchingNode != NULL ) {

        // Delete this node
        delete(nextMatchingNode, &nextMatchingNode);

        // Get next
        nextMatchingNode = getNode(matchingNode-> next, query);

        // Increment
        output++;
    }

    // Log completion
    printf("\nSuccessfully deleted N = '%d' records", output);
    return output;
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

    // Deleting first element
    printf("\n\nTesting deletion of first element:");printf("\n");
    delete(head, &head);
    printf("\n\nDisplaying list after head deletion:\n");
    printListLimit(head, 20);

    // Drop all by value
    printf("\n\nTesting dropping elements matching query:\n"); printf("\n");
    int query, deletedRecords;
    query = 1;
    deletedRecords = dropByValue(head, query);
    printf("\nNumber of records deleted = '%d'", deletedRecords);
    printf("\n\nDisplaying list after dropping by query:\n");
    printListLimit(head, 20);

    // Drop all by value
    printf("\n\nTesting dedupping from the head node:\n"); printf("\n");
    query = head-> data;
    deletedRecords = deDup(head, query);
    printf("\nNumber of records deleted = '%d'", deletedRecords);
    printf("\n\nDisplaying list after Dedupping:\n");
    printListLimit(head, 20);

    // Log completion
    printf("\n\n");
    return 0;
}