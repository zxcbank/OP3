//
// Created by Святослав on 29.10.2023.
//
#pragma once
#include "pile.h"


class Parser {
 public:
  int max_iter, freq;
  std::string in_filename, out_filename;
};

void Get_Data (int argc, char **argv, Parser& data_set);
void Get_Field_Size(const std::string& filename, Pile& pile);
void Set_Field(const std::string& filename, Pile& pile);