/**
 * Since I'm not a poker player, didn't waste additional time on
 *  the analysis side. Templated some data structures, and loose
 *  function to classify side.
 * 
 * The sorting aspect was preferred, because it was easier for me 
 *  to see how I can learn more about call by reference/value.
 * 
 * For instance if the code that makes up main, passes the deck
 *  to a void playGame(deckArr myDeck). Then the changes made to
 *  that game-deck, will not change the main-deck.
 * 
 * # Compile with
 * gcc -w -o deck-O-Cards deck-O-Cards.c
 * 
*/

// Dependencies & constants
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define string char*
#define sizeOf 5

/**
 * Supporting types
*/
typedef enum suit {
    clubs, diamonds, spades, hearts
} suit;

typedef struct card {
    short val;
    suit type;
} card;

// Separated out initially
//  but only really need one
typedef struct deckArr {
    card cards[52];
} deckArr;
typedef struct hand {
    card cards[sizeOf];
} hand;



/**
 * Deck Creation & Shuffling:
 * 
 * - Shuffling a fresh deck, randomly swaps elements then chunks.
 * - Shuffling a deck for a round, does that split deck trick, 
 *    and swaps smaller chunks.
*/
deckArr generateDeck();
void shuffleFreshDeck(deckArr *deck);
void interleaveDeck(deckArr *deck);
void swapDeckChunks(deckArr *deck, int amount);

deckArr generateDeck() {
    int counter = 0;
    deckArr deck;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            card newCard;
            newCard.type = i;
            newCard.val = j;
            deck.cards[counter] = newCard;
            counter++;
        }
    }
    // Suffle then return
    shuffleFreshDeck(&deck);
    return deck;
}
void shuffleFreshDeck(deckArr *deck) {
    deckArr temp = *deck;
    for ( int i = 0; i < 52; i++ ) {
        int cardA, cardB;
        cardA = (rand() % 50) + 1;
        cardB = (rand() % 50) + 1;
        while(cardB == cardA) {
            cardB = (rand() % 50) + 1;
        }
        swapCards(&temp.cards[cardA], &temp.cards[cardB]);
    }

    // Swap large chunks
    swapDeckChunks(&temp, 10);
    *deck = temp;
}

// Shuffling a deck for another round
void interleaveDeck(deckArr *deck) {
    
    // Init vars
    deckArr activeDeck = *deck;
    deckArr output;

    // Interleave
    int counter = 0, left = 0, right = 26;
    while (left < 26 && right < 52) {

        // Take cards
        card leftCard, rightCard;
        leftCard = activeDeck.cards[left];
        rightCard = activeDeck.cards[right];

        // Place cards
        output.cards[counter] = rightCard;
        counter++;
        output.cards[counter] = leftCard;
        counter++;

        // Increment
        left++;
        right++;
    }

    // Update active deck
    *deck = output;
}

// Helper method to see where to 
// put the chunk of cards from the middle
bool getChunkPlace() {
    int num = (rand() % 100) + 1;
    if (num < 50) {
        return true;
    }
    else {
        return false;
    }
}

// Swap a chunk of cards from the middle
//  to the top, or bottom (decided internally)
void swapDeckChunks(deckArr *deck, int amount) {
    
    // Init vars
    deckArr temp = *deck;
    int startMid, endMid, startTarget, endTarget;
    
    // Set middle range to swap target
    startMid = 26;
    endMid = startMid + amount;

    // Define target range based on placement
    bool useTop = getChunkPlace();
    if (useTop) {
        endTarget = 52;
        startTarget = endTarget - amount;
    }
    else {
        startTarget = 0;
        endTarget = startTarget + amount;
    }

    // Swap
    while( startTarget < endTarget ) {

        // Swap
        swapCards(&temp.cards[startMid], &temp.cards[startTarget]);

        // Increment pointers
        startMid++;
        startTarget++;
    }

    // Update deck
    *deck = temp;
}

