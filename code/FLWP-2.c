/**********************************
Name: Jordan D. 
Date: Feb 2, 2020
Purpose: The four letter pathfinder, this time better 
**********************************/
int numLetters = 4; 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./algs/includes/Minimax.h"
#include "./algs/includes/MinimaxTests.h"
#include "./algs/includes/BreadthFirstSearch.h"
#include "./algs/includes/MaxN.h"

#include "./structs/includes/HashMap.h"
#include "./structs/includes/TreeSet.h"

#include "./flwp/includes/PathfinderGame.h"

#include "./flwg/includes/FLWGGame.h"
#include "./flwg/includes/MultiplayerFLWG.h"

void testAlpaBetaPruning(struct wordDataArray *IntToWord_HashMap); 
int main(){

	srand(time(0)); 
	
	
    
	//The Hash Map that can take a word and find its ID
	struct DummyHeadNode** *WordToInt_HashMap;
	
	//The Hash Map that can take an integer and find all sorts of information about it, including the word 
	struct wordDataArray *IntToWord_HashMap; 
	
	char* path = "../docs/4.txt"; 
	
	//Allocates the Word to Int HashMap
	WordToInt_HashMap = Allocate_WordToInt();
	
	IntToWord_HashMap = Allocate_IntToWordStruct();  
	
	Initialize_HashMaps(WordToInt_HashMap, IntToWord_HashMap, path);

	int d = 4; 
	int n = 2; 
	
	Multiplayer_FLWG(WordToInt_HashMap, IntToWord_HashMap);
	//MultiplayerTest(IntToWord_HashMap);
	
	Free_HashMaps(WordToInt_HashMap, IntToWord_HashMap);

	return 0;
}


void testAlpaBetaPruning(struct wordDataArray *IntToWord_HashMap){
	int depth = 4;  
	struct minimaxOutput* a = createOutput(-100, 0, -1, -1); 
	struct minimaxOutput* b = createOutput(100, 1, -1, -1); 
	struct minimaxOutput* output = minimax(0, depth, depth, 1, *a, *b, IntToWord_HashMap); 
	printf("Final Choice: %d", output->id); 
	
	free(output);
	free(a);
	free(b); 
	
}

	/*******MINIMAX STARTS HERE***********/
	/*

	

	
	printf("----DEAN-----\n");
	struct minimaxOutput* deanMO = minimax(deanID, d, d, 1, *a, *b, IntToWord_HashMap);
	removeAlgFound(deanID, IntToWord_HashMap);
	
	printf("\n\n\n----LEAF-----\n");
	struct minimaxOutput* leafMO = minimax(leafID, d, d, 1, *a, *b, IntToWord_HashMap);
	removeAlgFound(leafID, IntToWord_HashMap);
	
	printf("\n");
	
	printf("Dean: \n");
	Print_MinimaxOutput(deanMO);
	printf("Leaf: \n");
	Print_MinimaxOutput(leafMO);
	*/




