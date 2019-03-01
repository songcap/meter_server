
#include "MaskHandle.h"

boost::mutex mutex;

/*
主要就是service.run可以使用线程池
然后在线程里面去响应回调函数，回调函数就直接放在线程里面好了
*/

MaskHandle::MaskHandle(boost::shared_ptr< boost::asio::ip::tcp::socket > psocket, MySQLInterface * SqlTool):socket_(psocket)
{
          if(socket_->is_open())
          {
               this->SqlTool = SqlTool;
               cout << "sock is open" << endl;
          }
}

MaskHandle::~MaskHandle()
{

}

char * MaskHandle::getBuf()
{
       return this->buf_;
}

boost::shared_ptr< boost::asio::ip::tcp::socket > MaskHandle::getSocket()
{
      return this->socket_;
}

void  MaskHandle::ReadService()
{
    //解包
    memset(this->buf_,0,100);
    this->socket_->async_read_some(boost::asio::buffer(this->buf_,sizeof(Meter_Message)),
    boost::bind(&MaskHandle::ReadHandle,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}


//读取回调函数
void MaskHandle::ReadHandle(const boost::system::error_code& error ,size_t bytes_transferred)
{

       if(error)
       {
			//这里用来做一下判断，下线一共有两种，就是说第一种是读取超时，第二种就是心跳包的超时
			cout << "read message failed, error code:" << error.value()  << " category name:" << error.category().name() << " message:" << error.message() << endl;
			if( error.value()  == 2)
			{
				   socket_->close();
				  delete this;
			}
			//return;
       }
       else
       {
              if(bytes_transferred >= sizeof(Meter_Message))
              {
                        updateMes();
                        //获取当前时间
                        Date * dateTest = new Date(mes);
                        if(!(dateTest->isValidTime()))
                        {
                                mes.status = 'e';
                        }
                       //记录消息到数据库
                       mutex.lock();
                       if(mes.month== 12 && mes.day == 31)
                       {
                             this->SqlTool->createdbTable(MysqlInstruct(CREATE_TABLE));
                       }
                       //MysqlInstruct(INSERT);
                       this->SqlTool->writeDataToDB(MysqlInstruct(INSERT));
                       mutex.unlock();
                        ReadService();
              }
       }
}

void MaskHandle::updateMes()
{
    memcpy(&mes,this->buf_,sizeof(Meter_Message));
}

string MaskHandle::MysqlInstruct(int mode)
{
    char sqlBuf[300];
    int year = (int)(mes.year);
    int month = (int)(mes.month);
    int day = (int)(mes.day);
    int hour = (int)(mes.hour);
    int minute = (int)(mes.minute);
    int second = (int)(mes.second);
    switch(mode)
    {
        case INSERT:
         sprintf(sqlBuf,"INSERT INTO `%d_meter_message`VALUES(%d,'%c','%d-%02d-%02d','%02d:%02d:%02d');" ,year,mes.id, mes.status,year,month,day,hour,minute,second);
          cout << sqlBuf << endl;
          break;
         case CREATE_TABLE :
         sprintf(sqlBuf,"Create Table If Not Exists `electric`.`%d_meter_message`( `id_ele` Bigint(8) unsigned,`status` Varchar(1),`dates` Date, `hour_min` Time )Engine InnoDB", year);
          break;
         default:
          break;
    }
    string str(sqlBuf);
    return sqlBuf;
}
