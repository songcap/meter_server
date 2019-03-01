#ifndef   __MASKHANDLE_H__
#define  __MASKHANDLE_H__

#include <string.h>
#include <ctime>
#include <iostream>
#include <boost/asio.hpp>
#include<boost/asio/ip/address.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "Meter_protocl.h"
#include "MySqlAPI.h"
#include "Date.h"

#define   INSERT 1
#define   CREATE_TABLE 2

using namespace std;
using namespace boost::asio;

using  boost::asio::ip::tcp;
using  boost::asio::ip::address;
using boost::system::error_code;

/*
��ʵ��������ж�ȡ������ν��ֻҪ��֤���buffer�ǰ�ȫ�ľͿ���
��Ҫ������Ҫrun����һֱѭ�����̳߳���������Ϳ����ˣ��̳߳ؿ���ʹ��boost�̳߳�
�첽�Ļ����Ǵ���һ��ָ��֮�������ָ��ͷ��ڶ�������ִ�С�
readhandle��������ǵ���һ�ε���read�����ͺá�
*/

class MaskHandle
{
    public:
          MaskHandle(boost::shared_ptr< boost::asio::ip::tcp::socket > psocket, MySQLInterface * SqlTool);
          ~MaskHandle();
         void  ReadService();
         char * getBuf();
         boost::shared_ptr< boost::asio::ip::tcp::socket > getSocket();
         void  ReadHandle(const boost::system::error_code& error,size_t bytes_transferred);

    private:
        char  buf_[100];
        Meter_Message mes;
        
        MySQLInterface * SqlTool;
    private:

        boost::shared_ptr< boost::asio::ip::tcp::socket > socket_;
        //��ȡ�ص�����const boost::system::error_code& error, size_t bytes_transferred
        void updateMes();

        string MysqlInstruct(int mode);
};


#endif   /*__MASKHANDLE_H__*/
