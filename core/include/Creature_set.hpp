#include <opencv2/opencv.hpp>
#incdlue "Creature.hpp"
#include "Data_set.hpp"

class Creature_set{
public:
  Creature_set(){}
  Creature get_fit_creature(Data_set data);
};
