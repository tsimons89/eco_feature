#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
typedef unsigned int Gene;
#define NUM_GENES 4

class Genome{
protected:
	static unsigned int gene_max;
	Gene random_select_gene(Gene g1,Gene g2);
	bool set_random_gene(double prob,Gene& gene);
	void split_genome_string(string s,Gene* values);

public:
	Genome(){}
	Genome(Genome mother, Genome father);
	Genome(string genome_string);
	Genome(int x_blur,int y_blur, int x_diff, int y_diff):
		x_blur(x_blur),y_blur(y_blur),x_diff(x_diff),y_diff(y_diff){}
	bool operator==(const Genome& rhs);
	friend ostream& operator<<(ostream& stream, const Genome& genome);

	bool mutate(double rate);
	void init();
	Gene x_blur,y_blur,x_diff,y_diff;
	int get_total() const;
	static void set_gene_max(unsigned int max){gene_max = max;}
};

