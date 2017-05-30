#include "Genome.hpp"
#include "probability.hpp"

using namespace std;

unsigned int Genome::gene_max = 0;


Genome::Genome(string genome_string){
	stringstream ss;
	Gene values[NUM_GENES];
	split_genome_string(genome_string,values);
	x_blur = values[0];
	y_blur = values[1];
	x_diff = values[2];
	y_diff = values[3];
}

void Genome::split_genome_string(string s,Gene* values){
	for(int i = 0; i < NUM_GENES;i++){
		Gene g;
		stringstream ss;
		ss << hex << s[i];
		ss >> g;
		values[i] = g;
	}
}

void Genome::init(){
	assert(gene_max > 0);
	mutate(1);
}

Genome::Genome(Genome mother, Genome father){
	x_blur = random_select_gene(mother.x_blur,father.x_blur);
	y_blur = random_select_gene(mother.y_blur,father.y_blur);
	x_diff = random_select_gene(mother.x_diff,father.x_diff);
	y_diff = random_select_gene(mother.y_diff,father.y_diff);
}

bool Genome::mutate(double rate){
	return (set_random_gene(rate,x_blur)|
			set_random_gene(rate,y_blur)|
			set_random_gene(rate,x_diff)|
			set_random_gene(rate,y_diff));
}

bool Genome::set_random_gene(double prob,Gene& gene){
	if(eval_probability(prob)){
		gene = get_random_uint(gene_max);
		return true;
	}
	return false;
}

Gene Genome::random_select_gene(Gene g1, Gene g2){
	if(eval_probability(.5))
		return g1;
	return g2;
}

int Genome::get_total() const{
	return x_blur + y_blur + x_diff + y_diff;
}

bool Genome::operator==(const Genome& rhs){
	return (x_blur == rhs.x_blur &&
	   		y_blur == rhs.y_blur &&
	   		x_diff == rhs.x_diff &&
	   		y_diff == rhs.y_diff);
}

ostream& operator<<(ostream& stream, const Genome& genome){
	stream << hex << genome.x_blur << genome.y_blur << genome.x_diff << genome.y_diff;
	return stream;
}