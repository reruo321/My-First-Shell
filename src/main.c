#include <stdio.h>
#include <stdlib.h>
#include "reruo_shell.h"

struct History * history;

int main(){

	history = malloc(sizeof(struct History));
	if(history == NULL){
		printf("ERROR: Failed to allocate memory\n");
		return 1;
	}

	init_history(history, MAX_HISTORY_LEN);

	while(1){
		// reruo > 
		prompt();

		// get a command line
		char * line = malloc(MAX_COMMAND_LEN * sizeof(char));
		if(line == NULL){
			printf("ERROR: Failed to allocate memory\n");
			return 1;
		}
		fgets(line, MAX_COMMAND_LEN, stdin);
		
		// read the command
		read_command(history, line);
	}

	return 0;
}
