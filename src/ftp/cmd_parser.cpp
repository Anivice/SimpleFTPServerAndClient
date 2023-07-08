#include <ftp.h>
#include <string>
#include <cstring>
#include <simple_err.h>

void to_upper(std::string & string)
{
    const char OFFSET = 'a' - 'A';
    for (auto & i : string)
    {
        i = (char)toupper(i);
    }
}

cmdlist strcmd2numcmd(const char *_cmdlist_str)
{
    std::string cmd = _cmdlist_str;
    int offset = 0;
    to_upper(cmd);

    for (auto& i : cmdlist_str)
    {
        if (cmd == i)
        {
            return (cmdlist)offset;
        }

        offset++;
    }

    // 550 response
}
