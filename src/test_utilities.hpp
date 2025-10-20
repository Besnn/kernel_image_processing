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

    static bool nextToken(std::istream& is, std::string& out) {
      out.clear();
      while (true) {
        int c = is.peek();
        if (c == EOF) return false;
        if (std::isspace(c)) { is.get(); continue; }
        if (c == '#') {
          is.get();
          while (true) {
            int d = is.get();
            if (d == '\n' || d == EOF) break;
          }
          continue;
        }
        break;
      }
      while (true) {
        int c = is.peek();
        if (c == EOF || std::isspace(c) || c == '#') break;
        out.push_back(static_cast<char>(is.get()));
      }
      return !out.empty();
    }

    struct NetpbmTextImage {
        int format = 0;                // 1, 2, or 3
        uint32_t width = 0, height = 0;
        uint32_t maxVal = 1;           // only used for P2/P3
        std::vector<uint32_t> data;    // pixels: PBM 1 value/pixel, PGM 1 value/pixel, PPM 3 values/pixel
    };

    static NetpbmTextImage parseNetpbmText(const std::string& path) {
      std::ifstream f(path);
      if (!f) throw std::runtime_error("Cannot open: " + path);

      std::string tok;
      if (!nextToken(f, tok) || tok.size() < 2 || tok[0] != 'P')
        throw std::runtime_error("Not a Netpbm text file: " + path);

      const int format = tok[1] - '0';
      if (format < 1 || format > 3)
        throw std::runtime_error("Unsupported format (expect P1, P2, P3)");

      if (!nextToken(f, tok)) throw std::runtime_error("Missing width");
      uint32_t w = static_cast<uint32_t>(std::stoul(tok));

      if (!nextToken(f, tok)) throw std::runtime_error("Missing height");
      uint32_t h = static_cast<uint32_t>(std::stoul(tok));

      uint32_t maxv = 1;
      if (format != 1) {
        if (!nextToken(f, tok)) throw std::runtime_error("Missing maxVal");
        maxv = static_cast<uint32_t>(std::stoul(tok));
        if (maxv == 0)
          throw std::runtime_error("Invalid maxVal (0)");
      }

      NetpbmTextImage img;
      img.format = format;
      img.width = w;
      img.height = h;
      img.maxVal = maxv;

      size_t pixel_count = static_cast<size_t>(w) * h;
      size_t channels = (format == 3 ? 3 : 1);
      img.data.resize(pixel_count * channels);

      for (size_t i = 0; i < img.data.size(); ++i) {
        if (!nextToken(f, tok))
          throw std::runtime_error("Unexpected EOF in pixel data");
        uint32_t v = static_cast<uint32_t>(std::stoul(tok));

        if (format == 1) {
          if (v != 0 && v != 1)
            throw std::runtime_error("PBM pixel not 0 or 1");
        } else if (v > maxv)
          throw std::runtime_error("Pixel exceeds maxVal");
        img.data[i] = v;
      }

      return img;
    }

    static bool equalNetpbmTextFiles(const std::string& pathA, const std::string& pathB) {
      try {
        NetpbmTextImage A = parseNetpbmText(pathA);
        NetpbmTextImage B = parseNetpbmText(pathB);

        if (A.format != B.format) {
          return false;
        }
        if (A.width != B.width) {
          return false;
        }
        if (A.height != B.height) {
          return false;
        }
        if (A.maxVal != B.maxVal) {
          return false;
        }

        if (A.data.size() != B.data.size()) {
          return false;
        }
        for (size_t i = 0; i < A.data.size(); ++i) {
          if (A.data[i] != B.data[i]) {
            return false;
          }
        }

        return true;
      } catch (const std::exception &e) {
        return false;
      }
    }
};

#endif //KERNEL_IMAGE_PROCESSING_TEST_UTILITIES_HPP