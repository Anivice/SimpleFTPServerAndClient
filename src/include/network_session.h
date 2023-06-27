#ifndef FTPSRVCLI_NETWORK_SESSION_H
#define FTPSRVCLI_NETWORK_SESSION_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <netinet/in.h>

/*
 * Client Session is a session handling one socket at a time.
 * if the socket is terminated, then the session is over.
 *
 * !! manually close file descriptor is required by session !!
 */

class client_session
{
protected:
    int sockfd = 0;
    struct sockaddr_in serv_addr{};
    int port;
    std::string ipv4_addr;

    /**
     * Create a socket
     * */
    void create_socket();

    /**
     * connect to the provided address
     * (address has already been initialized in client_session()
     * */
    void connect();

public:
    client_session(const char * ip_address, int _port);
    client_session() = delete;
    client_session(const client_session&) = default;

    /**
     * receive data
     *
     * @param buff buffer pointer
     * @param buff_length the length of the buffer
     * @return actual read length
     * */
    int64_t read(char * buff, int64_t buff_length) const;

    /**
     * send data
     *
     * @param buff buffer pointer
     * @param buff_length the length of the buffer
     * @return actual write length
     * */
    int64_t write(const char * buff, int64_t buff_length) const;

    /**
     * close the session
     */
    void close()  const;

    client_session & operator = (const client_session &) = delete;
};

/*
 * Server Session is a session handling one socket at a time, which is connected.
 * if the socket is terminated, then the session is over.
 *
 * !! manually close file descriptor is required by session !!
 *
 */
class server_session_pool;

class server_session
{
protected:
    int sockfd;
    int session_identifier;

public:
    explicit server_session(int _sockfd) : sockfd(_sockfd), session_identifier(0) { }
    server_session() = delete;
    server_session(const server_session&) = default;

    /**
     * receive data
     *
     * @param buff buffer pointer
     * @param buff_length the length of the buffer
     * @return actual read length
     * */
    int64_t read(char * buff, int64_t buff_length) const;

    /**
     * send data
     *
     * @param buff buffer pointer
     * @param buff_length the length of the buffer
     * @return actual write length
     * */
    int64_t write(const char * buff, int64_t buff_length) const;

    /**
     * close the session
     */
    void close() const;

    server_session & operator = (const server_session &) = delete;
    friend server_session_pool;
};

/**
 *
 * Session pool allocates sessions when theres an connection
 *
 * */


class server_session_pool
{
protected:
    int listenfd = 0;
    struct sockaddr_in serv_addr { };
    int port = 0;
    void (*listen_react_func)(server_session);

    /**
      * Create a socket
      * */
    void create_socket();

    /**
      * bind to a port
      * */
    void bind();

    [[noreturn]] void listen_thread();
public:

    explicit server_session_pool(int _port);
    server_session_pool() = delete;
    server_session_pool(const server_session_pool&) = delete;

    /**
     * start listen thread
     */
    void listen(void (*_func)(server_session));

    /**
     * close the session
     */
    void close() const;

    server_session_pool & operator = (const server_session_pool &) = delete;
};

#endif //FTPSRVCLI_NETWORK_SESSION_H
