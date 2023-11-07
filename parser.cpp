//
// Created by Святослав on 29.10.2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"

void Get_Data (int argc, char **argv, Parser& data_set){ // парсинг командной строки
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-m" || arg == "--max-iter"){
      data_set.max_iter = std::stoi(argv[++i]);
    } else if (arg == "-f" || arg == "--freq"){
      data_set.freq = std::stoi(argv[++i]);
    } else if (arg == "-i" || arg == "--input"){
      data_set.in_filename = argv[++i];
    } else if (arg == "-o" || arg == "--output"){
      data_set.out_filename = argv[++i];
    }
  }
}

void Get_Field_Size(const std::string& filename, Pile& pile){ // Инициализация пустого поля

  std::ifstream in(filename);
  int16_t ymax=-32768, xmax=-32768, ymin=32767, xmin=32767, tmpx, tmpy;
  uint64_t val;

  if (!in.is_open())
  {
    std::cerr << "no input file found \n";
  } else {
    std::string line;
    while (in)
    {
      in >> tmpx;
      in >> tmpy;
      in >> val;
      xmax = std::max(tmpx, xmax);
      ymax = std::max(tmpy, ymax);
      xmin = std::min(tmpx, xmin);
      ymin = std::min(tmpy, ymin);
    }
  }

  pile.x0 = xmin;
  pile.x1 = xmax;
  pile.y0 = ymin;
  pile.y1 = ymax;

  pile.width = abs(xmax - xmin) + 1;
  pile.height = abs(ymax - ymin ) + 1;
  if (pile.width == 1){

    pile.width++;
    pile.x1++;
  }
  if (pile.height == 1){
    pile.height++;
    pile.y1++;
  }
}

void Set_Field(const std::string& filename, Pile& pile){
  std::ifstream in(filename);
  int tmpx, tmpy;
  if (in.is_open())
  {
    std::string line;
    while (in)
    {
      in >> tmpx;
      in >> tmpy;
      in >> pile.coords[pile.y1 - tmpy][tmpx - pile.x0];
    }
    pile.x0 = 0;
    pile.x1 = pile.width - 1;
    pile.y0 = 0;
    pile.y1 = pile.height - 1;
  }
}