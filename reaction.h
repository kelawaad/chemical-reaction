#include <stdio.h>
#include <pthread.h>

struct reaction {
	// FILL ME IN
	pthread_cont_t o;
	pthread_cont_t h;
	pthread_mutex_t lock;
	int h_count;
	int o_count;
};

void reaction_init(struct reaction *reaction);

void reaction_h(struct reaction *reaction);

void reaction_o(struct reaction *reaction);
