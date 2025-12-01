#include "reader.h"

std::vector<std::string> Reader::readFile(const std::string &filename) const {

   std::string line;
   std::vector<std::string> lines;
   std::ifstream file(filename);

   while(std::getline(file, line)) {
      lines.push_back(line);
   }

   return lines;

}