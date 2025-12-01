#include <vector>
#include <iostream>
#include <fstream>

class Reader {
   public:
      std::vector<std::string> readFile(const std::string &filename) const;
};