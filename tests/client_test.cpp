#include <network_session.h>
#include <unistd.h>
#include <simple_err.h>
#include <iostream>

void react(server_session session)
{
    try
    {
        char buff[1024] { };
        session.read(buff, sizeof(buff));
        std::cout << "Server: " << buff << std::endl;

        std::string msg;
        msg = "Welcome!\n";
        session.write(msg.c_str(), (int) msg.length());
    }
    catch (simple_error_t & error)
    {
        std::cout << error.what() << std::endl;
    }

    session.close();
}

int main()
{
    try
    {
        server_session_pool pool(5000);
        pool.listen(react);

        int id = fork();
        if (id == 0) // child
        {
            for (int i = 0; i < 10; i++)
            {
                try {
                    client_session session("127.0.0.1", 5000);

                    session.write("ACK", 3);

                    char buff[1024]{};
                    session.read(buff, sizeof(buff));
                    std::cout << "Client: " << buff << std::endl;
                }
                catch (simple_error_t & error)
                {
                    std::cout << "Client: " << error.what() << std::endl;
                }

                sleep(1);
            }
        }
        else
        {
            getchar();
            pool.close();
        }
    }
    catch (simple_error_t & error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }

    return 0;
}
