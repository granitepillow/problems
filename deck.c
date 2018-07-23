#include "string.h"
#include "stdio.h"

typedef enum {
    CLUBS      = 0,
    DIAMONDS   = 1,
    HEARTS     = 2,
    SPADES     = 3,
} suit_e;

typedef enum {
    TWO    = 0,
    THREE  = 1,
    FOUR   = 2,
    FIVE   = 3,
    SIX    = 4,
    SEVEN  = 5,
    EIGHT  = 6,
    NINE   = 7,
    TEN    = 8,
    JACK   = 9,
    QUEEN  = 10,
    KING   = 11,
    ACE    = 12,
} value_e;

#define NUM_VALUES 13
#define NUM_SUITS  4

const char* suit_strings[NUM_SUITS] = {
    "CLUBS",
    "DIAMONDS",
    "HEARTS",
    "SPADES"
};

const char* value_strings[NUM_VALUES] = {
    "TWO",
    "THREE",
    "FOUR",
    "FIVE",
    "SIX",
    "SEVEN",
    "EIGHT",
    "NINE",
    "TEN",
    "JACK",
    "QUEEN",
    "KING",
    "ACE"
};

#define DECK_SIZE 52

#define NUM_PLAYERS     4
#define CARDS_PER_HAND  5

//This function translates a suit and value into a single integer encoding of a card
//eg HEARTS, THREE becomes 102
int get_card_int_value(suit_e suit, value_e value) {
    return value * 100 + suit;
}

suit_e get_card_suit(int card_int) {
    return card_int % 100;
}

value_e get_card_value(int card_int) {
    return card_int / 100;
}

void initialize_deck(int* deck, int deck_size) {
    suit_e i;
    value_e j;
    int deck_index = 0;
    for(i = CLUBS; i < NUM_SUITS; i++) {
        for(j = TWO; j < NUM_VALUES; j++) {
            if(deck_index >= deck_size) {
                printf("GAH! our deck isn't big enough to hold every suit and value!!!\n");
                return;
            }
            deck[deck_index] = get_card_int_value(i, j);
            deck_index++;
        }
    }
}

void print_card(int card_int) {
    suit_e suit = get_card_suit(card_int);
    value_e value = get_card_value(card_int);

    if(value >= NUM_VALUES || suit >= NUM_SUITS) {
        //invalid card value - return silently
        return;
    }
    printf("%s\tof %s\n", value_strings[value], suit_strings[suit]);
}

void print_deck(int* deck, int deck_size) {
    int i;
    for(i=0; i < deck_size; i++) {
        print_card(deck[i]);
    }
}

void shuffle_deck(int* deck, int deck_size) {
    //TODO

    //See https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
    printf("\n*** SHUFFLING NOT IMPLEMENTED\n");
}

int deal_hands(int* deck, int deck_size, int** hands, int num_players, int cards_per_hand) {
    //TODO
    printf("\n*** DEALING NOT IMPLEMENTED\n");

    //Example....
    /*
    hands[0][0] = deck[0]; //player 1's first card is the first card of the deck
    hands[1][0] = deck[1]; //player 2's first card is the second card of the deck
    hands[2][0] = deck[2]; //etc
    hands[3][0] = deck[3];

    hands[0][1] = deck[4];
    hands[1][1] = deck[5];
    ... etc
    */

    //return number of cards remaining in deck???
    return deck_size;
}

int find_best_poker_hand(int** hands, int num_players, int cards_per_hand) {
    printf("\n*** NOT IMPLEMENTED\n");

    if(cards_per_hand != 5) {
        printf("Invalid poker hand size");
        return -1;
    }

    //TODO

    //return the player that has the best hand
    return 0;
}

int main(void) {
    int main_hands[NUM_PLAYERS][CARDS_PER_HAND];
    int main_deck[DECK_SIZE];

    memset(main_hands, 0xFF, sizeof(main_hands));
    memset(main_deck, 0xFF, sizeof(main_deck));

    initialize_deck(main_deck, DECK_SIZE);
    printf("\n***Deck after initialization: \n");
    print_deck(main_deck, DECK_SIZE);


    shuffle_deck(main_deck, DECK_SIZE);
    printf("\n***Deck after shuffling: \n");
    print_deck(main_deck, DECK_SIZE);

    int deck_remaining = deal_hands(main_deck, DECK_SIZE, (int**)main_hands, NUM_PLAYERS, CARDS_PER_HAND);
    printf("\n***Remaining deck after dealing: \n");
    print_deck(&main_deck[DECK_SIZE - deck_remaining], deck_remaining);

    printf("\n***Player2's hand:\n");
    //for the purpose of printing, a single hand is like a small "deck" or more aptly, a set of cards
    print_deck((int*)&main_hands[1][0], CARDS_PER_HAND);

    return 0;
}
