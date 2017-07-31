import sys
import shutil
import os
import numpy as np
import cv2


class Images_extractor:
    def __init__(self):
        self.input_dirname = None
        self.output_dirname = None
        self.class_f = None

    def extract(self, input_dirname, output_dirname):
        self.input_dirname = input_dirname
        self.output_dirname = output_dirname
        self.create_outdir()
        self.extract_class_images()

    def create_outdir(self):
        if os.path.exists(self.output_dirname):
            shutil.rmtree(self.output_dirname)
        os.makedirs(self.output_dirname)

    def extract_class_images(self):
        self.class_f = open(self.output_dirname + "/class_index.dat", 'w')
        for dirname in os.listdir(self.input_dirname):
            if os.path.isdir(self.input_dirname + "/" + dirname):
                self.extract_class(dirname)

    def extract_class(self, class_name):
        self.setup_class(class_name)
        self.extract_images(class_name)

    def extract_images(self, class_name):
        out_path = self.output_dirname + "/" + class_name + "/"
        in_path = self.input_dirname + "/" + class_name + "/"
        image_index = open(out_path + "image_index.dat", 'w')
        for image_filename in os.listdir(in_path):
            if ".jpg" in image_filename:
                out_filename = self.extract_filename(image_filename)
                image_index.write(out_filename + "\n")
                self.extract_image(in_path + image_filename,
                                   out_path + out_filename)

    def extract_filename(self, image_filename):
        return image_filename.split(".jpg")[0] + ".dat"

    def extract_image(self, input_filename, output_filename):
        img = cv2.imread(input_filename, cv2.IMREAD_GRAYSCALE)
        img = np.asarray(img, dtype=int)
        img = img * 2
        my_file = open(output_filename, 'w')
        for x in np.nditer(np.asarray(img)):
            my_file.write(str(x) + '\n')
        my_file.close()

    def setup_class(self, class_name):
        class_value = raw_input("Enter value for class " + class_name + ": ")
        self.class_f.write(class_name + " " + class_value + "\n")
        os.makedirs(self.output_dirname + "/" + class_name)


if __name__ == "__main__":
    extractor = Images_extractor()
    extractor.extract(sys.argv[1], sys.argv[2])
