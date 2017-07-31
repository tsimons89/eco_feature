import sys
import numpy as np
import cv2


def extract_image(input_filename, output_filename):
    img = cv2.imread(input_filename, cv2.IMREAD_GRAYSCALE)
    img = np.asarray(img, dtype=int)
    img = img * 2
    my_file = open(output_filename, 'w')
    for x in np.nditer(np.asarray(img)):
        my_file.write(str(x) + '\n')
    my_file.close()


if __name__ == "__main__":
    extract_image(sys.argv[1], sys.argv[2])
