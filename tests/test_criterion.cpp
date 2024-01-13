#include <criterion/criterion.h>
#include "../src/proc_status_parser.h"
#include <vector>
#include <string>
using namespace std;
using namespace VMRSS;

Test(parser, readself)
{
    auto lines_option = getProcStatus("/proc/self/status"s);
    cr_expect(lines_option, "/proc/self/status should be readable");
    cr_expect(!(*lines_option).empty(), "/proc/self/status should return some lines");
}

Test(parser, parseSelf)
{
    std::vector<std::string> lines = *getProcStatus("/proc/self/status"s);
    auto rss = getVmRSS(lines);
    cr_expect(rss > 10, "/proc/self/status should return some lines");
}

Test(parser, parse)
{
    std::vector<std::string> lines;
    lines.push_back("VmSize:     8856 kB");
    lines.push_back("VmLck:         0 kB");
    lines.push_back("VmPin:         0 kB");
    lines.push_back("VmHWM:      2048 kB");
    lines.push_back("VmRSS:      1234 kB");
    lines.push_back("RssAnon:               0 kB");
    lines.push_back("RssFile:            2048 kB");
    lines.push_back("RssShmem:              0 kB");
    lines.push_back("VmData:      360 kB");
    lines.push_back("VmStk:       132 kB");
    lines.push_back("VmExe:        16 kB");
    lines.push_back("VmLib:      1796 kB");
    lines.push_back("VmPTE:        56 kB");
    lines.push_back("VmSwap:        0 kB");
    lines.push_back("HugetlbPages:          0 kB");
    lines.push_back("CoreDumping:    0");
    lines.push_back("THP_enabled:    1");
    lines.push_back("Threads:        1");
    lines.push_back("SigQ:   0/63390");
    lines.push_back("SigPnd: 0000000000000000");
    auto rss = getVmRSS(lines);
    cr_expect(rss == 1234, "VmRSS should be 1234");
}
