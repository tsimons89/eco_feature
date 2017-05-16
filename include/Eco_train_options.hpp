#pragma once
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

class Eco_train_options{
private:
	po::options_description desc("Allowed Options");
	po::variables_map vm;
	
	void add_options();
public:
	int population_size;
	float mutation_rate;
	float replacement_rate;
	int num_classes;
	string train_data_path;
	int runs;
	int max_lerners;

	Eco_train_options();
	void parse_options(int argc,char * argv[]);
};