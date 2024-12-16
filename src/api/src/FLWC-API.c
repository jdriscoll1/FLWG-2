#ifndef seenFLWCTutorial
#define seenFLWCTutorial

#include "../includes/FLWG-API.h"
#include "../../structs/includes/ArrayList.h"
#include "../../flwc/includes/Challenges.h"
#include "../../flwp/includes/UserInput.h"

// This creates the first word and returns a set of game components for the flwt
struct GameComponentsFLWC* initFLWC(struct DataStructures* data){
	struct GameComponentsFLWC* flwcComponents = malloc(sizeof(struct GameComponentsFLWC)); 

	struct EndWordParametersFLWC goalParams = {
		.comparatorId=0,
		.letter='c',
	}; 
	struct EndWordParametersFLWC avoidParams = {
		.comparatorId=0, 
		.letter='z',
	}; 

	
	flwcComponents->goalWords = createWordSetGivenCondition(goalParams, data); 
	flwcComponents->avoidWords = createWordSetGivenCondition(avoidParams, data); 

	struct StartWordParametersFLWC params = {
	    .goalWords = flwcComponents->goalWords,
	    .avoidWords = flwcComponents->avoidWords,
	    .minGoalDistance = 3,
	    .maxGoalDistance = 6,
	    .minAvoidDistance = 2,
	    .maxAvoidDistance = 6,
	    .minAdjacencies = 5,
	    .maxAdjacencies = 100,
	};

	flwcComponents->wordId = chooseStartWord_FLWCGeneral(params, flwcComponents, data); 
	return flwcComponents; 

}

// Choose a word
char* getStartWordFLWC(struct GameComponentsFLWC* flwcComponents, struct DataStructures *data){
	return Convert_IntToWord(flwcComponents->wordId, data->I2W); 

}

// Allow the user to insert a word 
int userEntersWordFLWC(char* userInput, struct GameComponentsFLWC* flwcComponents, struct DataStructures* data){
	int isValid = Check_Input(flwcComponents->wordId,(const char*)userInput, data->W2I, data->I2W, data->wordSet); 

	if(isValid == VALID){
		// if the word is valid, mark it as such
		int id = Convert_WordToInt(userInput, data->W2I); 
		markUsed_WordSet(id, data->wordSet); 
		flwcComponents->wordId = id; 
	}

	return isValid; 


}

int isGameWonFLWC(struct GameComponentsFLWC* flwcComponents){
	if(checkIfUsed_WordSet(flwcComponents->wordId, flwcComponents->goalWords)){
		return 1; 
	}
	if(checkIfUsed_WordSet(flwcComponents->wordId, flwcComponents->avoidWords)){
		return -1; 
	}
	return 0; 



}

char* getSolutionFLWC(struct GameComponentsFLWC* flwcComponents){
	return flwcComponents->solution; 		

}

void freeFLWC(struct GameComponentsFLWC* flwcComponents){
	free_WordSet(flwcComponents->avoidWords); 
	free_WordSet(flwcComponents->goalWords); 
	free(flwcComponents->solution); 
	free(flwcComponents); 


}

#endif