#pragma once
#include "Pile.h"

void Make_BMP_File(Pile& CurrentPile, int Iteration);
void Make_File_Name(char* Path, int Iteration);
void Put_BMP_Params(Pile& CurrentPile, std::ofstream& file);
void Pixel_Write(int height, int width, int pad, Pile& CurrentPile, std::ofstream& file);