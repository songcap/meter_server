#include "server_main.h"


MeterServer::MeterServer(io_service & io_svr, string bindIp,int port):io_service_(io_svr),myAccept(io_svr,tcp::endpoint(ip::address::from_string(bindIp), port))
{
    //"172.31.4.150"
     this->SqlTool = new MySQLInterface();
     this->SqlTool->connectMySQL("sh-cdb-r929uhoq.sql.tencentcdb.com","public1234","1234abcd","electric",62330);
}

MeterServer::~MeterServer()
{

}

void MeterServer::StartAccept()
{
      boost::shared_ptr< boost::asio::ip::tcp::socket > pSocket(new ip::tcp::socket(this->io_service_));

     //��������Ҫһ��socket��ָ��ȥ���ն��� ���socket��Ҫ����������
      this->myAccept.async_accept(*pSocket,boost::bind(&MeterServer::AcceptHandle,this,pSocket,_1));
}

 //���ӻص�����
 void  MeterServer::AcceptHandle(boost::shared_ptr<ip::tcp::socket> pSocket,boost::system::error_code ec)
{
          if(!ec)
          {
                    if(pSocket->is_open())
                     {
                         MaskHandle * task = new MaskHandle(pSocket,this->SqlTool);
                         client_sockets.push_back(pSocket);
                           //ִ�в���
                          task->ReadService();
                     }
                     StartAccept(); //���ż���
          }
          else
           {

           }
}



void MeterServer::StartService(void)
{
        StartAccept();

        boost::thread_group group;
         for (int num = 0 ; num < 20 ; ++num)
         {
                    //create_thread()��һ���������������Դ���thead���������̣߳�ͬʱ�����ڲ���list
                    // group.create_thread(boost::bind(&runchild , num)) ;
                    group.create_thread(boost::bind(&ThreadRun)) ;
          }
         group.join_all() ; //�ȴ������߳�ִ�н���
}

void  MeterServer::StartSend(char * buffer,size_t buff_size)
{
     this->socket_->async_send(boost::asio::buffer(buffer, buff_size),boost::bind(&MeterServer::SendHandle,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,buffer));
}

 //���ͻص�����
void  MeterServer::SendHandle(const boost::system::error_code& error ,size_t bytes_transferred,char * buf)
{
      if(!error)
      {
        delete buf;
      }
      else
      {
         //�쳣����
      }
}
