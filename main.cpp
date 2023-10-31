#include <iostream>
#include "parser.h"

int main(int argc, char ** argv) {
  parser data_set1;
  get_data(argc, argv, data_set1);
  Pile Field;
  get_field_size(data_set1.in_filename, Field);
  Field.make_pile();
  set_Field(data_set1.in_filename, Field);
  Field.print_pile("old.txt");
  Field.interation(67000);
  Field.print_pile("new.txt");
  return 0;
}
