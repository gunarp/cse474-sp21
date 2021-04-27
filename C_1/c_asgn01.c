/*c_asgn01.c
 *
 *      EE474 introductory C programming assignment #1
 *      Spring 2021
 *
 *     Student Name: Peter Gunarso 1821083
 *
 */

/*  Objectives:
       Gain experience and proficiency with C programming.


Format of assignment:
  1)  make a backup copy of this file
  2)  enter your name into the space above
  3)  Read through the comments below and
edit code into this file to solve the problems.
  4)  check your results against posted solution

Notes:   You are not required to use #defines for all constants
in this assignment but please do so for problem 3.

Printing:   Use the following functions to print unless
directed not to do so:

  print_int(int x)                prints out an integer
  print_usi(unsigned int x)       prints out an unsigned int
  print_newl()                    prints a "newline" character
  print_str(char *x)                 prints a string (pointed to by x)
  print_dble(double)              prints out a double precision floating point number

These functions are at the bottom of this file.  Feel free to study
them to see how they work.
*/
/*  #include some system library function prototypes */
      //  we will use printf()
#include <stdio.h>
//  also get math function
#include <math.h>
#include <string.h>    // for strlen
#include <malloc.h>    // for malloc(!)
#include <stdlib.h>    // for random()


#define LINUX            1
//#define VISUALC          1

#define CARD_ERROR       -1
// data types
typedef int           shuffle;
//typedef unsigned char hand[7];


/*  function prototypes for simplified printing functions */
void print_int(int);
void print_usi(unsigned int);
void print_newl();
void print_str(char*);
void print_dble(double);



// solution functions


/**********************************************************************
                 All variable declarations
**********************************************************************/

int i,j,k;      // these make good loop iterators.
int card, suit;

//  Random number seed.
//      try  43227 (player 1 has 4 10s)
int seed = 43227;

// Part 1.2
int t1, t2;
double rms;


// Part 2.0

shuffle cards[52][2];

//  Part 2.2

unsigned char testhand[7]={0};


//Part 3.0

char *card_names[]={"Ace", "2", "3", "4","5","6","7","8","9","10", "Jack", "Queen", "King"};
char *suit_names[]={"Hearts", "Diamonds", "Clubs", "Spades"};

// Part 3.1

char textline[80];      // array that can hold a string up to 79 characters

// Part 3.2

unsigned char player1_hand[7];
unsigned char player2_hand[7];
shuffle  game_deck[52][2];
int dealer_deck_count=0;

// Part 3.3

int cardsheld[13][3];              // number of cards held of each type in 3 hands.

/***********************************************************************
                      Function prototypes
**************************************************************************/
char* length_pad(char*, int);     // prob 1.4
int randN(int);                   // 2.1
void fill(shuffle[52][2]);             // 2.1
int convert(int card, int suit, int handcard, unsigned char hand[7]);  // 2.2
void test(int, unsigned char[]);            // 2.2
int gcard(unsigned char card);   // 2.2
int gsuit(unsigned char card);   // 2.2
void names(int n, int j, char *answer);          // 2.3
void deal(int M, unsigned char hand[7], shuffle deck[52][2]);    // 3.2
void check_hand(unsigned char hand[7], int n, char * handname);
void print_combinations(int raw_counts[13], int card_counter[13][4], int r);
void print_combos(int input[], int data[], int start, int end, int index, int r, int card);
int n_choose_r(int n, int r);


