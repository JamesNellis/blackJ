#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
	char rank[2];
	char suit[2];
	int hidden;
} Card;

typedef struct{
	int size;
	Card cards[52];
} Deck;

typedef struct{
	char name[20];
	Card hand[10];
	int handSize;
	int eval[2];
	int money;
} Player;

typedef struct{
	Player players[5];
	int togo;
	int playercount;
	Deck deck;
} Table;




void evalP(Player *player){
	int sum = 0;
	for (int i = 0; i < player->handSize; i++){

	}
	// add up values, if hand contains ACE, add another value which is +10, then once done, evaluate values, remove
	//any that are greater than 21, and set player->eval to either {#, #}, {bust,} or {#, bust}? thin
	// of some way to easily interpret that, and where it should be done
}

void showCard(Card *card){
	if (!card->hidden){
		printf("%s%s ", card->rank, card->suit);
	}
	else{
		printf("XX ");
	}
}

void showHand(Player *player){
	printf("%s's Hand: \n", player->name);
	for (int n = 0; n < player->handSize; n++){
		showCard(&(player->hand[n]));
	}
	printf("\n");
}

void showDeck(Deck *deck){
	for (int i = 0; i < deck->size; i++){
		showCard(&(deck->cards[i]));
	}
	printf("\n");
}

void showTable(Table *table){
	printf("------\n");
	printf("Table's Hands:\n");
	printf("------\n");
	for (int i = 0; i < table->playercount; i++){

		showHand(&(table->players[i]));
	}
	printf("------\n");
}


void shuffleDeck(Deck *deck){
	Card temp;
	for (int i = 0; i < deck->size - 1; i++){
		int randi = rand() % (deck->size - i) + i;
		temp = deck->cards[randi];
		deck->cards[randi] = deck->cards[i];
		deck->cards[i] = temp;
	}
}

void makeDeck(Deck *deck){
	deck->size = 0;
	char suits[4][2] = {"S", "C", "D", "H"};
	char ranks[13][6] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 13; j++) {
			strcpy(deck->cards[deck->size].rank, ranks[j]);
			strcpy(deck->cards[deck->size].suit, suits[i]);
			deck->cards[deck->size].hidden = FALSE;
			deck->size++;
		}
	}
	shuffleDeck(deck);	
}


void drawCard(Player *player, Deck *deck, int cards, int hidden){
	for (int n = 0; n < cards; n++){
		player->hand[player->handSize] = deck->cards[(deck->size) - 1];
		player->hand[player->handSize].hidden = hidden;
		player->handSize++;
		deck->size--;
	}
}

void dealFirst(Table *table){
	drawCard(&(table->players[0]), &(table->deck), 1, TRUE);
	drawCard(&(table->players[0]), &(table->deck), 1, FALSE);
	for (int i = 1; i < table->playercount; i++){
		drawCard(&(table->players[i]), &(table->deck), 2, FALSE);
	}
}

void makeTable(){
	//int players;
    // printf("How many players?: ");
    // scanf("%d", &players);
    // printf("Continuing with: %d player(s)...\n", players);
    // char names[players + 1][20];
    // strcpy(names[0], "Dealer");
    // while(!getchar());
    // for (int i = 0; i < players; i ++){
    // 	printf("Enter Player %d Name: ", i+1);
    // 	fgets(names[i+1], sizeof(names[i+1]), stdin);
    // 	names[i+1][strcspn(names[i + 1], "\n")] = 0;
    // }
    // printf("\n");

    int players = 3;
	char names[4][20] = {"Dealer", "James", "Andrew", "Catherine"};
    Table table;
    makeDeck(&table.deck);
    table.playercount = players + 1;
    table.togo = 0;

    for (int i = 0; i< players + 1; i++){
    	strcpy(table.players[i].name, names[i]);
    	table.players[i].handSize = 0;
    }

    dealFirst(&table);
    showTable(&table);

}

int main(){
	srand(time(NULL));
	makeTable();
	return 0;
}
