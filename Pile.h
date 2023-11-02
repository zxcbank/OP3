//
// Created by Святослав on 29.10.2023.
//
#pragma once
#include <cstdint>
#include <string>
#include <iostream>

class Pile {
 public:
  int width = 1, height = 1;
  mutable int16_t x0, y0, x1, y1;
  uint64_t** coords;
  void Make_Pile();
  void Print_Pile(std::string& filename) const;
  void Extend_Pile(int le, int ue, int re, int de);
  void Iterate(int n);
};

class Point{
 public:
  int16_t x = -1, y = -1;
  Point(int16_t x, int16_t y) : x(x), y(y){};
  Point() : x(-1), y(-1){};

};
Point* resize (Point * array, int& size);