import numpy as np


class Filter:
    def __init__(self, x_blur, y_blur, x_diff, y_diff):
        self.x_blur = x_blur
        self.y_blur = y_blur
        self.x_diff = x_diff
        self.y_diff = y_diff
        self.image_shift = None
        self.image_shrunk = None
        self.np_image = None

    def apply(self, image):
        self.np_image = np.array(image, dtype=np.int32)
        for _ in range(self.x_blur):
            self.blur_x()
        for _ in range(self.y_blur):
            self.blur_y()
        for _ in range(self.x_diff):
            self.diff_x()
        for _ in range(self.y_diff):
            self.diff_y()
        return self.np_image.tolist()

    def blur_x(self):
        self.shift_right()
        self.blur()
        return self.np_image

    def blur_y(self):
        self.shift_down()
        self.blur()
        return self.np_image

    def diff_x(self):
        self.shift_right()
        self.diff()
        return self.np_image

    def diff_y(self):
        self.shift_down()
        self.diff()
        return self.np_image

    def shift_right(self):
        self.image_shift = self.np_image[:, 1:]
        self.image_shrunk = self.np_image[:, :-1]

    def shift_down(self):
        self.image_shift = self.np_image[1:, :]
        self.image_shrunk = self.np_image[:-1, :]

    def blur(self):
        self.np_image = np.add(self.image_shrunk, self.image_shift)

    def diff(self):
        self.np_image = np.subtract(self.image_shift, self.image_shrunk)
