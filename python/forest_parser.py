import yaml
import sys
import numpy as np


class Forest_parser:
    def __init__(self):
        self.genome = None
        self.start = False
        self.line = None
        self.forest = None
        self.node_iter = None
        self.node = None
        self.node_array = None
        self.leaf_array = None
        self.first_id = None
        self.first_space = None
        self.f_out = None

    def parse_yaml_file(self, filename):
        self.genome = filename.split("rf_")[1][:4]
        yml_doc = ''
        with open(filename, 'r') as f_in:
            for self.line in f_in:
                if 'max_depth:' in self.line:
                    self.max_depth = int(self.line.split()[-1])
                if ' trees:' in self.line:
                    self.start = True
                if self.start:
                    if '{' in self.line:
                        # self.line = self.line.lstrip()
                        num_leading_spaces = len(self.line) - len(
                            self.line.lstrip())
                        leading_spaces = ' ' * num_leading_spaces
                        indent = '\n    ' + leading_spaces
                        self.line = self.line.replace('{ ', indent)
                        self.line = self.line.replace(', ', indent)
                        self.line = self.line.replace(',', '')
                        self.line = self.line.replace('}', '')
                        self.line = self.line.replace(':', ': ')
                    if self.line.lstrip().startswith("le:"):
                        self.line = self.line.replace('}', '')
                        self.line = self.line.replace(':', ': ')
                    yml_doc += self.line
        self.forest = yaml.load(yml_doc)

    def write_trees(self, output_dir):
        out_filename = output_dir + '/forest_' + self.genome + '.dat'
        self.f_out = open(out_filename, 'w')
        self.first_id = 2**(self.max_depth - 1) - 1
        self.first_space = 2**(self.max_depth - 2)
        for tree in self.forest['trees']:
            self.write_tree(tree)

    def write_tree(self, tree):
        self.node_array = np.empty([2**self.max_depth - 1, 3], dtype=int)
        self.leaf_array = np.empty([2**self.max_depth, 1], dtype=int)
        self.node_iter = iter(tree['nodes'])
        self.add_node(self.first_id, self.first_space, False)
        self.node_array = self.node_array[self.node_array[:, 1].argsort()]
        for node in self.node_array:
            for data in node:
                self.f_out.write(str(data) + ' ')
            self.f_out.write('\n')
        for leaf in self.leaf_array:
            self.f_out.write(str(leaf[0]) + '\n')

    def add_node(self, node_id, space, trunc):
        if not trunc:
            self.node = self.node_iter.next()
            if 'splits' not in self.node:
                trunc = True
        var = None
        value = None
        if not trunc:
            var = int(self.node['splits'][0]['var'])
            value = int(self.node['splits'][0]['le'])
        else:
            var = 0
            value = 0
        self.node_array[node_id] = [node_id, var, value]
        if (space == 0):
            self.add_leaf(node_id, trunc)
            self.add_leaf(node_id + 1, trunc)
            return
        self.add_node(node_id - space, space / 2, trunc)
        self.add_node(node_id + space, space / 2, trunc)

    def add_leaf(self, leaf_id, trunc):
        if not trunc:
            self.node = self.node_iter.next()
        self.leaf_array[leaf_id] = self.node['norm_class_idx']


if __name__ == '__main__':
    parser = Forest_parser()
    parser.parse_yaml_file(sys.argv[-1])
    parser.write_trees("./")
