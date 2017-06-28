import numpy as np


class Filter:
    def __init__(self, x_blur, y_blur, x_diff, y_diff):
        self.x_blur = x_blur
        self.y_blur = y_blur
        self.x_diff = x_diff
        self.y_diff = y_diff

    def apply(self, image):
        np_image = np.array(image)
        for _ in range(self.x_blur):
            image = self.blur_x(np_image)
        return image

    def blur_x(self, image):
        image_shift = image[:, 1:]
        image_shrunk = image[:, :-1]
        sum_images = np.add(image_shrunk, image_shift)
        return sum_images.tolist()