// Wrapper method for shuffling an in-game deck
void shuffleDeck(deckArr *deck) {

    // Interleave
    deckArr temp = *deck;
    interleaveDeck(&temp);

    // Chunk swap
    for ( int i = 0; i < 6; i++) {
        swapDeckChunks(&temp, 6);
    }

    // Update deck
    *deck = temp;
}

// Deal a hand from deck
hand dealHand(deckArr deck) {
    hand output;
    for(int i = 0; i < sizeOf; i++) {
        output.cards[i] = deck.cards[i];
    }
    return output;
}

// Wrapper method for playing a round
hand dealShuffledHand(deckArr *deck) {

    // Init vars
    hand output;
    deckArr temp = *deck;

    // Shuffle
    shuffleDeck(&temp);

    // Deal hand
    output = dealHand(temp);

    // Update deck: dealHand should pull from stack
    // hence last
    *deck = temp;

    // Return new sorted hand
    sortHand(&output);
    return output;
}


/**
 * Card sorting methods
*/

// Swap two cards
void swapCards(card *a, card *b) {
    card temp = *a;
    *a = *b;
    *b = temp;
}

// Sort a hand of cards,
// helper method for analysiss/readability of hand
void sortHand(hand *activeHand) {
    hand temp = *activeHand;
    bool sorting = true;
    int iters = 0;
    while ( sorting ) {
        int counter=0;
        for ( int i = 0; i < sizeOf - 1; i++ ) {
            if ( temp.cards[i].val > temp.cards[i+1].val ) {
                swapCards(&temp.cards[i], &temp.cards[i+1]);
                counter++;
            }
        }
        if (counter == 0) {
            sorting = false;
            printf("\nData for your cards was sorted after '%d' iterations\n", iters);
        }
        else {
            iters++;
        }
    }
    //printHand(temp);
    *activeHand = temp;
}


/**
 * Hand analysis tracking
*/

// Data structure to indicate the best hand to play,
//  as well keep track of hands played
typedef struct handCount {
    int zip, aceHighLow, pair, twoPair, threeKind;
    int straight, flush, fullHouse, fourKind;
    int straightFlush, royalFlush; 
} handCount;

// Initializes an empty hand analysis
handCount initHand = {
    .zip = 0, .aceHighLow = 0, .pair = 0, .twoPair = 0,
    .threeKind = 0, .straight = 0, .flush = 0, .fullHouse = 0,
    .fourKind = 0, .straightFlush = 0, .royalFlush = 0
};

// Analyze the hand in one scan... 
//   Bit ambitious for poker knoob :)
handCount analyzeHand(card hand[]) {
    handCount initHand;

    bool pair = false;
    bool threePair = false;
    bool fourPair = false;
    bool activeStraight = false;
    bool activeFlush = false;

    int pairCount = 0, threePairCount = 0, fourPairCount = 0;
    int flushCount = 0;
    int straight = 0;
    int royal = 0;
    for (int i = 0; i < sizeOf-1; i++) {

        // Current & next card
        card currentCard = hand[i];
        card nextCard = hand[i+1];

        // Check if current card pairs with next
        if ( currentCard.val == nextCard.val ) {
            if ( pair ) {
                if (threePair) {
                    fourPair = true;
                    fourPairCount++;
                } 
                else {
                    threePair = true;
                    threePairCount++;
                }
            }
            else {
                pair = true;
                pairCount++;
            }
        }

        // Check if next is one higher
        if ( currentCard.val+1 == nextCard.val ) {
            if ( activeStraight ) {
                straight++;
            }
            else {
                activeStraight = true;
                straight = 1;
            }
        }

        // Check flush
        if ( currentCard.type = nextCard.type ) {
            if ( activeFlush ) {
                flushCount++;
            }
            else {
                activeFlush = true;
                flushCount = 1;
            }
        }
    }

    // Update accordingly
    
    return initHand;
}

// Add the score of the current hand, to an analysis tracker
void incrementCount(handCount tracker, handCount currentHand) {
    tracker.zip += currentHand.zip;
    tracker.aceHighLow += currentHand.aceHighLow;
    tracker.pair += currentHand.pair;
    tracker.threeKind += currentHand.threeKind;
    tracker.straight += currentHand.straight;
    tracker.flush += currentHand.flush;
    tracker.fourKind += currentHand.fourKind;
    tracker.straightFlush += currentHand.straightFlush;
    tracker.royalFlush += currentHand.royalFlush;
}

