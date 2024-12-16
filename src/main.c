/**********************************
Name: Jordan D. 
Date: Feb 2, 2020
Purpose: The four letter pathfinder, this time better 
**********************************/
int numLetters = 4; 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "./api/includes/FLWG-API.h"
#include "./api/includes/FLWT-API.h"
#include "./api/includes/FLWC-API.h"

#include "./algs/includes/Minimax-2.h"
#include "./algs/includes/MinimaxTests.h"
#include "./algs/includes/BreadthFirstSearch.h"
#include "./algs/includes/MaxN.h"
#include "./algs/includes/MontyCarlosTreeSearch.h"

#include "./structs/includes/HashMap.h"
#include "./structs/includes/TreeSet.h"
#include "./structs/includes/WordSet.h"
#include "./structs/includes/IntLinkedList.h"
#include "./structs/includes/Queue.h"


#include "./flwp/includes/PathfinderGame.h"
#include "./flwp/includes/GameFunctions.h"

#include "./flwg/includes/FLWGGame.h"
#include "./flwc/includes/FLWC.h"
#include "./flwg/includes/MultiplayerFLWG.h"

void testAlpaBetaPruning(struct wordDataArray *IntToWord_HashMap); 
void runMultiplayerFLWG();
void PathfindBetweenTwoWords(char* start, char* end, struct DummyHeadNode*** WordToInt_HashMap, struct wordDataArray *IntToWord_HashMap, struct WordSet* wordSet);
void runFLWG();
void testMCTS();
void initializeStructures();
void fourletterwordgame_example(); 
void test_new_flwg(); 

void flwcChooseGoals_Example(); 

int main(){

	srand(time(0)); 
	int fd = open("docs/4.txt", O_RDONLY);
	struct DataStructures* dataStructures = initDataStructures(fd); 
	struct GameComponentsFLWC* flwcComponents = initFLWC(dataStructures);	
	printf("Get to a word with 'c' in it\n");
	printf("Do not touch any words with 'z' in it\n"); 
	printf("Start Word: %s\n", getStartWordFLWC(flwcComponents, dataStructures));
	while(isGameWonFLWC(flwcComponents) == 0){
		char userInput[256];
		if (fgets(userInput, sizeof(userInput), stdin) != NULL) {
			userInput[strcspn(userInput, "\n")] = '\0'; // Remove trailing newline
		    	userEntersWordFLWC(userInput, flwcComponents, dataStructures);
		}
		printf("Curr Word: %s\n", getStartWordFLWC(flwcComponents, dataStructures));
	}
	printf("Best  Solution:\n%s\n", getSolutionFLWC(flwcComponents));

	freeFLWC(flwcComponents); 
	
	close(fd); 
	freeDataStructures(dataStructures);	
	return 0; 

}

void flwcChooseGoals_Example(){


	// Initialize the Data Structures
	srand(time(0)); 
	int fd = open("docs/4.txt", O_RDONLY);
	struct DataStructures* data = initDataStructures(fd); 

	// Initialize the starting word
	int startId = 0; 

	// Initialize the goal words
	int* goalWordSet = NULL;   

	while(goalWordSet == NULL){
	//	goalWordSet = getGoalWordSet(startId, distanceFromGoalWord, data); 
	}
	
	printf("\nStarting Word: %s\n", Convert_IntToWord(startId, data->I2W)); 
	char* w0 = Convert_IntToWord(goalWordSet[0], data->I2W); 
	char* w1 = Convert_IntToWord(goalWordSet[1], data->I2W); 
	printf("Opponent A: %s\n", w0);  
	printf("Opponent B: %s\n", w1);  
	free(goalWordSet); 

	// While game is not over
		// Allow the bot to take a turn 
		// Allow the user to take a turn 
	
	// Declare the winner 
	freeDataStructures(data); 
}

void test_new_flwg(){
	srand(time(0)); 
	int fd = open("docs/4.txt", O_RDONLY);
	struct DataStructures* data = initDataStructures(fd); 
        int num_games = 800;
        int bot_wins = 0;
        int random_wins = 0;
	for (int i = 0; i < num_games; i++){
                if (i % 100 == 0) {
                  printf("%d/%d games complete\n", i, num_games);
                }
		int word = ChooseStart(data->I2W); 
                //int word = 0;
		markUsed_WordSet(word, data->wordSet); 
		int winner = -1; 
		int rounds = 0; 
		int whoseTurn = 1; 

		while (winner == -1){
                        assert(word != -1);
			
			if(whoseTurn){
				//word = botPly_FLWC(word, depth, data); 
				//printf("Minimax Chooses: %s\n", (word == -1) ? "LOSE CONDITION" : Convert_IntToWord(word, data->I2W));
			}
			else{
				word = botPly_Random(word, data); 
				//printf("Random Chooses: %s\n", (word == -1) ? "LOSE CONDITION" : Convert_IntToWord(word, data->I2W));
			}
			whoseTurn = (whoseTurn + 1) % 2; 
			if(word == -1){
				winner = whoseTurn; 
			}
			rounds++; 
		}
                if (winner == 0) {
                  random_wins++;
                } else {
                  bot_wins++;
                }
		reset_WordSet(data->wordSet); 
	}

	//printf("%s Wins\n\n", (winner != 0) ? "Minimax": "Random");
        printf("Bot wins: %d Random wins: %d\n", bot_wins, random_wins);
	
}