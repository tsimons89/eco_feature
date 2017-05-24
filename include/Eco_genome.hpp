#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
typedef unsigned int Gene;
#define NUM_GENES 4

class Eco_genome{
protected:
	static unsigned int gene_max;
	Gene random_select_gene(Gene g1,Gene g2);
	bool set_random_gene(double prob,Gene& gene);
	void split_genome_string(string s,Gene* values);

public:
	Eco_genome(){}
	Eco_genome(Eco_genome mother, Eco_genome father);
	Eco_genome(string genome_string);
	bool operator==(const Eco_genome& rhs);
	friend ostream& operator<<(ostream& stream, const Eco_genome& genome);

	bool mutate(double rate);
	void init();
	Gene x_blur,y_blur,x_diff,y_diff;
	int get_total() const;
	static void set_gene_max(unsigned int max){gene_max = max;}
};

