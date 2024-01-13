#include <string>
#include <vector>
#include <optional>

namespace VMRSS
{
    std::optional<std::vector<std::string>> getProcStatus(std::string fileName);
    std::optional<int64_t> getVmRSS(std::vector<std::string> const &lines);
}