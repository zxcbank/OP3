//
// Created by Святослав on 29.10.2023.
//
#include "pile.h"

class parser {
 public:
  int max_iter, freq;
  std::string in_filename, out_filename;
};

void get_data (int argc, char **argv, parser& data_set);
void get_field_size(const std::string& filename, Pile& pile);
void set_Field(const std::string& filename, Pile& pile);