/*
Title: FLWGGame.c
Description: This file will contain the functions for the four letter word game
Author: Jordan Driscoll
Date: 5/1/21

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/FLWGGame.h"

#include "../../algs/includes/MinimaxTests.h"

#include "../../flwp/includes/UserInput.h"
#include "../../flwp/includes/GameFunctions.h"

#include "../../structs/includes/IntLinkedList.h"
#include "../../structs/includes/TranspositionTable.h"

extern int numLetters; 

int FLWG(struct DummyHeadNode*** WordToInt_HashMap, struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet){
	unsigned long hash = 0;

	//So, first choose a start word
	int word = 1; 

	markUsed_WordSet(word, wordSet); 
	//Variable that determines winner: 1 - Algorithm, 0 - player
	int winner = -1;

	//How deep does the bot check? 
	int depth = 4; 
	int rounds = 0; 
	char* wordStr;   
	//Determines if a word is valid
	int isValid = 0; 
	int whoseTurn = 0; 
	while(word >= 0){
		
		//Output the current word
		printf("%s\n", Convert_IntToWord(word, IntToWord_HashMap)); 
		hash = update_GameStateHash(hash, word);
		printf("%d: ", word % (sizeof(unsigned long) * 8));
		long2binary(hash);
		if(whoseTurn == 0){
				
			word = userPly(word, WordToInt_HashMap, IntToWord_HashMap, wordSet);
			
		
		}
		else if(whoseTurn == 1){			
	
			word = botPly(word, depth, hash, IntToWord_HashMap, wordSet, minimax);
			
			//Check the word
			//Go to the connections, and ask if there are any more
		
				
			
		 
		}
		
		whoseTurn = (whoseTurn + 1) % 2;  
		if(word == -1){
			winner = whoseTurn; 
		}
		rounds++; 
		
	}
	printf("%s Wins!\n%d Rounds\n", (winner == 0) ? "Bot A": "Bot B", rounds); 
	//return winner
	return winner; 
	
	
	
	
	
	
}

void FLWG_Test(struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet){
	int A = 0; 
	int B = 0; 
	
	unsigned long hash = 0;
	//So, first choose a start word
	int w = 0; 
	int i = 0;
	int start = 0; 
	int end = 900;  
	int totalRounds = 0; 
	int winner; 
	for(i = start; i < end; i++){
		w = i;
		
		markUsed_WordSet(w, wordSet);
	 
		//Variable that determines winner: 1 - Algorithm, 0 - player
		winner = -1;
		//How deep does the bot check? 

		int depth = 9; 
	
		int rounds = 0;
 
		char* wordStr;   
		//Determines if a word is valid
		int isValid = 0;
		
		int whoseTurn = 0; 

		while(w >= 0){
			//printf("%s\n", IntToWord_HashMap->array[w]->word); 
			if(whoseTurn == 0){
				//w = weakBotPly(w, IntToWord_HashMap);
				w = botPly(w, depth, hash, IntToWord_HashMap, wordSet, minimax);	
			}
			else if(whoseTurn == 1){
				//printf("List: %s\n", toString_IntLL(IntToWord_HashMap->array[w]->connectionHeader, SEPERATED, IntToWord_HashMap)); 
				//w = botPly(w, depth, IntToWord_HashMap, chooseFirst);
				
				w = weakBotPly(w, IntToWord_HashMap, wordSet);
			 
			}
			
			whoseTurn = (whoseTurn + 1) % 2;  
			if(w == -1){
				winner = whoseTurn; 
			}
			rounds++; 
			
			
		}
		totalRounds += rounds; 
		//printf("%s Wins!\n%d Rounds\nRound %d\n", (winner == 0) ? "Bot A" : "Bot B", rounds, i); 

		
		//printf("Rounds: %d\n", rounds); 
		if(winner == 0){
			A++; 
		} 
		else{
			B++; 
		}
		reset_WordSet(wordSet);
	}
	printf("A: %d, B: %d, avg rounds: %d", A, B, totalRounds / (end - start)); 
	
	
	
}

int Input_FLWG(int prevWord, struct DummyHeadNode*** WordToInt_HashMap, struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet){
	int isValid = 0; 
	int wordID; 
	char* wordStr; 
	//Then, the player says a word
	while(isValid != 1){
		printf("Choose a word: "); 
		//Player chooses word 
		//NOTICE -- DISCREET MALLOC
		wordStr = toLowerCase(Take_Input_NoSize());  
		if(strcmp(wordStr, "\n") != 0){	
			wordStr = strtok(wordStr, "\n"); 
		}
		if(strcmp(wordStr, "end") == 0){
			free(wordStr); 
			return -1; 
		}
		wordStr[numLetters] = '\0'; 
		//if the word is end -- game over 
		
		//It checks if the word is valid
		isValid = Check_Input(prevWord, wordStr, WordToInt_HashMap, IntToWord_HashMap); 
		if(isValid == 1){
			wordID = Convert_WordToInt(wordStr, WordToInt_HashMap);
			//if the word has been used
			if(checkIfUsed_WordSet(wordID, wordSet) != 0){
				printf("Word Already Used.\n"); 
				free(wordStr); 
				isValid = 0; 
			}
		}
		else{
			free(wordStr); 
		}

		
	}

	//Add the word to the hash map
	markUsed_WordSet(wordID, wordSet);

	free(wordStr); 
	return wordID; 
	
	
}


int botPly(int word, int depth, unsigned long hash, struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet, struct minimaxOutput* (*minimax_func)(int, int, int, int, struct minimaxOutput, struct minimaxOutput, struct wordDataArray*, struct WordSet*, unsigned long) ){

	struct minimaxOutput* alpha = createOutput(-100, 0, -1, -1); 
	struct minimaxOutput* beta = createOutput(100, 1, -1, -1); 
	//Then, the bot takes this word and runs the minimax algorithm
	struct minimaxOutput* output = (*minimax_func)(word, depth, depth, 1, *alpha, *beta, IntToWord_HashMap, wordSet, hash);
	 
	//If it returns NULL -- game over
	if(output == NULL){
		//The bot won, there is nothing to free
		return -1;  
		
	}
	word = output->id;
	markUsed_WordSet(word, wordSet);
	//Print_MinimaxOutput(output);
	free(output); 
	free(alpha); 
	free(beta); 
	 
	return word; 
	
}

int userPly(int word, struct DummyHeadNode*** WordToInt_HashMap, struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet){
	//Take the user's input
	return Input_FLWG(word, WordToInt_HashMap, IntToWord_HashMap, wordSet); 
	
	
	
}

int weakBotPly(int word, struct wordDataArray* IntToWord_HashMap, struct WordSet *wordSet){
	int w = chooseFirst(word, IntToWord_HashMap, wordSet); 
	if(w == -1){return -1;}
	markUsed_WordSet(w, wordSet); 
	return w; 
	
	
}