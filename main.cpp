#include <iostream>
#include "Parser.h"
#include "image.h"

int main(int argc, char ** argv) {
  Parser ParseObject;
  Get_Data(argc, argv, ParseObject);
  Pile CurrentPile;
  Get_Field_Size(ParseObject.in_filename, CurrentPile);
  CurrentPile.Make_Pile();
  std::string tmp = "j.txt";
  Set_Field(ParseObject.in_filename, CurrentPile);
  CurrentPile.Print_Pile(tmp);

  CurrentPile.Iterate(100000);
  CurrentPile.Print_Pile(ParseObject.out_filename);
  Make_MBP_File(CurrentPile, 1);

  return 0;
}
