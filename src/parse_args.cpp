#include "parse_args.h"
#include <algorithm>
#include <ranges>

using namespace std;

namespace VMRSS {
    vector<string_view> parseArgs(int argc, char *argv[])
    {
        vector<string_view> args;
        args.reserve(argc-1);
        for (int i = 1; i < argc; i++)  // i=1 to remove self-name
        {
            args.push_back(argv[i]);
        }
        return args;
    }

    bool hasOption(vector<string_view> const &args, string_view const &option) {
        return ranges::any_of(args, [opt = option](auto v) { return v == opt; });
    }

    void removeValue(std::vector<std::string_view> &args, std::string_view const &option)
    {        
        auto pos = std::find(args.begin(), args.end(), option);
        if (pos != args.end())
            args.erase(pos);
    }

    optional<string> getOptionValue(vector<string_view> const &args, string_view const &option) {
        size_t pos = 0;
        for (auto const &value : args) {
            if (value == option) {
                if (args.size() > pos + 1) {
                    return make_optional<string>(args[pos+1]);
                } else {
                    return nullopt;
                }
            }
            pos++;
        }

        return nullopt;
    }

    bool isNumber(string_view const &input) {
        for (const auto& chr : input) {            
            if (!isdigit(chr)) {
                if (chr != '.' && chr != ',')
                    return false;
            } 
        }
        return true;
    }
}