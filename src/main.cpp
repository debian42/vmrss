#include "proc_status_parser.h"
#include "parse_args.h"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <ranges>

using namespace std;
using namespace VMRSS;

int main(int argc, char** argv)
{
     vector<string_view> arguments = parseArgs(argc, argv);
     
     // -n 1
     auto sleepOption = getOptionValue(arguments, "-n");
     string sleepTime_str = "";
     int sleepTimeInMillis = 2000;

     bool hasNOption = hasOption(arguments, "-n");     
     if (sleepOption) {
          sleepTime_str = *sleepOption;
          bool number = isNumber(sleepTime_str);
          if (!number) {
               cerr << "-n must follow a valid number";
               return EXIT_FAILURE;
          }
          sleepTimeInMillis = std::stol(sleepTime_str);
          removeValue(arguments,"-n");
          removeValue(arguments,sleepTime_str);
     } else {
          if (hasNOption)
          {
               cerr << "-n must follow a valid number";
               return EXIT_FAILURE;
          }
     }     

     string pid = "self"; // default: self-test

     if (arguments.empty() || (arguments.size() == 2 && sleepOption))
     {
          cout << " -Self-Test- " << endl;// okay Self-Test
     } else {
          if (arguments.size() == 1)
          {
               pid = arguments.back();
          } else {
               cerr << "wrong arguments passed. Allowed:\n" 
               << "-n xxx : refresh time in millis. Default: 2000. Optional\n"
               << "PID\n"
               << "Example:  " << argv[0] << " 12345 -n 1000\n";
               return EXIT_FAILURE;
          }
     }
     
     cout << "refresh every " << sleepTimeInMillis << " ms\n";

     string path = "/proc/" + pid + "/status";
     while (true) // CTRL+C is your friend
     {
          auto vmrss = getProcStatus(path).and_then(getVmRSS);
          if (vmrss) {
               cout << *vmrss << " kB" << endl;
          } else {
               cerr << "could not open " << path << endl;
               return EXIT_FAILURE;
          }
                    
          this_thread::sleep_for(chrono::milliseconds(sleepTimeInMillis));
     }

     return EXIT_SUCCESS;
}