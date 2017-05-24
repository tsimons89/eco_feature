#include "Eco_population.hpp"
#include "probability.hpp"

#define CALC_TIME_S(F,s) {clock_t begin##s = clock();F; clock_t end##s = clock();cout << "Cycles" << s <<": " << end##s - begin##s << endl;}
#define CALC_TIME(F) {clock_t begin = clock();F; clock_t end = clock();cout << "Cycles: " << end - begin << endl;}


double Eco_population::replacement_rate;
double Eco_population::mutation_rate;
double Eco_population::percent_of_images_held;
unsigned int Eco_population::population_size;

Eco_population::Eco_population(){
	assert_params_set();
}

void Eco_population::assert_params_set(){
	assert(replacement_rate >= 0 && replacement_rate <= 1);
	assert(mutation_rate >= 0 && mutation_rate <= 1);
	assert(percent_of_images_held > 0 && percent_of_images_held < 1);
	assert(population_size > 0);	
}

Eco_creature Eco_population::create_fit_creature(Data_set data_set){
	set_data_sets(data_set);
	init_evolution();
	do{
		evolve();
	}while(!is_evolution_done());
	return population.front();
}

void Eco_population::set_data_sets(Data_set data_set){
	data_set.random_split(hold_set,train_set,Eco_population::percent_of_images_held);
}

void Eco_population::init_evolution(){
	best_fitness = -1;
	stayed_same_count = 0;
	num_selected = ceil((double)Eco_population::population_size * (1.0 - Eco_population::replacement_rate));
	init_population();
}

void Eco_population::init_population(){
	population.clear();
	while(population.size() < Eco_population::population_size)
		population.push_back(Eco_creature());
}

void Eco_population::evolve(){
	natrual_selection();
	cross_over();
	mutate();
	sort_by_fitness();
}
void Eco_population::natrual_selection(){
	sort_by_fitness();
	population.erase(population.begin()+num_selected,population.end());
}

void Eco_population::sort_by_fitness(){
	for(auto& creature:population){
		creature.train(train_set);
		creature.update_fitness(hold_set);
	}
	sort(population.begin(),population.end());
	reverse(population.begin(),population.end());
}

void Eco_population::cross_over(){
	while(population.size() < Eco_population::population_size){
		population.push_back(get_new_offspring());
	}
}

Eco_creature Eco_population::get_new_offspring(){
	return Eco_creature(select_parent(),select_parent());
}

Eco_creature Eco_population::select_parent(){
	return population.at(get_random_uint(num_selected-1));
}

void Eco_population::mutate(){
	// for(auto& creature:population)
	// 	creature.mutate(Eco_population::mutation_rate);
	for(unsigned int i = num_selected-1; i < population.size(); i++)
		population.at(i).mutate(Eco_population::mutation_rate);
}

bool Eco_population::is_evolution_done(){
	double cur_best = population.front().get_fitness();
	if(best_fitness == cur_best)
		stayed_same_count++;
	else{
		stayed_same_count = 0;
		best_fitness = cur_best;
	}
	return REQUIRED_STAY_SAME_COUNT <= stayed_same_count;
}

