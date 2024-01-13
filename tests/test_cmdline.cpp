#include <criterion/criterion.h>
#include "../src/parse_args.h"
#include <vector>
#include <string>
using namespace std;
using namespace VMRSS;

Test(cli, hasOption)
{
    std::vector<std::string_view> lines;
    lines.push_back("programName");
    lines.push_back("-n");
    bool value = hasOption(lines,"-n");
    cr_expect(value==true, "-n should be there have a value");
}

Test(cli, getOptionValueOkay)
{
    std::vector<std::string_view> lines;
    lines.push_back("programName");
    lines.push_back("-n");
    lines.push_back("1234");
    auto value = getOptionValue(lines,"-n");
    cr_expect(value, "-n should be there have a value");
}

Test(cli, getOptionValueNOK)
{
    std::vector<std::string_view> lines;
    lines.push_back("programName");
    lines.push_back("-n");
    auto value = getOptionValue(lines,"-n");
    cr_expect(!value, "-n should not have a value");
}

Test(cli, hasOptionOK)
{
    std::vector<std::string_view> lines;
    lines.push_back("programName");
    lines.push_back("-n");
    auto value = hasOption(lines,"-n");
    cr_expect(value, "-n should be there");
}

Test(cli, hasOptionNOK)
{
    std::vector<std::string_view> lines;
    lines.push_back("programName");
    lines.push_back("-d");
    auto value = hasOption(lines,"-n");
    cr_expect(!value, "-n should NOT be there");
}

Test(cli, removeValueOK)
{
    std::vector<std::string_view> lines;
    lines.push_back("1");
    lines.push_back("2");
    lines.push_back("3");
    removeValue(lines,"1");
    removeValue(lines,"2");
    cr_expect(lines.size() == 1, "should have removed two elements");
}

Test(cli, isNumber1)
{    
    cr_expect(isNumber("1") == true, "should be a isNumber1");
}

Test(cli, isNumber1234)
{    
    cr_expect(isNumber("1234") == true, "should be a isNumber1234");
}

Test(cli, isNumberFraction)
{    
    cr_expect(isNumber("12.34") == true, "should be a isNumberFraction");
}