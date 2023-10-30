#include <iostream>
#include "parser.h"

int main(int argc, char ** argv) {
  parser data_set1;
  get_data(argc, argv, data_set1);
  Pile Field;
  get_field_size(data_set1.in_filename, Field);
  Field.make_pile();
  std::cout << " width:" << Field.width << "\n height:" << Field.height << "\n";
  set_Field(data_set1.in_filename, Field);
  Field.print_pile(data_set1.out_filename);

  return 0;
}
