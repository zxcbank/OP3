#include "image.h"
#include <cstring>
#include <fstream>

void Make_BMP_File(Pile& CurrentPile, int Iteration) {
  char* Path = new char[100]{};
  Make_File_Name(Path, Iteration);
  int width = CurrentPile.x1 - CurrentPile.x0 + 1;
  int height = CurrentPile.y1 - CurrentPile.y0 + 1;

  std::ofstream file(Path, std::ios::binary);
  if (!file.is_open()) {
    std::cout << Path << std::endl;
    throw std::runtime_error("no such file or directory");
  }
  Put_BMP_Params(CurrentPile, file);
  int pad = ((4 - ((width) / 2 + width % 2) % 4) % 4);
  Pixel_Write(height, width, pad, CurrentPile, file);
}

void Put_BMP_Params(Pile& CurrentPile, std::ofstream& file) {
  int height = CurrentPile.y1 - CurrentPile.y0 + 1;
  int width = CurrentPile.x1 - CurrentPile.x0 + 1;

  int pad = ((4 - (width / 2 + width % 2) % 4) % 4);
  uint64_t file_size =
      14 + 40 + 20 + (width / 2 + width % 2) * height + pad * height;
  int offset = 14 + 40 + 20;
  int header_size = 40;
  int zero = 0;
  int colors = 5;
  int planes = 1;
  int bits_per_pixel = 4;
  file.write("BM", 2);
  file.write(reinterpret_cast<char*>(&file_size), 8);
  file.write(reinterpret_cast<char*>(&offset), 4);
  file.write(reinterpret_cast<char*>(&header_size), 4);
  file.write(reinterpret_cast<char*>(&width), 4);
  file.write(reinterpret_cast<char*>(&height), 4);
  file.write(reinterpret_cast<char*>(&planes), 2);
  file.write(reinterpret_cast<char*>(&bits_per_pixel), 2);
  file.write(reinterpret_cast<const char*>(&zero), 4);
  file.write(reinterpret_cast<char*>(&zero), 4);
  file.write(reinterpret_cast<char*>(&zero), 4);
  file.write(reinterpret_cast<char*>(&zero), 4);
  file.write(reinterpret_cast<char*>(&colors), 4);
  file.write(reinterpret_cast<char*>(&zero), 4);
}
void Pixel_Write(int height, int width, int pad, Pile& CurrentPile,
                 std::ofstream& file) {
  // white
  file.write("\xff\xff\xff\x00", 4);
  // green
  file.write("\x60\xad\x26\x00", 4);
  // yellow
  file.write("\x30\xa6\xab\x00", 4);
  // purple
  file.write("\x6a\x2c\x70\x00", 4);
  // black
  file.write("\x00\x00\x00\x00", 4);
  for (ssize_t i = CurrentPile.y1; i >= CurrentPile.y0; --i) {
    for (size_t j = 0; j < width / 2; ++j) {
      uint8_t pixel = 0;
      pixel |= ((CurrentPile.coords[i][CurrentPile.x0 + 2 * j] > 3) ? 4 : CurrentPile.coords[i][CurrentPile.x0 + 2 * j]) << 4;
      pixel |= ((CurrentPile.coords[i][CurrentPile.x0 + 2 * j + 1] > 3) ? 4 : CurrentPile.coords[i][CurrentPile.x0 + 2 * j + 1]);
      file.write(reinterpret_cast<char*>(&pixel), 1);
    }
    if (width % 2 == 1) {
      uint8_t pixel = 0;
      pixel |= ((CurrentPile.coords[i][CurrentPile.x1] > 3) ? 4 : CurrentPile.coords[i][CurrentPile.x1]) << 4;
      file.write(reinterpret_cast<char*>(&pixel), 1);
    }
    for (size_t j = 0; j < pad; ++j) {
      file.write("\x00", 1);
    }
  }
}

void Make_File_Name(char* Path, int Iteration) {
  char* number = new char[20]{};
  std::strcat(Path, "sandpile");
  std::sprintf(number, "%zu", Iteration);
  std::strcat(Path, number);
  std::strcat(Path, ".bmp");
  delete[] number;
}
