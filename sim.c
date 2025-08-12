#define TRUE 1
#define FALSE 0

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



typedef struct{
	int hand[10];
	int size;
	int hidden;
	int money;
	int bet;
	int eval[2];
} Hand;

typedef struct{
	char deck[52];
	int deckS;

	Hand hands[3];
	Hand publicHands[3];
	int userHands;
	int played;
} Table;


void drawCard(Table *table, int i);

void initHandNegTwo(int hand[], int len);

void updatePublicHands(Table *table);

void initTable(Table *table);

void shuffleDeck(Table *table);

void evalHand(Table *table, Hand *hand, int print);

void promptChoice(Table *table);

//temp:

void showHand(Hand *hand);

void showTable(Table *table);

int main(){
	srand(time(NULL));
	Table table;
	initTable(&table);


	for (int j = 0; j < 2; j++){
		for (int i = 0; i < 2; i++){
			drawCard(&table, i);
		}
	}
	showTable(&table);

	promptChoice(&table);





	return 0;
}





void initHandNegTwo(int hand[], int len){
	for (int i = 0; i < len; i++){
		hand[i] = -2;
	}
}

void updatePublicHands(Table *table) {
	for (int j = 0; j < 2; j++){
		for (int i = 0; i < table->hands[j].size; i++){
			table->publicHands[j].hand[i] = MIN(table->hands[j].hand[i], (table->hands[j].hidden && i == 0) ? -1 : 10);
		}
		table->publicHands[j].size = table->hands[j].size;
	}

}

void initTable(Table *table){

	table->hands[0].hidden = TRUE;
	initHandNegTwo(table->hands[0].hand, 10);
	table->hands[0].size = 0;

	table->hands[1].hidden = FALSE;
	initHandNegTwo(table->hands[1].hand, 10);
	table->hands[1].size = 0;
	table->userHands = 1;

	for (int j = 0; j < 2; j++){
		for (int i = 0; i < table->hands[0].size; i++){
			table->publicHands[j].hand[i] = -2;
		}
	}

	shuffleDeck(table);
}

void shuffleDeck(Table *table){
	table->deckS = 52;

	for (int i = -12; i < 40; i++){
		table->deck[i+12] = MAX(0, (i / 4));
	}

	for (int i = 0; i < table->deckS; i++){
		int randi = rand() % (table->deckS - i) + i;
		int temp = table->deck[randi];
		table->deck[randi] = table->deck[i];
		table->deck[i] = temp;
	}
}

void drawCard(Table *table, int i){
	table->hands[i].hand[table->hands[i].size] = table->deck[table->deckS-1];
	table->hands[i].size++;
	table->deckS--;
	updatePublicHands(table);
	evalHand(table, &table->publicHands[i], 0);
}

void evalHand(Table *table, Hand *hand, int print){

	// no ace, no bust, no bj: n, -1
	// ace: n, n+10
	// bj: 21, -1
	// bust: -2, max([0:1])

	hand->eval[1] = -1;
	int sum = 0;
	int ace = FALSE;

	for (int i = 0; i < hand->size; i++){

		// add card value
		if (hand->hand[i] != -1) {
			sum += (hand->hand[i] == 0 ? 10 : hand->hand[i]);
		
				// if ace not in hand, check if it should be
				if (!ace){
					ace = (hand->hand[i] == 1? TRUE : FALSE);
				}	}
	}
	hand->eval[0] = sum;
	if (ace){
		hand->eval[1] = hand->eval[0] + 10;
	}

	if (hand->eval[0] == 21 || hand->eval[1] == 21){
		hand->eval[0] = 21;
		hand->eval[1] = -1;
	}
	else if (hand->eval[0] > 21 && (hand->eval[1] > 21 || hand->eval[1] == -1)) {
		hand->eval[1] = MAX(hand->eval[0], hand->eval[1]);
		hand->eval[0] = -2;
	}
	if (print){
		if (hand->eval[1] == -1){
			printf("EVAL: %d\n", hand->eval[0]);
		}
		else {
			printf("EVAL: %d OR %d\n", hand->eval[0], hand->eval[1]);
		}
	}
}

//temp for tetsing:

void showHand(Hand *hand){
	for (int i = 0; i < hand->size; i++){
		printf("%d, ", hand->hand[i]);
	}
	printf("\n");
}

void showTable(Table *table){
	printf("Table's Hands: \n");
	for (int i = 0; i < (table->userHands + 1); i++){
		printf("Hand %d: \n", i);
		showHand(&(table->publicHands[i]));
		evalHand(table, &table->publicHands[i], 1);
	}
	printf("\n");
}



