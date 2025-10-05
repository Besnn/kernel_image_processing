//
// Created by besnn on 10/5/2025.
//

#ifndef KERNEL_IMAGE_PROCESSING_TEST_UTILITIES_HPP
#define KERNEL_IMAGE_PROCESSING_TEST_UTILITIES_HPP

#include <string>
#include <ios>
#include <fstream>

class TEST_HELPER
{
public:
  static bool files_are_identical(const std::string &path1, const std::string &path2)
  {
    std::ifstream f1(path1, std::ios::binary | std::ios::ate);
    std::ifstream f2(path2, std::ios::binary | std::ios::ate);

    if (!f1.is_open() || !f2.is_open())
      return false; // can't open one of the files

    if (f1.tellg() != f2.tellg())
      return false; // different sizes

    std::ifstream::pos_type size = f1.tellg();
    f1.seekg(0);
    f2.seekg(0);

    constexpr size_t BUFFER_SIZE = 4096;
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    while (size > 0)
    {
      size_t chunk = std::min<size_t>(BUFFER_SIZE, size);
      f1.read(buffer1, chunk);
      f2.read(buffer2, chunk);

      if (std::memcmp(buffer1, buffer2, chunk) != 0)
        return false;

      size -= chunk;
    }

    return true;
  }
};

#endif //KERNEL_IMAGE_PROCESSING_TEST_UTILITIES_HPP
