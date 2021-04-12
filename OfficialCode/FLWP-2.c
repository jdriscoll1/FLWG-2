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




#include "HashMap2.h"

#include "Arrays.h"

#include "BreadthFirstSearch.h"

#include "GenericLinkedListNode.h"

#include "HashSet.h"

#include "HashFunctions.h"

#include "UserInput.h"

#include "GameFunctions.h"

#include "PathGameComponents.h"

#include "ArrayList.h"

#include "PathfinderGame.h"

#include "FLWGAlgorithm.h"

void WordConnections(); 
void GenericLLExample(); 
void WordLLTest();
void HashSetExample(); 
void OneDimArray(); 
void CreateBasicWordLL(); 
void RandomizeArrayExample(); 
void RandomizedList(); 
void WeBeginTheGame(); 
void AllConnections(); 
void AVLTree(); 
void PathfinderGameMain(); 
int ConnectionOptimization(); 
void FLWP(); 


int main(){
 	struct DummyHeadNode*** HashMap = Create_HashMap(NULL); 
 	
	 struct word*** HashSet = AllocateHashSet(); 
	 //Alright now I need to make an algorithm that will go through and find all of the number of nodes each one has as it goes out 
 	AddToHashSet("take", HashSet, 1);
	struct TreeStorageNode* tree = FLWGAlgorithm("take", HashSet, HashMap); 
	if(tree == NULL){
		printf("Fail");
		exit(0);  
	}
	Print_TreeStorageReverseConnections(tree);

	return 0;  
}




void FLWP(){
	srand(time(0)); 
	int totalWordsCount[3] = {30, 590, 2235};  
	char** allWords = calloc(totalWordsCount[numLetters - 2], sizeof(char*)); 
	struct DummyHeadNode*** H = Create_HashMap(allWords);
	Play_FLWP(H, allWords); 
	Free_HashMap(H); 
	Free_2DArray(totalWordsCount[numLetters - 2], (void***)allWords, 0); 

	
 


}
//So, I need to get a mean, and the upper and lower quartile 
//What I have to do, Is I have to run through all of the words, and all of their number of connections from 2 to 15 and find
//Now, how in the hell am I going to be able to redo a round? 
//I have to ask the user if they'd like to move on to the next round
//They will have 3 options, yes, no, or redo
//If they choose yes, it will move them along
//If they choose no, it will end the game
//If they choose retry, it'll re-initialize the game Components, but this time the score and the goal will be the old score and also goal 
//So, I think I have no choice but to create a structure that stores everything 
//it'll store their score
//The the round they are on
//Their total score



void WordLLTest(){
	struct word *header = malloc(sizeof(struct word)); 
	header->next = NULL; 
	AddToBack_WordLL("pies", header, 0);
	AddToBack_WordLL("ties", header, 0); 
	AddToBack_WordLL("lies", header, 0); 
	AddToFront_WordLL("dies", header, 0); 
	Remove_WordLL("pies", header); 
	Print_WordLL(header, SEPERATED); 
	Free_WordLL(header);   
	
}


void OneDimArray(){
	int* array = (int*)Allocate_Array(5);  
	int i = 0; 
	/*From Here*/ 
	for(i = 0; i < 5; i++){
		*((int*)array + i) = i; 
	}
	
	/*To Here, without this snippit of code it works perfectly*/
	free(array);
}

void CreateBasicWordLL(){
	struct word *testList = malloc(sizeof(struct word)); 
	testList->next = NULL; 
	AddToBack_WordLL("pies", testList, 0);
	AddToBack_WordLL("dies", testList, 0);
	AddToBack_WordLL("lies", testList, 0);
	AddToBack_WordLL("ties", testList, 0);
	AddToBack_WordLL("vies", testList, 0);
	AddToBack_WordLL("yies", testList, 0);


	char** array = ConvertWordLLTo2DArray(testList);
	Print_2DArray(6, (void***)array, STRING); 
	 
	Free_2DArray(6, (void***)array, 0); 
	Free_WordLL(testList);  
}



