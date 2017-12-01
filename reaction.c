#include <pthread.h>
#include "reaction.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();


void reaction_init(struct reaction *reaction)
{
	// FILL ME IN
	reaction->h_count = 0;
	reaction->o_count = 0;
	int ret = pthread_cond_init(&(reaction->o), NULL) | pthread_cond_init(&(reaction->h), NULL) | pthread_mutex_init(&(reaction->lock), NULL);
	if(ret != 0)
		printf("Error occured while creating the locks and the condition vars");
}


void reaction_h(struct reaction *reaction)
{
	// FILL ME IN
	pthread_mutex_lock(&(reaction->lock));
	
	static int count = 0;
	debug_print("Call %d to hydrogen_thread\n", ++count);
	int order = count;
	
	if(reaction->h_count >= 1 && reaction->o_count >= 1) {
		debug_print("H[%d] is waking up 1 O and 1 H\n", order);
		reaction->h_count -= 1;
		reaction->o_count--;
		pthread_cond_signal(&(reaction->o));
		pthread_cond_signal(&(reaction->h));
	} else {
		reaction->h_count++;
		debug_print("H[%d] is going to sleep...\n", order);
		pthread_cond_wait(&(reaction->h), &(reaction->lock));
		debug_print("H[%d] is waking up...\n", order);
	}
	pthread_mutex_unlock(&(reaction->lock));
}


void reaction_o(struct reaction *reaction)
{
	// FILL ME IN
	pthread_mutex_lock(&(reaction->lock));
	static int count = 0;
	debug_print("Call %d to oxygen_thread\n", ++count);
	int order = count;
	
	if(reaction->h_count >= 2) {
		debug_print("O[%d] is waking up 2 H\n", order);
		reaction->h_count -= 2;
		pthread_cond_signal(&(reaction->h));
		pthread_cond_signal(&(reaction->h));
		debug_print("Making water now...%d\n", 1);
		make_water();
	} else {
		reaction->o_count++;
		debug_print("O[%d] is going to sleep...\n", order);
		pthread_cond_wait(&(reaction->o), &(reaction->lock));
		debug_print("O[%d] is waking up...\n", order);
		debug_print("Making water now...%d\n", 1);
		make_water();
	}
	pthread_mutex_unlock(&(reaction->lock));

}


