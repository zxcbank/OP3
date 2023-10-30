//
// Created by Святослав on 29.10.2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

void get_data (int argc, char **argv, parser& data_set){
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

void get_field_size(const std::string& filename, Pile& pile){

  std::ifstream in(filename);
  int ymax=-9999999, xmax=-9999999, ymin=999999, xmin=999999, tmpx, tmpy, val;
  // окрываем файл для
  // чтения

  if (!in.is_open())
  {
    std::cerr << "no in file \n";
  } else {
    std::string line;
    int i = 0;
    while (in)
    {
      in >> tmpx;
      in >> tmpy;
      in >> val;
      xmax = std::max(tmpx, xmax);
      ymax = std::max(tmpy, ymax);
      xmin = std::min(tmpx, xmin);
      ymin = std::min(tmpy, ymin);
//      std::cout << ++i << " " << tmpx << " " << tmpy << "\n";
    }
  }

//  std::cout << xmax << "  " << ymax << "\n";
//  std::cout << xmin << "  " << ymin << "\n";

  pile.width = 2 * std::max(abs(xmax), abs(xmin)) + 1;
  pile.height = 2 * std::max(abs(ymax), abs(ymin)) + 1;
  in.close();
}

void set_Field(const std::string& filename, Pile& pile){
  std::ifstream in(filename);
  int tmpx, tmpy, val;
  if (in.is_open())
  {
    std::string line;
    int i = 0;
    while (in)
    {
      in >> tmpx;
      in >> tmpy;
      std::cout << pile.height/2 - tmpy << " " << pile.width/2 + tmpx << "\n";
      in >> pile.coords[pile.height/2 - tmpy][pile.width/2 + tmpx];
    }
  }
}



