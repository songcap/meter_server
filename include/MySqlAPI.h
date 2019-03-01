#ifndef   __MYSQLAPI_H__
#define  __MYSQLAPI_H__

#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <vector>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

using namespace std;

class MySQLInterface
{
public:
    MySQLInterface();
   virtual ~MySQLInterface();

   bool connectMySQL(char* server, char* username, char* password, char* database,int port);
   bool createDatabase(std::string& dbname);
   bool createdbTable(const std::string& query);

   void errorIntoMySQL();
   bool writeDataToDB(string queryStr);
   bool getDatafromDB(string queryStr, std::vector<std::vector<std::string> >& data);
   void closeMySQL();

public:
   int errorNum;                    //�������
   const char* errorInfo;           //������ʾ

private:
   MYSQL mysqlInstance;               //MySQL���󣬱ر���һ�����ݽṹ
   MYSQL_RES *result;                 //���ڴ�Ž�� ������char* ���齫�˽��ת��

};

#endif   /*__MYSQLAPI_H__*/
