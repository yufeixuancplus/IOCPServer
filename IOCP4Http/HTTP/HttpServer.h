#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__
#include "../Iocp/IocpServer.h"

class HttpServer : public IocpServer
{
public:
	HttpServer(short listenPort, int maxConnCount = MAX_CONN_COUNT);
    ~HttpServer();
	
protected:
    void notifyPackageReceived(ClientContext* pClientCtx) override;
    //void notifyDisconnected(SOCKET s, Addr addr) override;
};

#endif // !__HTTP_SERVER_H__
