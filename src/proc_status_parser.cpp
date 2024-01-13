#include <iostream>
#include <vector>
#include <fstream>
#include "proc_status_parser.h"

using namespace std;
namespace VMRSS
{
     optional<vector<string>> getProcStatus(string fileName)
     {
          ifstream file(fileName);

          if (!file.is_open())
               return nullopt;

          string line;
          vector<string> lines;
          lines.reserve(128);

          while (!std::getline(file, line).eof())
          {
               lines.push_back(line);
          }

          return make_optional(lines);
     }

     optional<int64_t> getVmRSS(vector<string> const &lines)
     {
          for (auto const &line : lines)
          {
               if (line.starts_with("VmRSS:"s))
               {
                    auto end = line.find(" kb"s);
                    string valueInKb = line.substr(6, end);
                    return make_optional(std::stoll(valueInKb));
               }
          }
          return nullopt;
     }
}