// Print the analysis tracker
void printProps(handCount tracker, int count) {
    printf("\nNothing:\tCount = '%d', Proportion = '%lf'", tracker.zip, ((double) (tracker.zip/count)));
    printf("\nAce High/Low:\tCount = '%d', Proportion = '%lf'", tracker.aceHighLow, ((double) (tracker.aceHighLow/count)));
    printf("\nPair:\tCount = '%d', Proportion = '%lf'", tracker.pair, ((double) (tracker.pair/count )));
    printf("\nTwo Pair:\tCount = '%d', Proportion = '%lf'", tracker.twoPair, ((double) (tracker.twoPair/count)));
    printf("\nThree of Kind:\tCount = '%d', Proportion = '%lf'", tracker.threeKind, ((double) (tracker.threeKind/count)));
    printf("\nStraight:\tCount = '%d', Proportion = '%lf'", tracker.straight, ((double) (tracker.straight/count)));
    printf("\nFlush:\tCount = '%d', Proportion = '%lf'", tracker.flush, ((double) (tracker.flush/count )));
    printf("\nFull Houset:\tCount = '%d', Proportion = '%lf'", tracker.fullHouse, ((double) (tracker.fullHouse/count)));
    printf("\nFour of Kind:\tCount = '%d', Proportion = '%lf'", tracker.fourKind, ((double) (tracker.fourKind/count)));
    printf("\nStraight Flush:\tCount = '%d', Proportion = '%lf'", tracker.straightFlush, ((double) (tracker.straightFlush/count)));
    printf("\nRoyal Flush:\tCount = '%d', Proportion = '%lf'", tracker.royalFlush, ((double) (tracker.royalFlush/count)));
}


/**
 * Functions to display a deck & a hand o'cards
*/
void printDeck(deckArr deck) {
    printf("\n\n------- Displaying Deck -------\n");
    for ( int i = 0; i < 52; i++) {
        card currentCard = deck.cards[i];
        printf("Card-%d: Suit is '%d', and Value is '%d'\n", i, currentCard.type, currentCard.val);
    }
    printf("------- Displaying Deck -------\n");
}
void printHand(hand myHand) {
    printf("\n\n------- Displaying Hand -------\n");
    for ( int i = 0; i < sizeOf; i++ ) {
        card currentCard = myHand.cards[i];
        printf("Card-%d: Suit is '%d' and Value is '%d'\n", i, currentCard.type, currentCard.val);
    }
    printf("------- Displaying Hand -------\n");
}


/**
 * Main program
 *  => Displays sorting
 *  => Didn't fancy copying the MC solution from github ;)
*/
int main() {

    // Init vars
    srand(time(0));
    deckArr myDeck;
    hand activeHand;

    // Generate a deck
    printf("\nGenerating a fresh deck:");
    myDeck = generateDeck();
    printDeck(myDeck);

    // Fetch and display a hand
    printf("\n\nDealing a hand from un-shuffled deck:");
    activeHand = dealHand(myDeck);
    printHand(activeHand);

    // Shuffle fresh deck
    printf("\n\nShuffling fresh deck:");
    shuffleFreshDeck(&myDeck);
    printDeck(myDeck);

    // Fetch and display a hand
    printf("\n\nPlaying first round:");
    activeHand = dealShuffledHand(&myDeck);
    printf("\nDisplaying the Deck for this round:");
    printDeck(myDeck);
    printf("\nDisplaying your hand for this round:");
    printHand(activeHand);

    // Dealing another sorted hand
    printf("\n\nPlaying a new round:");
    activeHand = dealShuffledHand(&myDeck);
    printf("\nDisplaying the Deck for this round:");
    printDeck(myDeck);
    printf("\nDisplaying your hand for this round:");
    printHand(activeHand);

    // End program
    printf("\n\n");
    return 0;
}