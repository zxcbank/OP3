//
// Created by Святослав on 02.11.2023.
//

#include "Pile.h"
#include <fstream>
#include <iostream>
#include "image.h"

void Pile::Make_Pile() {
  coords = new uint64_t *[height];
  for (int i = 0; i < height; i++){
    coords[i] = new uint64_t [width];
    for (int j = 0; j < width; j++)
      coords[i][j] = 0;
  }
}

void Pile::Extend_Pile(int le, int ue, int re, int de){
  x0 = x0 - le + width/2;
  x1 = x1 + re + width/2;
  y0 = y0 - ue + height/2;
  y1 = y1 + de + height/2;
  int newh = height/2 + height/2 + height, neww = width/2 + width/2 + width;
  uint64_t **tmp = new uint64_t *[newh];
  for (int i = 0; i < newh;i++){
    tmp[i] = new uint64_t [neww];
    for (int j = 0; j < neww; j++){
      tmp[i][j] = 0;
    }
  }

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      tmp[i+height/2][j+width/2] = coords[i][j];
    }
  }

  width = width + width/2 + width/2;
  height = height + height/2 + height/2;
  coords = new uint64_t *[height];
  for (int i = 0; i < height; i++){
    coords[i] = new uint64_t[width];
    for (int j = 0; j < width; j++){
      coords[i][j] = tmp[i][j];
    }
  }
  delete [] tmp;
}

void Pile::Iterate(int n, int freq){
  if (freq == 0){
    freq = n-1;
  }
  for (int iter = 0; iter < n; iter++){
    if (iter % freq == 0)
      Make_BMP_File(*this, iter);
    int size = 2, k = 0;
    Point* array = new Point[size];
    for (int y = 0; y < height; y++){
      for (int x = 0; x < width; x++) {
        if (coords[y][x] >= 4){
          if (k == size){
            array = resize(array, size);
          }
          array[k++] = Point(x, y);
        }
      }
    }

    int le, ue, re, de;
    for (int i = 0; i < size; i++){
      if (array[i].x == -1)
        break;
      le = 0, ue = 0, re = 0, de = 0;
      if (array[i].x - 1 <= 0)
        le=1;
      if (array[i].x >= width-1)
        re=1;
      if (array[i].y - 1 <= 0)
        ue=1;
      if (array[i].y >= height-1)
        de=1;
      if (le || re || ue || de){
        int oldw = width, oldh = height;
        Extend_Pile(le, ue, re, de);

        for (int j = 0; j < size; j++){
          if (array[j].x == -1)
            break;
          array[j].x = array[j].x + oldw/2;
          array[j].y = array[j].y + oldh/2;
        }
      }

      coords[array[i].y][array[i].x] -= 4;
      coords[array[i].y][array[i].x-1]++;
      if (array[i].x-1 <= x0 && x0 != 0)
        x0--;
      coords[array[i].y][array[i].x+1]++;
      if (array[i].x+1 >= x1 && x1 != width-1)
        x1++;
      coords[array[i].y-1][array[i].x]++;
      if (array[i].y-1 <= y0 && y0 != 0)
        y0--;
      coords[array[i].y+1][array[i].x]++;
      if (array[i].y+1 >= y1 && y1 != height-1)
        y1++;
    }
  }
}

Point* resize (Point * array, int& size){
  Point* tmp = new Point[size * 2];
  for (int i = 0; i < size; i++){
    tmp[i].x = array[i].x;
    tmp[i].y = array[i].y;
  }
  size *=2;

  delete [] array;
  return tmp;
}


void Pile::Print_Pile(std::string& filename) const{
  std::ofstream file(filename);
  if (!file.is_open()){
    std::cerr << "no out file";
  } else {
    for (int i = y0; i <= y1; i++){
      for (int j = x0; j <= x1; j++){
        if (coords[i][j] == 0)
          file << "." << " ";
        if (coords[i][j] == 1)
          file << "1" << " ";
        if (coords[i][j] == 2)
          file << "2" << " ";
        if (coords[i][j] == 3)
          file << "3" << " ";
        if (coords[i][j] > 3)
          file << "*" << " ";
      }
      file << "\n";
    }
  }
}
