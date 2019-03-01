#ifndef  __SERVER_MAIN_H
#define  __SERVER_MAIN_H
//����������ӳ����쳣����δ���

#include <string.h>
#include <iostream>
#include <boost/asio.hpp>
#include<boost/asio/ip/address.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/thread/thread.hpp>

#include <vector>
#include <iostream>


#include "Meter_protocl.h"
#include "MySqlAPI.h"
#include "MaskHandle.h"

using boost::system::error_code;
using namespace boost::asio;


using namespace std;

using  boost::asio::ip::tcp;
using  boost::asio::ip::address;

class  MeterServer
{
public:
            MeterServer(io_service & io_svr,string  bindIp,int port);
              ~MeterServer();
             void  StartAccept();
             void  StartSend(char * buffer,size_t buff_size);

             void  StartService(void) ;
private:

          std::vector< boost::shared_ptr<ip::tcp::socket>  > client_sockets;
          char  buf_[1024];
           //����accept�Ķ���
           ip::tcp::acceptor  myAccept;
           //io_service��
           io_service  &  io_service_;
          //��ʱ����socket�������
          ip::tcp::socket * socket_;

          MySQLInterface * SqlTool;
          //���ӻص�����
          void  AcceptHandle(boost::shared_ptr< ip::tcp::socket > pSocket,boost::system::error_code ec);

          //���ͻص�����
          void  SendHandle(const boost::system::error_code& error ,size_t bytes_transferred,char * buf);
};

void ThreadRun();
//����������ӳ����쳣����δ���

#endif
