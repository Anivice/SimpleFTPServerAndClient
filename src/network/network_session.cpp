#include <unistd.h>
#include <cerrno>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <network_session.h>
#include <simple_err.h>
#include <thread>

void client_session::create_socket()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        throw simple_error_t(SOCKET_CREATION_FAILED_CDX,
                             "create_socket in client_session failed");
    }
}

void client_session::connect()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port);

    int ret_inet_pton = inet_pton(AF_INET, ipv4_addr.c_str(), &serv_addr.sin_addr);
    if(ret_inet_pton <= 0)
    {
        throw simple_error_t(SOCKET_CREATION_FAILED_CDX,
                             "convert ip to binary failed");
    }

    int ret_connect = ::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(ret_connect < 0)
    {
        throw simple_error_t(CONNECT_FAILED_CDX,
                             "connect to server failed");
    }
}

client_session::client_session(const char *ip_address, int _port)
{
    ipv4_addr = ip_address;
    port      = _port;
    create_socket();
    connect();
}

void client_session::close() const
{
    ::close(sockfd);
}

int64_t client_session::read(char *buff, int64_t buff_length) const
{
    int64_t read_len = ::read(sockfd, buff, buff_length);
    if (read_len < 0)
    {
        throw simple_error_t(ERROR_IN_READ_CDX, "client session read() returns -1");
    }

    return read_len;
}

int64_t client_session::write(const char *buff, int64_t buff_length) const
{
    int64_t write_len = ::write(sockfd, buff, buff_length);
    if (write_len < 0)
    {
        throw simple_error_t(ERROR_IN_WRITE_CDX, "client session write() returns -1");
    }

    return write_len;
}

void server_session::close() const
{
    ::close(sockfd);
}

int64_t server_session::read(char *buff, int64_t buff_length) const
{
    int64_t read_len = ::read(sockfd, buff, buff_length);
    if (read_len < 0)
    {
        throw simple_error_t(ERROR_IN_READ_CDX, "client session read() returns -1");
    }

    return read_len;
}

int64_t server_session::write(const char *buff, int64_t buff_length) const
{
    int64_t write_len = ::write(sockfd, buff, buff_length);
    if (write_len < 0)
    {
        throw simple_error_t(ERROR_IN_WRITE_CDX, "client session write() returns -1");
    }

    return write_len;
}

void server_session_pool::create_socket()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd < 0)
    {
        throw simple_error_t(SOCKET_CREATION_FAILED_CDX,
                             "create_socket in client_session failed");
    }
}

void server_session_pool::bind()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    int bind_result = ::bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_result < 0)
    {
        throw simple_error_t(BIND_FAILED_CDX, "Bind to the port failed");
    }
}

server_session_pool::server_session_pool(int _port)
{
    port = _port;
    listen_react_func = nullptr;
    create_socket();
    bind();
}

[[noreturn]] void server_session_pool::listen_thread()
{
    if (::listen(listenfd, 10) < 0)
    {
        throw simple_error_t(LISTEN_FAILED_CDX, "Listen failed in listen_thread");
    }

    while (true)
    {
        int connfd = accept(listenfd, nullptr, nullptr);

        if (connfd < 0)
        {
            throw simple_error_t(ACCEPT_FAILED_CDX, "accept() returned -1");
        }
        std::thread react_thread(listen_react_func, server_session(connfd));
        react_thread.detach();
    }
}

void server_session_pool::listen(void (*_func)(server_session))
{
    listen_react_func = _func;
    std::thread listen_thread(&server_session_pool::listen_thread, this);
    listen_thread.detach();
}

void server_session_pool::close() const
{
    ::close(listenfd);
}
