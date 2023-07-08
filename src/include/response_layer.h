#ifndef FTPSRVCLI_RESPONSE_LAYER_H
#define FTPSRVCLI_RESPONSE_LAYER_H

#include <network_session.h>
#include <ftp.h>

class response_layer
{
private:
    server_session_pool pool;

public:
    explicit response_layer(int port);

};

#endif //FTPSRVCLI_RESPONSE_LAYER_H
