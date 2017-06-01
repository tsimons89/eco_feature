#pragma once
#include "Genome.hpp"
#include "Data_set.hpp"

using namespace ml;

#define MIN_SAMPLE_COUNT 5
#define NOT_UPDATED -1

class Creature{
protected:
	Genome genome;	
	double fitness = NOT_UPDATED;
	double alpha;
	Ptr<RTrees> forest;
	bool trained = false;
	Mat labels;
	Mat images;
	
	Mat process(vector<Mat> data_set);
	void init_forest();
	void set_labels_and_images(Data_set data_set);
	void set_fitness(Data_set data_set);
	void set_alpha(Data_set data_set);
	Mat predict();
	double calc_fitness(Mat results,vector<double> weights);
	static int num_trees,max_tree_depth;
	void load_forest(string path);

public:
	Creature(){genome.init();}
	Creature(string genome_str,double alpha,string forest_path);
	Creature(string genome_str);
	Creature(int x_blur,int y_blur, int x_diff, int y_diff);
	Creature(Creature mother, Creature father)
		{genome = *(new Genome(mother.genome,father.genome));}
	friend ostream& operator<<(ostream& stream, const Creature& eco_creature);
	bool operator<(const Creature& rhs);
	int predict(Mat image);
	bool mutate(double rate){trained = false;return genome.mutate(rate);}
	void train(Data_set data_set);
	void update_fitness(Data_set data_set);
	double get_fitness()const{return fitness;}
	double get_alpha()const{return alpha;}
	Genome get_genome()const{return genome;}
	void write_forest(string path);
	void reset_fitness(){fitness = NOT_UPDATED;}

	static void set_num_trees(int num){num_trees = num;}
	static void set_max_tree_depth(int depth){max_tree_depth = depth;}
};

