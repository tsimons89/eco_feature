import unittest
from filter import Filter


class Filter_unit_tests(unittest.TestCase):
    def test_ident_filter(self):
        filter = Filter(0, 0, 0, 0)
        image = [[1, 1], [1, 1]]
        filtered_image = filter.apply(image)
        self.assertEqual(filtered_image, [[1, 1], [1, 1]])

    def test_2x1_x_blur(self):
        filter = Filter(1, 0, 0, 0)
        image = [[1, 1], [1, 1]]
        filtered_image = filter.apply(image)
        self.assertEqual(filtered_image, [[2], [2]])

    def test_3x1_x_blur(self):
        filter = Filter(1, 0, 0, 0)
        image = [[1, 1, 1], [1, 1, 1]]
        filtered_image = filter.apply(image)
        self.assertEqual(filtered_image, [[2, 2], [2, 2]])

    def test_3x1_x_blur2(self):
        filter = Filter(2, 0, 0, 0)
        image = [[1, 1, 1], [1, 1, 1]]
        filtered_image = filter.apply(image)
        self.assertEqual(filtered_image, [[4],[4]])

    # def test_3x2_x_blur1(self):
    #     filter = Filter(1, 0, 0, 0)
    #     image = [[1, 1, 1], [1, 1, 1]]
    #     filtered_image = filter.apply(image)
    #     self.assertEqual(filtered_image, [[1, 1], [1, 1]])


if __name__ == "__main__":
    unittest.main()
