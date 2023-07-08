#include <ftp.h>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <simple_err.h>

int get_port(int argc, char ** argv)
{
    char *arg_value = nullptr;
    int arg, port;

    opterr = 0;

    while ((arg = getopt(argc, argv, "p:")) != -1)
    {
        switch (arg) {
            case 'p':
                arg_value = optarg;
                break;
            case '?':
            default:
                if (optopt == 'p')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                abort();
        }
    }

    if (arg_value == nullptr)
    {
        fprintf(stderr, "%s -p [PORT]\n", argv[0]);
        abort();
    }

    port = (int)strtol(arg_value, nullptr, 10);
    return port;
}

int main (int argc, char **argv)
{
    try {
        int port = get_port(argc, argv);
        server_session_pool pool(port);
        pool.listen()
    }
    catch (simple_error_t & error)
    {
        std::cerr << "Exception caught!\n" << error.what() << std::endl;
        return 1;
    }
    catch (std::exception & error)
    {
        std::cerr << "C++ exception object caught!\n\tERROR: " << error.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << std::endl;
        return 1;
    }

    return 0;
}

//int main (int argc, char ** argv)
//{
//
//
//    return 0;
//}
