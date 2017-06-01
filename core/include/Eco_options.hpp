#pragma once
#include <boost/program_options.hpp>
#include "Population.hpp"
#include "Genome.hpp"
#include "Data_set.hpp"
#include "Adaboost_model.hpp"

namespace po = boost::program_options;
using namespace std;

class Eco_options{
private:
	po::options_description train_desc,test_desc,single_predict_desc;
	po::variables_map vm;
	
	void add_train_options();
	void add_test_options();
	void add_single_predict_options();
	void verify_dir_path(string path);
	string single_image_path;
public:
	Eco_options();
	void parse_train_options(int argc,char * argv[]);
	void parse_test_options(int argc,char * argv[]);
	void parse_single_predict_options(int argc,char * argv[]);
	string get_image_path(){return single_image_path;}
};