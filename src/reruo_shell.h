#define MAX_COMMAND_LEN 200
#define MAX_HISTORY_LEN 10000
#include <stddef.h>

struct History{
	char ** lines;
	int max_size;
	int begin;
};

typedef struct {
	const char *name;
	void (*func)(void *);
	int argc;
} Command;

void init_history();
void prompt();
void read_command(struct History * history, char * line);
void write_command(struct History * history, char * line);
void print_error();

// Shell Commands
void reruo_date();
void reruo_uptime();
void reruo_ls();
void reruo_log();
void reruo_exit(struct History * history, char * line);
void reruo_history(struct History * history);
void reruo_hclear(struct History * history);

extern Command commands[];
