#include "probability.hpp"

bool initilized = false;

void init_rand(){
	initilized = true;
	srand(time(NULL));
}

double get_random_probability(){
	assert(initilized);
	return (double)rand()/(double)RAND_MAX;
}

bool eval_probability(double prob){
	assert(initilized);
	return (prob > get_random_probability());
}

unsigned int get_random_uint(unsigned int max_val){
	assert(initilized);
	return rand() % (max_val + 1);
}
