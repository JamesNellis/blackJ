#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
	char rank[6];
	char suit[2];
	int hidden;
} Card;

typedef struct{
	int size;
	Card cards[52];
} Deck;

typedef struct{
	char name[10];
	Card hand[10];
	int handSize;
} Player;

typedef struct{
	Player players[5];
	int togo;
	int playercount;
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


void showCard(Card *card){
	if (!card->hidden){
		printf("%s%s ", card->rank, card->suit);
	}
	else{
		printf("XX ");
	}
}

void assignCard(Deck *deck, char crank[], char csuit[]){
	//deck counter only goes up, cannot cope with anything more than making a deck
	strcpy(deck->cards[deck->size].rank, crank);
	strcpy(deck->cards[deck->size].suit, csuit);
	deck->cards[deck->size].hidden = FALSE;
	deck->size++;
}

void showDeck(Deck *deck){
	for (int i = 0; i < deck->size; i++){
		showCard(&(deck->cards[i]));
	}
	printf("\n");
}

void makeDeck(Deck *deck){
	deck->size = 0;
	char suits[4][2] = {"S", "C", "D", "H"};
	char ranks[13][6] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 13; j++) {
			assignCard(deck, ranks[j], suits[i]);
		}
	}
	shuffleDeck(deck);	
}

void showHand(Player *player){
	printf("%s's Hand: \n", player->name);
	for (int n = 0; n < player->handSize; n++){
		showCard(&(player->hand[n]));
	}
	printf("\n");
}

void drawCard(Player *player, Deck *deck, int cards, int hidden){
	for (int n = 0; n < cards; n++){
		player->hand[player->handSize] = deck->cards[(deck->size) - 1];
		player->handSize++;
		deck->size--;
	}
}


//void makePlayer(

int main(){
	srand(time(NULL));
	Deck deck;
	makeDeck(&deck);
	Player dealer;
	strcpy(dealer.name, "Dealer");
	dealer.handSize = 0;
	drawCard(&dealer, &deck, 2, 0);
	showHand(&dealer);
	printf("%d", deck.size);
	return 0;
}
