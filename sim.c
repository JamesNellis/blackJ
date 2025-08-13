#define TRUE 1
#define FALSE 0

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


typedef struct{
	int hand[10];
	int size;
	char hidden;
	int eval;
	char hasAce;
} Hand;

typedef struct{
	char deck[52];
	int deckS;

	Hand hands[3];
	int userHands;
	int played;
} Table;


void drawCard(Table *table, Hand *hand);

void initHandNegTwo(int hand[], int len);

void initTable(Table *table);

void shuffleDeck(Table *table);

void evalHand(Table *table, Hand *hand, int print);

int makeChoice(Table *table, Hand *hand);

//temp:

void showHand(Hand *hand);

void showTable(Table *table);


int sleeptime = 0;
int main(){
	srand(time(NULL));
	Table table;
	initTable(&table);


	for (int j = 0; j < 2; j++){
		for (int i = 0; i < 2; i++){
			drawCard(&table, &table.hands[i]);
		}
	}
	


	showTable(&table);

	table.hands[0].hidden = FALSE;
	showTable(&table);



	// while (table.hands[1].eval
	// 	makeChoice(&table);

	while ((table.hands[0].eval < 17) || (table.hands[0].eval == 17 && table.hands[0].hasAce)){
		drawCard(&table, &table.hands[0]); // evals when draw
		showTable(&table);
	}

	for (;makeChoice(&table, &table.hands[1]););

	return 0;
}




int makeChoice(Table *table, Hand *hand){
	char choice[1];
	int doublable = (hand->size == 2);
	int splitable = (doublable) && (hand->hand[0] == hand->hand[1]) && (table->userHands = 1);
	printf("(H)it, (S)tand%s%s?: ", ((doublable) ? ", (D)ouble" : ""), (splitable) ? ", Split (2)" : "");
    fflush(stdout);
    
    scanf("%c", choice);

    while (1){

    	// 1: go again 2: 
	    if (choice[0] == 'h'){
	    	drawCard(table, hand);
	    	showTable(table);
	    	return 1;
	    }
	    else if (choice[0] == 's'){
	    	return 0;
	    }
	    else if (choice[0] == 'd' && doublable){
	    	drawCard(table, hand);
	    	showTable(table);
	    	// hand->bet *= 2;
	    	return 0;
	    }
	    else if (choice[0] == '2' && splitable) {
	    	table->userHands = 2;
	    	table->hands[2].hand[0] = table->hands[0].hand[1];
	    	hand->size--;
	    	table->hands[2].size++;
	    	// carry over bet
	    	return 1;
	    }
	    printf("Poor input.\n");
	    printf("(H)it, (S)tand%s%s?: ", ((doublable) ? ", (D)ouble" : ""), (splitable) ? ", Split (2)" : "");
	    fflush(stdout);
	    scanf("%c", choice);

	 }

}



void initHandNegTwo(int hand[], int len){
	for (int i 
		= 0; i < len; i++){
		hand[i] = -2;
	}
}


void initTable(Table *table){

	for (int i = 0; i < 3; i++){
		table->hands[i].hidden = FALSE;
		initHandNegTwo(table->hands[i].hand, 10);
		table->hands[i].size = 0;
		table->hands[i].hasAce = 0;
	}


	table->hands[0].hidden = TRUE;
	table->userHands = 1;


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

void drawCard(Table *table, Hand *hand){
	hand->hand[hand->size] = table->deck[table->deckS-1];
	hand->size++;
	table->deckS--;
	evalHand(table, hand, 0);
}

void evalHand(Table *table, Hand *hand, int print) {


	hand->eval = -1;
	int sum = 0;
	int ace = FALSE;

	for (int i = (hand->hidden? 1 : 0); i < hand->size; i++){

		// add card value
		if (hand->hand[i] != -1) {
			sum += (hand->hand[i] == 0 ? 10 : hand->hand[i]);
		
				// if ace not in hand, check if it should be
				if (!ace){
					ace = (hand->hand[i] == 1? TRUE : FALSE);
				}	
			}
	}
	if (ace) {
		hand->hasAce = 1;
	}
	if (sum <= 21 && ace && sum < 12){
		sum += 10;
	}

	hand->eval = sum;
	if (print){
		printf("EVAL: %d\n", sum);

	}

}





//temp for tetsing:

void showHand(Hand *hand){
	printf("%s", hand->hidden? "X, ": "");
	for (int i = (hand->hidden? 1: 0); i < hand->size; i++){
		printf("%d, ", hand->hand[i]);
	}
	printf("\n");
}

void showTable(Table *table){
	system("clear");
	printf("Table's Hands: \n");
	for (int i = 0; i < (table->userHands + 1); i++){
		printf("Hand %d: \n", i);
		showHand(&(table->hands[i]));
		evalHand(table, &(table->hands[i]), 1);
	}
	printf("\n");
	usleep(sleeptime);
}