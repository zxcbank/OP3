#include "Parser.h"

int main(int argc, char ** argv) {
  Parser ParseObject;
  Get_Data(argc, argv, ParseObject);
  Pile CurrentPile;
  Get_Field_Size(ParseObject.in_filename, CurrentPile);
  CurrentPile.Make_Pile();
  Set_Field(ParseObject.in_filename, CurrentPile);
  CurrentPile.Iterate(ParseObject.max_iter, ParseObject.freq);

  return 0;
}
