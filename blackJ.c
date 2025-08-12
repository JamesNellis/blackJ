#define TRUE 1
#define FALSE 0

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
	char rank[3];
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
} Player;

typedef struct{
	Player players[5];
	int playercount;
	Deck deck;
} Table;




void evalTable(Table *table){
	for (int i = 0; i < table->playercount; i++){
		//only eval live players
		int sum = 0;
		int ace = FALSE;
		char rank;

		if (!(table->players[i].eval[1] == -1)){
			for (int j = 0; j < table->players[i].handSize; j++){
			

				if (!(table->players[i].hand[j].hidden)){

					rank = table->players[i].hand[j].rank[0];

					// 2-9 all sequential in ascii
					if ((2 <= rank - '0') && (rank - '0' <= 10)){

						sum += (rank - '0');
					}
					// ace
					else if (rank == 'A'){
						sum += 1;
						ace = TRUE;
					}
					// all else
					else{
						sum += 10;
					}

				}


			}
		}

		table->players[i].eval[0] = sum;
		if (ace){
			table->players[i].eval[1] = sum + 10;
		//bust: -1, n
		if (table->players[i].eval[0] > 21 || table->players[i].eval[1] > 21) {
			table->players[i].eval[1] = MAX(table->players[i].eval[1], table->players[i].eval[0]);
			table->players[i].eval[0] = -1;
			
		}
		// blackjack: 21, 0
		else if (table->players[i].eval[0] == 21 || table->players[i].eval[1] == 21){
			table->players[i].eval[0] = 21;
			table->players[i].eval[1] = 0;
		}

		}
		

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

void showHand(Player *player, int allinfo){
	printf("%s's Hand: \n", player->name);
	for (int n = 0; n < player->handSize; n++){
		showCard(&(player->hand[n]));
	}
	if (allinfo){
		if (player->eval[1]){
			printf(" - %d OR %d", player->eval[0], player->eval[1]);
		}
		else {
		printf(" - %d", player->eval[0]);
		}
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

		showHand(&(table->players[i]), TRUE);
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

Table makeTable(char names[][20], int players){

    


    Table table;
    makeDeck(&table.deck);
    table.playercount = players + 1;

    for (int i = 0; i< players + 1; i++){
    	strcpy(table.players[i].name, names[i]);
    	table.players[i].handSize = 0;
    	table.players[i].eval[0] = 0;
    	table.players[i].eval[1] = 0;
    }
    return (table);
}

Table startGame(){
	// int players;
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

    
    Table table = makeTable(names, players);
    return(table);
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

	evalTable(table);

}




int main(){
	srand(time(NULL));
	Table table = startGame();
    //game loop from here, so all in a while True loop
    dealFirst(&table);
    showTable(&table);

    //evalWinners()
    //letDraw()
    //evalWinners()

    return 0;
}
