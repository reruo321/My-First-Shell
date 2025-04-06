#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reruo_shell.h"

Command commands[] = {
	{"date", (void (*)(void *))reruo_date, 0},
	{"uptime", (void (*)(void *))reruo_uptime, 0},
	{"ls", (void (*)(void *))reruo_ls, 0},
	{"log", (void (*)(void *))reruo_log, 0},
	{"exit", (void (*)(void *))reruo_exit, 0},
	{"history", (void (*)(void *))reruo_history, 0},
	{"hclear", (void (*)(void *))reruo_hclear, 0},
	{NULL, NULL, 0}
};

void init_history(struct History * history, int size){
	history->max_size = size;
	history->lines = malloc(size * sizeof(char *));
	for(int i=0; i<size; ++i){
		history->lines[i] = NULL;
	}
}

void prompt(){
	printf("reruo > ");
}

void read_command(struct History * history, char * line){
	size_t len = strlen(line);
	if(len == 0)
		return;
	if(line[len-1] == '\n'){
		line[len-1] = '\0';
	}

	char * line_modify = line;
	char * cmd = strtok(line_modify, " ");
	if(cmd == NULL || strlen(cmd) == 0)
		return;

	// Check !num
	if(cmd[0] == '!'){
		char * str_no = malloc(strlen(cmd-1) * sizeof(char));
		for(int i=1; i<(int)strlen(cmd); ++i){
			if(cmd[i] < '0' || cmd[i] > '9'){
				print_error();
				return;
			}
			str_no[i-1] = cmd[i];
		}
		int h_no = atoi(str_no) - 1;
		free(str_no);
		if(h_no >= history->begin || h_no < 0){
			print_error();
			return;
		}

		char * history_line_copy = strdup(history->lines[h_no]);
		if(history_line_copy == NULL){
			print_error();
			return;
		}

		read_command(history, history_line_copy);
		return;
	}

	// Write commands that do not start with !
	write_command(history, line);
	// Check Available Commands
	for(int i=0; commands[i].name != NULL; ++i){
		if(strcmp(cmd, commands[i].name) == 0){
			// reruo_exit
			if(strcmp(cmd, "exit") == 0){
				reruo_exit(history, line);
			} else{
				// Other Functions
				commands[i].func(history);
			}
			return;
		}
	}
	print_error();
}

void write_command(struct History * history, char * line){
	if(history->lines[history->begin] != NULL){
		free(history->lines[history->begin]);
	}
	history->lines[history->begin] = line;
	history->begin = (history->begin + 1) % history->max_size;
}

void print_error(){
	printf("ERROR\n");
}

void reruo_date(){
	system("date");
}

void reruo_uptime(){
	system("uptime");
}

void reruo_ls(){
	system("ls -al");
}

void reruo_log(){
	system("dmesg");
}

void reruo_exit(struct History * history, char * line){

	// Free allocated memory
	for(int i=0; i<history->max_size; ++i){
		if(history->lines[i] != NULL){
			free(history->lines[i]);
			history->lines[i] = NULL;
		}
	}
	free(history->lines);
	free(history);

	exit(0);
}

void reruo_history(struct History * history){
	for(int i=0; i<history->begin; ++i){
		printf("%d  %s\n", i+1, history->lines[i]);
	}
}

void reruo_hclear(struct History * history){
	for(int i=0; i<history->max_size; ++i){
		if(history->lines[i] != NULL){
			free(history->lines[i]);
			history->lines[i] = NULL;
		}
	}
	history->begin = 0;
}
