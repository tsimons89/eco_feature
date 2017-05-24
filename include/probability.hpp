#pragma once

#include <time.h>
#include <stdlib.h>
#include <assert.h> 

void init_rand();

double get_random_probability();

bool eval_probability(double prob);

unsigned int get_random_uint(unsigned int max_val);

