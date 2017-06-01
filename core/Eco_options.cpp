#include "Eco_options.hpp"
#include <sys/types.h>
#include <sys/stat.h>


Eco_options::Eco_options(){
	add_train_options();
	add_test_options();
	add_single_predict_options();
}

void Eco_options::add_train_options(){
		train_desc.add_options()
		("help,h", "Produce this help message")
		("train_data_path,d", po::value<string>(),"Folder with training images")
		("results_path,o", po::value<string>(),"Destination path for results")
		("num_learners,n",po::value<unsigned int>()->default_value(20),"Num of weak learners")
		("population_size,p", po::value<int>()->default_value(6),"Size of the GA population")
		("mutation_rate,m", po::value<double>()->default_value(0.25),"GA mutation rate")
		("replacement_rate,r", po::value<double>()->default_value(0.5),"GA replacement rate")
		("percent_images_held,a", po::value<double>()->default_value(0.4),"Percent of images held for testing")
		("gene_max,g", po::value<unsigned int>()->default_value(5),"Max value for any gene in genome")
		("num_trees,t", po::value<unsigned int>()->default_value(15),"Number of trees in each random forest")
		("tree_depth,e", po::value<unsigned int>()->default_value(15),"Max depth of any tree")
		("pool_size,f",po::value<unsigned int>()->default_value(3),"Size of AdaBoost creature selection pool")
		;
}

void Eco_options::parse_train_options(int argc,char * argv[]){        
	po::store(po::parse_command_line(argc, argv, train_desc), vm);
    po::notify(vm);

	if (vm.count("help")) {
	    cout << train_desc << "\n";
	    exit(1);
	}
	if (vm.count("train_data_path")){
		verify_dir_path(vm["train_data_path"].as<string>());
		Data_set::set_data_set_path(vm["train_data_path"].as<string>());
	}
	else{
		cout << "Specify training data path\n";
		exit(-1);
	}
	if (vm.count("results_path")){
		verify_dir_path(vm["results_path"].as<string>());
		Adaboost_model::set_results_path(vm["results_path"].as<string>());
	}
	else{
		cout << "Specify restuls output path\n";
		exit(-1);
	}
	Adaboost_model::set_num_creatures(vm["num_learners"].as<unsigned int>());	
	Population::set_population_size(vm["population_size"].as<int>());
	Adaboost_model::set_pool_size(vm["pool_size"].as<unsigned int>());
	Population::set_mutation_rate(vm["mutation_rate"].as<double>());
	Population::set_replacement_rate(vm["replacement_rate"].as<double>());
	Population::set_percent_of_images_held(vm["percent_images_held"].as<double>());
	Genome::set_gene_max(vm["gene_max"].as<unsigned int>());
	Creature::set_num_trees(vm["num_trees"].as<unsigned int>());
	Creature::set_max_tree_depth(vm["tree_depth"].as<unsigned int>());
}

void Eco_options::add_test_options(){
		test_desc.add_options()
		("help,h", "Produce this help message")
		("test_data_path,d", po::value<string>(),"Folder with testing images")
		("results_path,r", po::value<string>(),"Folder with training results")
		;
}


void Eco_options::parse_test_options(int argc,char * argv[]){        
	po::store(po::parse_command_line(argc, argv, test_desc), vm);
    po::notify(vm);

	if (vm.count("help")) {
	    cout << test_desc << "\n";
	    exit(1);
	}
	if (vm.count("test_data_path")){
		verify_dir_path(vm["test_data_path"].as<string>());
		Data_set::set_data_set_path(vm["test_data_path"].as<string>());
	}
	else{
		cout << "Need testing folder to operate on.\n";
		exit(-1);
	}
	if (vm.count("results_path")){
		verify_dir_path(vm["results_path"].as<string>());
		Adaboost_model::set_results_path(vm["results_path"].as<string>());
	}

}

void Eco_options::add_single_predict_options(){
		single_predict_desc.add_options()
		("help,h", "Produce this help message")
		("image,i", po::value<string>(),"Image path")
		("results_path,r", po::value<string>(),"Folder with training results")
		;
}


void Eco_options::parse_single_predict_options(int argc,char * argv[]){        
	po::store(po::parse_command_line(argc, argv, single_predict_desc), vm);
    po::notify(vm);

	if (vm.count("help")) {
	    cout << single_predict_desc << "\n";
	    exit(1);
	}
	if (vm.count("image")){
		single_image_path = (vm["image"].as<string>());
	}
	else{
		cout << "Need image path\n";
		exit(-1);
	}
	if (vm.count("results_path")){
		verify_dir_path(vm["results_path"].as<string>());
		Adaboost_model::set_results_path(vm["results_path"].as<string>());
	}

}





void Eco_options::verify_dir_path(string path){
	struct stat info;
	if( stat( path.c_str(), &info ) != 0 || !(info.st_mode & S_IFDIR)){
		cout << path << " is not a valid directory\n";
		exit(-1);
	}
}
