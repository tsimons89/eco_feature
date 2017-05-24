#pragma once

#include <opencv2/opencv.hpp>
#include "Eco_creature.hpp"
#include "Data_set.hpp"

#define REQUIRED_STAY_SAME_COUNT 3
#define OFFSPRING_TRIES 100

class Eco_population{
private:
	Data_set train_set,hold_set;
	vector<Eco_creature> population;

	double best_fitness;
	int stayed_same_count,num_selected;

	void assert_params_set();
	void init_evolution();
	void init_population();
	void set_data_sets(Data_set data_set);
	void evolve();
	bool is_evolution_done();
	void natrual_selection();
	void cross_over();
	void mutate();
	void sort_by_fitness();
	Eco_creature select_parent();
	Eco_creature get_new_offspring();

	static double replacement_rate,mutation_rate,percent_of_images_held;
	static unsigned int population_size;



public:
	Eco_population();
	Eco_creature create_fit_creature(Data_set data_set);
	
	static void set_replacement_rate(double rate){replacement_rate = rate;}
	static void set_mutation_rate(double rate){mutation_rate = rate;}
	static void set_percent_of_images_held(double percent){percent_of_images_held = percent;}
	static void set_population_size(int size){population_size = size;}
};

