#include "Population.hpp"
#include "probability.hpp"

double Population::replacement_rate;
double Population::mutation_rate;
double Population::percent_of_images_held;
unsigned int Population::population_size;

Population::Population(){
	assert_params_set();
}

void Population::assert_params_set(){
	assert(replacement_rate >= 0 && replacement_rate <= 1);
	assert(mutation_rate >= 0 && mutation_rate <= 1);
	assert(percent_of_images_held > 0 && percent_of_images_held < 1);
	assert(population_size > 0);	
}

Creature Population::create_fit_creature(Data_set data_set){
	set_data_sets(data_set);
	init_evolution();
	do{
		evolve();
	}while(!is_evolution_done());
	return population.front();
}

void Population::set_data_sets(Data_set data_set){
	data_set.random_split(hold_set,train_set,percent_of_images_held);
}

void Population::init_evolution(){
	best_fitness = -1;
	stayed_same_count = 0;
	num_selected = ceil((double)population_size * (1.0 - replacement_rate));
	init_population();
}

void Population::init_population(){
	population.clear();
	while(population.size() < population_size)
		population.push_back(Creature());
}

void Population::evolve(){
	natrual_selection();
	cross_over();
	mutate();
	sort_by_fitness();
}
void Population::natrual_selection(){
	sort_by_fitness();
	population.erase(population.begin()+num_selected,population.end());
}

void Population::sort_by_fitness(){
	for(auto& creature:population){
		creature.train(train_set);
		//creature.update_fitness(hold_set);
		creature.update_weighted_fitness(hold_set);
	}
	sort(population.begin(),population.end());
	reverse(population.begin(),population.end());
}

void Population::cross_over(){
	while(population.size() < population_size){
		population.push_back(get_new_offspring());
	}
}

Creature Population::get_new_offspring(){
	return Creature(select_parent(),select_parent());
}

Creature Population::select_parent(){
	return population.at(get_random_uint(num_selected-1));
}

void Population::mutate(){
	for(unsigned int i = num_selected-1; i < population.size(); i++)
		population.at(i).mutate(mutation_rate);
}

bool Population::is_evolution_done(){
	//double cur_best = population.front().get_fitness();
	double cur_best = population.front().get_weighted_fitness();
	if(best_fitness == cur_best)
		stayed_same_count++;
	else{
		stayed_same_count = 0;
		best_fitness = cur_best;
	}
	return REQUIRED_STAY_SAME_COUNT <= stayed_same_count;
}

