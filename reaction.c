#include <pthread.h>
#include "reaction.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();


void reaction_init(struct reaction *reaction)
{
	// FILL ME IN
	h_count = 0;
	o_count = 0;
	o = PTHREAD_COND_INITIALIZER;
	h = PTHREAD_COND_INITIALIZER;
	lock = PTHREAD_LOCK_INITIALIZER;
}


void reaction_h(struct reaction *reaction)
{
	// FILL ME IN
	pthread_mutex_lock(&(reaction->lock));
	reaction->h_count++;
	if(h_count >= 2 && o_count >= 1) {
		pthread_cond_signal(reaction->o);
		pthread_cond_signal(reaction->h);
	} else {
		//while(h_count < 2 || o_count < 1)
			pthread_cond_wait(&(reaction->lock), &(reaction->h));
	}
	rection->h_count--;
	pthread_mutex_unlock(&(reaction->lock));
}


void reaction_o(struct reaction *reaction)
{
	// FILL ME IN
	pthread_mutex_lock(&(reaction->lock));
	reaction->o_count++;
	if(h_count >= 2) {
		pthread_cond_signal(reaction->h);
		pthread_cond_signal(reaction->h);
	} else {
		pthread_cond_wait(&(reaction->lock), &(reaction->o));
	}
	reaction->o_count--;
	make_water();
	pthread_mutex_unlock(&(reaction->lock));

}


