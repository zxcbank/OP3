//
// Created by Святослав on 29.10.2023.
//
#include <cstdint>
#include <string>

class Pile {
 public:
  int width = 1, height = 1;
  int16_t** coords;
  void make_pile();
  void print_pile(std::string filename) const;
};




