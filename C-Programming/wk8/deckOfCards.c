#include <stdio.h>
#include <stdbool.h>
#define string char*

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

typedef struct deckArr {
    card cards[52];
    suitsInDeck activeCards;
} deckArr;

typedef struct suitsInDeck {
    int clubCount;
    int diamondCount;
    int spadeCount;
    int heartCount;
    int total;
} suitsInDeck;

suitsInDeck suitCount = {
    .clubCount = 12,
    .diamondCount = 12,
    .spadeCount = 12,
    .heartCount = 12,
    .total = 52
};

typedef struct splitDeck {
    card left[26];
    card right[26];
} splitDeck;


/**
 * Deck shuffling
 * 
 * Swapping deck chunks is about, taking that bit in the middle
 *  and putting near top/bottom. That you do a few times
 * 
*/
splitDeck deckSplit(deckArr *deck);
deckArr interleaveSplits(splitDeck *splits);
void swapDeckChunks(deckArr *deck, int amount, bool topOrBottom);


/**
 * Deck handling
 * 
*/
card getCard(deckArr *deck);
void decrementDeckSuit(deckArr *deck, suit);
deckArr resetDeck();