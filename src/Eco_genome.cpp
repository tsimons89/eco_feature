#include "Eco_genome.hpp"
#include "probability.hpp"

using namespace std;

unsigned int Eco_genome::gene_max = 0;


Eco_genome::Eco_genome(string genome_string){
	stringstream ss;
	Gene values[NUM_GENES];
	split_genome_string(genome_string,values);
	x_blur = values[0];
	y_blur = values[1];
	x_diff = values[2];
	y_diff = values[3];
}

void Eco_genome::split_genome_string(string s,Gene* values){
	for(int i = 0; i < NUM_GENES;i++){
		Gene g;
		stringstream ss;
		ss << hex << s[i];
		ss >> g;
		values[i] = g;
	}
}

void Eco_genome::init(){
	assert(Eco_genome::gene_max > 0);
	mutate(1);
}

Eco_genome::Eco_genome(Eco_genome mother, Eco_genome father){
	x_blur = random_select_gene(mother.x_blur,father.x_blur);
	y_blur = random_select_gene(mother.y_blur,father.y_blur);
	x_diff = random_select_gene(mother.x_diff,father.x_diff);
	y_diff = random_select_gene(mother.y_diff,father.y_diff);
}

bool Eco_genome::mutate(double rate){
	return (set_random_gene(rate,x_blur)|
			set_random_gene(rate,y_blur)|
			set_random_gene(rate,x_diff)|
			set_random_gene(rate,y_diff));
}

bool Eco_genome::set_random_gene(double prob,Gene& gene){
	if(eval_probability(prob)){
		gene = get_random_uint(Eco_genome::gene_max);
		return true;
	}
	return false;
}

Gene Eco_genome::random_select_gene(Gene g1, Gene g2){
	if(eval_probability(.5))
		return g1;
	return g2;
}

int Eco_genome::get_total() const{
	return x_blur + y_blur + x_diff + y_diff;
}

bool Eco_genome::operator==(const Eco_genome& rhs){
	return (x_blur == rhs.x_blur &&
	   		y_blur == rhs.y_blur &&
	   		x_diff == rhs.x_diff &&
	   		y_diff == rhs.y_diff);
}

ostream& operator<<(ostream& stream, const Eco_genome& genome){
	stream << hex << genome.x_blur << genome.y_blur << genome.x_diff << genome.y_diff;
	return stream;
}