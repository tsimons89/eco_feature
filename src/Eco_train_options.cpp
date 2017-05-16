#include "Eco_train_options.hpp"

Eco_train_options::Eco_train_options(){
	add_options();
}

void Eco_train_options::add_options(){
		desc.add_options()
		("help", "Produce this help message")
		("train_data_path,d", po::value< vector<string> >(),"Folder with training images")
		("num_classes,c", po::value<int>(),"Number of classes")
		("max_learners,l",po::value<int>()->default_value(1000),"Max num of weak learners")
		("population_size,p", po::value<int>()->default_value(10),"Size of the GA population")
		("runs,u", po::value<int>()->default_value(10),"runs of the program to make")
		("mutation_rate,m", po::value<float>()->default_value(0.025),"GA mutation rate")
		("replacement_rate,r", po::value<float>()->default_value(0.125),"GA replacement rate")
		;
}

void Eco_train_options::parse_options(int argc,char * argv[]){        
	po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

	if (vm.count("help")) {
	    cout << desc << "\n";
	    exit(1);
	}
	if (vm.count("training_folder"))
		train_data_path = vm["train_data_path"].at<string>();
	else{
		cout << "Need training folder to operate on.\n";
		exit(-1);
	}
	if (vm.count("num_classes"))
		num_classes = vm["num_classes"].as<int>();
	else{
		cout << "Need training folder to operate on.\n";
		exit(-1);

	}
	max_learners = vm["max_learners"].as<int>();	
	population_size = vm["population_size"].as<int>();
	runs = vm["runs"].as<int>();
	mutation_rate = vm["mutation_rate"].as<float>();
	replacement_rate = vm["replacement_rate"].as<float>();
}
