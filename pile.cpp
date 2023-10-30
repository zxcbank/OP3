//
// Created by Святослав on 29.10.2023.
//

#include <fstream>
#include <iostream>
#include "pile.h"

void Pile::make_pile() {
    coords = new int16_t*[height];
    for (int i = 0; i < height; i++){
      coords[i] = new int16_t [width];
      for (int j = 0; j < width; j++)
        coords[i][j] = 0;
    }
}

void Pile::print_pile(std::string filename) const{
  std::ofstream file(filename);

  if (!file.is_open()){
    std::cerr << "no out file";
  } else {
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        file << coords[i][j] << " ";
      }
      file << "\n";
    }
  }
}

