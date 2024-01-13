#include <vector>
#include <string>
#include <optional>

namespace VMRSS
{
    std::vector<std::string_view> parseArgs(int argc, char *argv[]);
    bool isNumber(std::string_view const &input);
    std::optional<std::string> getOptionValue(std::vector<std::string_view> const &args,std::string_view const &option);
    bool hasOption(std::vector<std::string_view> const &args,std::string_view const &option);
    void removeValue(std::vector<std::string_view> &args, std::string_view const &option);
}