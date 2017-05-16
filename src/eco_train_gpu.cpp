#include "Eco_train_optrions.hpp"
#include "Gpu_eco_trainer.hpp"

int main(int argc, char *argv[]){
	Eco_train_options options;
	options.parse_options(arc,argv);
	Gpu_eco_trainer trainer(options);
	trainer.write_results();
}