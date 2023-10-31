//
// Created by Святослав on 29.10.2023.
//
#include <cstdint>
#include <string>

class Pile {
 public:
  int width = 1, height = 1;
  mutable int x0, y0, x1, y1;
  int16_t** coords;
  void make_pile();
  void print_pile(std::string filename) const;
  void extends_pile(int le, int ue, int re, int de);
  void interation(int n);
};

class point{
 public:
  int x, y;
  point(int i, int i_1) : x(i), y(i_1){};
  point() : x(-1), y(-1){};

};
point* resize (point * array, int size);