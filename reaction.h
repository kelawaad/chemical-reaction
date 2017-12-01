#include <stdio.h>
#include <pthread.h>


 #define DEBUG 1

// #define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
// #define __NARG_I_(...) __ARG_N(__VA_ARGS__)
// #define __ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10, N,...) N
	  
// #define __RSEQ_N() 9,8,7,6,5,4,3,2,1,0

// #define _VFUNC_(name, n) name##n
// #define _VFUNC(name, n) _VFUNC_(name, n)
// #define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)

// #define debug_print(...) VFUNC(debug_print, __VA_ARGS__)

// #define GET_MACRO(_1, _2, NAME, ...) NAME


#define get_file_name(varname) #varname".txt"
#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%d:%s():"fmt, \
                                __LINE__, __func__, __VA_ARGS__); } while (0) 							


#undef DEBUG
#define DEBUG 0
struct reaction {
	// FILL ME IN
	pthread_cond_t o;
	pthread_cond_t h;
	pthread_mutex_t lock;
	int h_count;
	int o_count;
};

void reaction_init(struct reaction *reaction);

void reaction_h(struct reaction *reaction);

void reaction_o(struct reaction *reaction);
