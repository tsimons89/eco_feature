import unittest
import numpy as np
from filter import Filter


class Filter_unit_tests(unittest.TestCase):
    def setUp(self):
        self.ones3X3 = np.ones((3, 3)).tolist()
        self.eye3x3 = np.identity(3)
        self.image = None
        self.filtered_image = None

    def test_ident_filter(self):
        filter = Filter(0, 0, 0, 0)
        self.image = self.ones3X3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, self.ones3X3)

    def test_3x3_xb1(self):
        filter = Filter(1, 0, 0, 0)
        self.image = self.ones3X3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[2, 2], [2, 2], [2, 2]])

    def test_3x3_xb2(self):
        filter = Filter(2, 0, 0, 0)
        self.image = self.ones3X3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[4], [4], [4]])

    def test_3x3_yb1(self):
        filter = Filter(0, 1, 0, 0)
        self.image = self.ones3X3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[2, 2, 2], [2, 2, 2]])

    def test_3x3_yb2(self):
        filter = Filter(0, 2, 0, 0)
        self.image = self.ones3X3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[4, 4, 4]])

    def test_3x3_xd1(self):
        filter = Filter(0, 0, 1, 0)
        self.image = self.eye3x3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[-1, 0], [1, -1], [0, 1]])

    def test_3x3_yd1(self):
        filter = Filter(0, 0, 0, 1)
        self.image = self.eye3x3
        self.apply_filter(filter)
        self.assertEqual(self.filtered_image, [[-1, 1, 0], [0, -1, 1]])

    def apply_filter(self, filter):
        self.filtered_image = filter.apply(self.image)


if __name__ == "__main__":
    unittest.main(
)