/**********************************************************************
                          main()
***********************************************************************/
int main() 
{
/************************************************************************
                    Start YOUR code here                                     */

/************************************************************************
 *
 * PROBLEM 1,  C-Basics
 *
 */

// initialize random numbers.
//  change the seed for testing.  Use this value to compare results with
#ifdef VISUALC
srand(seed);
#endif
#ifdef LINUX
srandom(seed);
#endif

print_str("Random seed: "); print_int(seed); print_newl();


// 1.1  Write a code to print out the 10 integers between 1 and 10 on separate lines:
print_str("Problem 1.1: \n");

//  1.1 code here ... 
for (i = 1; i <= 10; i++) {
  print_int(i);
  print_newl();
}

// 1.2 Modify 1.1 to print (after the 10 ints):
//   a) sum of the ints.  b) sum of the ints squared.   

print_str("Problem 1.2: \n");

//  1.2 code here ...
int t1 = 0;
int t2 = 0;
for (i = 1; i <= 10; i++) {
  t1 += i;
  t2 += i * i;
}
print_int(t1);
print_newl();
print_int(t2);
print_newl();

//*********
//  1.3  Modify 1.2 so that all quanitities in 1.2 are labeled "sum:", "sum of squares: ",
//     "root-mean-square: " and they all appear on separate lines.


print_str("Problem 1.3:\n");

// you code for 1.3 here ...
char * l1 = "sum: ";
char * l2 = "sum of squares: ";
print_str(l1) ; print_int(t1) ; print_newl();
print_str(l2) ; print_int(t2) ; print_newl();



//  1.4  Write a fcn, char* length_pad(char *st, int n), which takes a string and adds
//       the right amount of spaces so that it's length is n.  It should return a pointer
//       the new string.  If the length of st is > n, return NULL.  Use malloc() to get
//       the new string pointer.


//  Add your length_pad function below main. 

//  1.5 Modify 1.3 to use length_pad() so that the numbers are all starting in col 21
//      (i.e. all labels have length 20).

print_str("Problem 1.5: \n");


// test code
print_str(length_pad(l1,20)) ; print_int(t1) ; print_newl();
print_str(length_pad(l2,20)) ; print_int(t2) ; print_newl(); 





/************************************************************************
 * 2.0   Card games
 *
 *  A 'shuffle' is an array of 52 pairs of integers.   The first of the pair is the card type
(0-13 representing ace, 2, 3, .... King) and the second representing the suit (hearts, diamonds, clubs, spades).   Thus a pair of numbers (1-13)(1-4) describes a unique card in the deck. 
 */


// 2.1 Write a function to fill a shuffle with 52 random integer pairs, BUT,
//     as with your playing cards, there must be exactly one of each pair in the
//     shuffle.
//    Use your function to print out all the "cards" of the shuffle, 7 cards per line.

print_str("Problem 2.1: ");    ; print_newl();
 

fill(cards);


// print out the random cards.

// print out this pair
for (i = 0; i < 52; i++) {
  int rank = cards[i][0];
  int suite = cards[i][1];
  printf("[ %d\t %d ]\t", rank, suite);
  if ((i + 1) % 7 == 0) {
    print_newl();
  }
}
print_newl();




// 2.2    A 'hand' is an array of seven unsigned chars.  Each char represents one card.  We use a four bit field in the char for each of the two numbers above:  the four most significant bits [7...4] represent the card number (1-13) and the lower four [3...0] represent the suit. 


//        Write functions to:  a)  convert two integers (from  a shuffle for example) into a char as above. 
//                             b) test if a char equals an integer pair
//                             c)  get the integer suit from a char
//                             d)  get the integer card from a char

//        Both functions a and b must return CARD_ERROR if they get invalid input (such as suit > 4).

//        Write code which verifys these functions work properly and prints results.
//

//

print_str("Problem 2.2: ");     ; print_newl();

//  your code for convert()  below main.
 


// test code
// to test, lets fill a hand up with some cards:
    card = 5;
    suit = 2;
    if(convert(card,suit,0,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();

    card = 15;
    suit = 2;
    if(convert(card,suit,1,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();
 
    card = 12;
    suit = 1;
    if(convert(card,suit,2,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();

    card = 6;
    suit = 3;
    if(convert(card,suit,3,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();

    card = -1;
    suit = 7;
    if(convert(card,suit,4,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();

    card = 10;
    suit = 4;
    if(convert(card,suit,5,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();

    card = 3;
    suit = 3;
    if(convert(card,suit,6,testhand) == CARD_ERROR) {print_str("Error Converting "); }
    print_int(card); print_int(suit); print_newl();
 
print_str("\nTest results:  ...\n");
 

for(i=0;i<7;i++) {    
   card = gcard(testhand[i]);
   suit = gsuit(testhand[i]);
    print_int(i); print_int(card);print_int(suit) ; print_newl();

  
   }
print_newl();





//***************************************************************************
//  3.0  Pointers and array manipulation

// 3.1  Create the array
//     char * card_names={"Ace", "2", "3", ...  ,"10", "Jack", "Queen", "King"};
//     and a similar array for the suits in the order hearts, diamonds, clubs, spades.
//
//     Write a function names(int card, int suit, char answer[]) which places a string of the name and suit of a card in the array "answer[]".
//     For example:    name(11) => "Queen of Hearts", name(20) => "8 of Diamonds".
//     hint:  look up and use the pre-defined function strcpy(char *source, char *dest);
//


print_str("Problem 3.1: ");     ; print_newl();

//  Put your code for the names function below main.


// test code
names(11, 4, textline);
  print_str(textline); print_newl();
names(3, 2, textline);
  print_str(textline); print_newl();



// 3.2  Write a function to deal a hand of M (0<M<8) cards from a shuffle.  Keep track of
//      which cards have been dealt.  Test this by dealing two hands of 7 cards from a shuffled
//      deck.  Use 2.2 and 3.1 to print out the dealt cards and the remaining
//      deck.


print_str("Problem 3.2: ");     ; print_newl();

/*  This code will be used to TEST your "deal()" function. Do not change it.  */
// test code
dealer_deck_count=0;
fill(game_deck);
deal(7, player1_hand, game_deck);
deal(7, player2_hand, game_deck);

print_str("Player 1: \n");
for(i=0;i<7;i++) { 
        card = gcard(player1_hand[i]);
        suit = gsuit(player1_hand[i]);
        names(card, suit, textline);
        print_str(textline); print_newl(); 
   }
print_str("Player 2: \n");
for(i=0;i<7;i++) { 
        card = gcard(player2_hand[i]);
        suit = gsuit(player2_hand[i]);
        names(card, suit, textline);
        print_str(textline); print_newl(); 
   }

print_str("Remainder of Deck: \n");
for(i=dealer_deck_count;i<52;i++) {
        card = game_deck[i][0];
        suit = game_deck[i][1]; 
        names(card, suit, textline);
        print_int(i);
        print_str(textline); print_newl();
        }


// 3.3 

//  The next step is evaluating the strength of the hands!
//   Deal three hands from a deck.
//  Write a function which finds out if the hands contains any pairs,
//   three-of-a-kinds, or 4 of a kinds, and lists them.

print_str("\nProblem 3.3: \n");
 
unsigned char h1[7], h2[7], h3[7];


// Do not modifiy this test code
fill(game_deck);  // shuffle a new deck
dealer_deck_count = 0;

deal(7,h1,game_deck);
deal(7,h2,game_deck);
deal(7,h3,game_deck);


print_str("Dealt hands:\n");


print_str("Player 1: \n");
for(i=0;i<7;i++) { 
        card = gcard(h1[i]);
        suit = gsuit(h1[i]); 
        names(card, suit, textline);
        print_str(textline); print_newl(); 
   } 

print_str("Player 2: \n");
for(i=0;i<7;i++) { 
        card = gcard(h2[i]);
        suit = gsuit(h2[i]); 
        names(card, suit, textline);
        print_str(textline); print_newl(); 
   } 

print_str("Player 3: \n");
for(i=0;i<7;i++) { 
        card = gcard(h3[i]);
        suit = gsuit(h3[i]); 
        names(card, suit, textline);
        print_str(textline); print_newl(); 
   } 
// end of test code

// card rank -> suit, 1 in corresponding column if that suit is present
check_hand(h1, 7, "hand 1");
check_hand(h2, 7, "hand 2");
check_hand(h3, 7, "hand 3");


#ifdef VISUALC
getchar();
return 0;
#endif
// end of main
}



// Part 1.4
//  your function length_pad() here...

char* length_pad(char *st, int n) {
    int len = strlen(st);
    int curr = 0;
    char * ret = malloc(n);
    
    // Copy everything we can from the original string
    while (curr < len && curr < n) {
      ret[curr] = st[curr];
      curr++;
    }

    // Add in spaces at the end if neccessary
    if (len < n) {
      while (curr < n) {
        ret[curr] = ' ';
        curr++;
      }
    }

    return ret;
}


//Part 2.1
// your function fill() here ...
void fill(shuffle deck[52][2]) {
  // populate an 52-long array with numbers,
  // each representing a unique card
  int list[52];
  for (int i = 0; i < 52; i++) {
    list[i] = i;
  }

  // swap each member of this list with another random
  // member of the list
  int dest;
  int temp;
  for (int i = 0; i < 52; i++) {
    dest = randN(52) - 1; // need something zero indexed
    temp = list[dest];
    list[dest] = list[i];
    list[i] = temp;
  }

  // now we have a shuffled deck of cards, 
  // need to interpret it in the way the deck structure expects
  int rank;
  int suite;
  for (int i = 0; i < 52; i++) {
    rank = (list[i] % 13) + 1;
    suite = (list[i] / 13) + 1;
    deck[i][0] = rank;
    deck[i][1] = suite;
  }
}


// Part 2.2
//  your code for convert() here
 
int convert(int card, int suit, int handcard, unsigned char hand[7])
    {
      if (handcard < 0 || handcard >= 7 ||
          card < 1     || card > 13 ||
          suit < 1     || suit > 4) {
        return CARD_ERROR;
      }
      unsigned char hand_mask = 0x00;
      unsigned char temp_mask = 0x08;
      while (temp_mask > 0) {
        if ((temp_mask & card) != 0x00) {
          hand_mask = hand_mask | temp_mask;
        }
        temp_mask = temp_mask >> 1;
      }
      hand_mask = hand_mask << 4;

      temp_mask = 0x04;
      while (temp_mask > 0) {
        if ((temp_mask & suit) != 0) {
          hand_mask = hand_mask | temp_mask;
        }
        temp_mask = temp_mask >> 1;
      }

      hand[handcard] = hand_mask;
      return 1;
    }

// your code for gsuit and gcard here
 
int gcard(unsigned char card)
  {
    unsigned char card_mask = 0xF0 & card;
    card_mask = card_mask >> 4;
    card_mask = card_mask & 0x0F;
    int ret = 0;
    int curr = 1;
    while (card_mask > 0) {
      ret += curr * (card_mask & 0b1);
      curr *= 2;
      card_mask = card_mask >> 1;
    }

    if (ret < 1 || ret > 13) return CARD_ERROR;

    return ret;
  }

int gsuit(unsigned char card)
  {
    unsigned char suit_mask = 0x0F & card;
    int ret = 0;
    int curr = 1;
    while (suit_mask > 0) {
      ret += curr * (suit_mask & 0b1);
      curr *= 2;
      suit_mask = suit_mask >> 1;
    }

    if (ret < 1 || ret > 4) return CARD_ERROR;

    return ret;
  } 



//Part 3.1:  
//  Your code for names() here

void names(int card, int suit, char answer[])
 {
    char * rank_name = card_names[card - 1];
    char * suit_name = suit_names[suit - 1];

    int curr = 0;
    for (int i = 0; i < strlen(rank_name); i++) {
      answer[curr] = rank_name[i];
      curr++;
    }

    char * transition = " of ";
    for (int i = 0; i < strlen(transition); i++) {
      answer[curr] = transition[i];
      curr++;
    }

    for (int i = 0; i < strlen(suit_name); i++) {
      answer[curr] = suit_name[i];
      curr++;
    }
    // add in the nul terminator so we don't need to worry
    // about the rest of the string
    answer[curr] = '\0';
 }


// Part 3.2

void deal(int M, unsigned char hand[7], shuffle deck[52][2])
  {
    // don't do anything if the deck is empty
    int allEmpty = 1;
    for (int i = 0; i < 52; i++) {
      if (deck[i][0] != 0) {
        allEmpty = 0;
        break;
      }
    }
    if (allEmpty) return;

    for (int i = 0; i < M; i++) {
      convert(deck[dealer_deck_count][0], deck[dealer_deck_count][1], i, hand);
      dealer_deck_count++;
    }
  }


// Part 3.3
void check_hand(unsigned char hand[7], int n, char * handname) {
  int card_counter[13][4] = {0};
  int raw_counts[13] = {0};
  // count instances of each card in the hand
  int card, suit;
  for (int i = 0; i < n; i++) {
    card = gcard(hand[i]);
    suit = gsuit(hand[i]);
    card_counter[card-1][suit - 1] = 1;
    raw_counts[card-1] += 1;
  }

  // go back over instances of each card
  int nPairs = 0, nTripl = 0, nQuads = 0;
  for (int i = 0; i < 13; i++) {
    nPairs += n_choose_r(raw_counts[i], 2);
    nTripl += n_choose_r(raw_counts[i], 3);
    nQuads += n_choose_r(raw_counts[i], 4);
  }
  
  if (nPairs == 0 && nTripl == 0 && nQuads == 0) {
    printf("%s has nothing\n", handname);
    return;
  }

  if (nPairs != 0) {
    printf("%s has %d pair(s):\n", handname, nPairs);
    print_combinations(raw_counts, card_counter, 2);
  }
  if (nTripl != 0) {
    printf("%s has %d three-of-a-kind(s):\n", handname, nTripl);
    print_combinations(raw_counts, card_counter, 3);
  }
  if (nQuads != 0) {
    printf("%s has %d 4 of a kind(s):\n", handname, nQuads);
    print_combinations(raw_counts, card_counter, 4);
  }
}

void print_combinations(int raw_counts[13], int card_counter[13][4], int r) {
  for (int i = 0; i < 13; i++) {
    if (raw_counts[i] < r) continue;
    
    // Get a list of the available suits we can make combinations of
    int suits[raw_counts[i]];
    int curr = 0;
    for (int j = 0; j < 4; j++) {
      if (card_counter[i][j] == 1) {
        suits[curr] = j;
        curr++;
      }
    }
  
    // print out all possible combinations
    int data[raw_counts[i]];
    print_combos(suits, data, 0, raw_counts[i]-1, 0, r, i);
  }
}

void print_combos(int input[], int data[], int start, int end, int index, int r, int card) {
  if (index == r) {
    printf("\t");
    // base case
    for (int i = 0; i < r; i++) {
      char ans[80] = {0};
      names(card + 1, data[i] + 1, ans);
      printf("%s, ", ans);
    }
    printf("\n");
  }

  for (int i = start; i <= end && end-i+1 >= r-index; i++) {
    data[index] = input[i];
    print_combos(input, data, i+1, end, index+1, r, card);
  }

}

int n_choose_r(int n, int r) {
  if (n < r) return 0;
  if (n == r) return 1;

  int numer = 1;
  for (int i = 2; i <= n; i++) {
    numer *= i;
  }

  int d1 = 1;
  for (int i = 2; i <= r; i++) {
    d1 *= i;
  }

  int d2 = 1;
  for (int i = 2; i <= (n - r); i++) {
    d2 *= i;
  }

  return numer / (d1 * d2);
}

/**************************************************************************
  simplified I/O and other functions for this assignment
***************************************************************************/
void print_int(int x)
  {
  printf(" %d ",x);
  }
void print_usi(unsigned int x)
  {
  printf(" %d",x);
  }
void print_dble(double x)
  {
  printf(" %f",x);
  }
void print_newl()
  {
  printf("\n");
  }
void print_str(char *x)
  {
  printf("%s",x);
  }

int randN(int n)   //  return a random integer between 1 and n
  {
  double x;
  x = 1.0 + (double) n * rand() / RAND_MAX;
  return((int)x);
  }
