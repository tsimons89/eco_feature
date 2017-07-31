from forest_parser import Forest_parser
import os
import sys
import shutil
import fnmatch


class Results_parser:
    def __init__(self):
        self.results_dirname = None
        self.forest_filenames = None

    def parse_results(self, results_dirname, output_dirname):
        self.results_dirname = results_dirname
        self.output_dirname = output_dirname
        self.make_outdir()
        self.copy_adaboost()
        self.get_forest_filenames()
        self.parse_forests()
        self.copy_adaboost()

    def make_outdir(self):
        if os.path.exists(self.output_dirname):
            shutil.rmtree(self.output_dirname)
        os.makedirs(self.output_dirname)

    def get_forest_filenames(self):
        self.forest_filenames = [
            os.path.join(self.results_dirname, filename)
            for filename in os.listdir(self.results_dirname)
            if fnmatch.fnmatch(filename, 'rf_*.yml')
        ]

    def parse_forests(self):
        for filename in self.forest_filenames:
            forest_parser = Forest_parser()
            forest_parser.parse_yaml_file(filename)
            forest_parser.write_trees(self.output_dirname)

    def copy_adaboost(self):
        shutil.copyfile(self.results_dirname + '/adaboost_model',
                        self.output_dirname + '/adaboost_model')


if __name__ == "__main__":
    parser = Results_parser()
    parser.parse_results(sys.argv[1], sys.argv[2])
