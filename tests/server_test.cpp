#include <network_session.h>
#include <unistd.h>
#include <simple_err.h>
#include <iostream>

void react(server_session session)
{
    try
    {
        std::string msg;
        msg = "Welcome!\n";
        session.write(msg.c_str(), (int) msg.length());

        for (int i = 0; i < 10; i++)
        {
            char buff[1024] { };
            auto len = session.read(buff, sizeof(buff));
            session.write(buff, len);
        }
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
        getchar();
    }
    catch (simple_error_t & error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }

    return 0;
}
