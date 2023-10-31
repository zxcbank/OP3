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
  x0 = 0;
  y0 = 0;
  x1 = width;
  y1 = height;
}

void Pile::extends_pile(int le, int ue, int re, int de){
  x0 = x0 - le + width/2;
  x1 = x1 + re + width/2;
  y0 = y0 - ue + height/2;
  y1 = y1 + de + height/2;
  int newh = height/2 + height/2 + height, neww = width/2 + width/2 + width;
  int16_t **tmp = new int16_t*[newh];
  for (int i = 0; i < newh;i++){
    tmp[i] = new int16_t[neww];
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
  coords = new int16_t*[height];
  for (int i = 0; i < height; i++){
    coords[i] = new int16_t [width];
    for (int j = 0; j < width; j++){
      coords[i][j] = tmp[i][j];
    }
  }
  delete [] tmp;
}
void Pile::interation(int n){
  for (int iter = 0; iter < n; iter++){
    int size = 2, k = 0;
    point* array = new point[size];
    array[0] = point(-1, -1);
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++) {
        if (coords[i][j] >= 4){
          if (k == size){
            array = resize(array, size);
            size *=2;
          }
          array[k++] = point(j, i);
        }
      }
    }
    int le, ue, re, de;
    for (int i = 0; i < size; i++){
      if (array[i].x == -1)
        break;
      le = 0, ue = 0, re = 0, de = 0;
      if (array[i].x - 1 < 0)
        le=1;
      if (array[i].x + 1 >= width)
        re=1;
      if (array[i].y - 1 < 0)
        ue=1;
      if (array[i].x + 1 >= height)
        de=1;
      if (le || re || ue || de){
        int oldw = width, oldh = height;
        extends_pile(le, ue, re, de);
        for (int j = 0; j < size; j++){
          if (array[j].x == -1)
            break;
          array[j].x = array[j].x + oldw/2;
          array[j].y = array[j].y + oldh/2;
        }
      }
      std::cout << array[i].x << " " << array[i].y << "\n";
      coords[array[i].y][array[i].x] -= 4;
      coords[array[i].y][array[i].x-1]++;
      if (array[i].x-1 <= x0 && x0 != 0)
        x0--;
      coords[array[i].y][array[i].x+1]++;
      if (array[i].x+1 >= x1-1 && x1 != width)
        x1++;
      coords[array[i].y-1][array[i].x]++;
      if (array[i].y-1 <= y0 && y0 != 0)
        y0--;
      coords[array[i].y+1][array[i].x]++;
      if (array[i].y+1 >= y1-1 && y1 != height)
        y1++;
    }
  }
}

point* resize (point *array, int size){
  point* tmp =  new point[size*2];
  for (int i = 0; i < size; i++){
    if (i < size){
      tmp[i].x = array[i].x;
      tmp[i].y = array[i].y;
    } else {
      tmp[i].x = -1;
      tmp[i].y = -1;
    }
  }

  delete [] array;
  return tmp;
}
void Pile::print_pile(std::string filename) const{
  std::ofstream file(filename);
  if (!file.is_open()){
    std::cerr << "no out file";
  } else {
    std::cout << x0 << " " << x1 << " " << y0 << " " << y1 << "\n";
//    std::cout << width << " " << height << "\n";
    for (int i = y0; i < y1; i++){
      for (int j = x0; j < x1; j++){
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