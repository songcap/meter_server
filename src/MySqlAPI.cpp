/************************
*author ��ming hao
*filename:MysqlApi

*************************/

#include "MySqlAPI.h"

#include <mysql/mysql.h>

//���캯�� ��ʼ����������������
MySQLInterface::MySQLInterface():errorNum(0),errorInfo("ok")
{
	mysql_library_init(0,NULL,NULL);
	mysql_init(&mysqlInstance);
	mysql_options(&mysqlInstance,MYSQL_SET_CHARSET_NAME,"gbk");
}

MySQLInterface::~MySQLInterface()
{

}

//����MySQL
bool MySQLInterface::connectMySQL(char* server, char* username, char* password, char* database,int port)
{
    	if(mysql_real_connect(&mysqlInstance,server,username,password,database,port,0,0) != NULL)
    	{
                cout<<"connect mysql success!"<<endl;
        		return true;
        }
    	else
    	{
                cout<<"connect mysql success!"<<endl;
        		errorIntoMySQL();
        		return false;
        }
}



//�ж����ݿ��Ƿ���ڣ��������򴴽����ݿ⣬����
bool MySQLInterface::createDatabase(std::string& dbname)
{
        	std::string queryStr = "create database if not exists ";
        	queryStr += dbname;
        	if (0 == mysql_query(&mysqlInstance,queryStr.c_str()))
        	{
        		queryStr = "use ";
        		queryStr += dbname;
        		if (0 == mysql_query(&mysqlInstance,queryStr.c_str()))
        		{
        			cout<<"creat database success!"<<endl;
        			return true;
        		}

        	}
        	errorIntoMySQL();
        	cout<<"creat database fail!"<<endl;
        	return false;
}

/*



 */
//�ж����ݿ����Ƿ������Ӧ���������򴴽���
bool MySQLInterface::createdbTable(const std::string& query)
{

        	if (0 == mysql_query(&mysqlInstance,query.c_str()))
        	{
        		cout<<"creat table success!"<<endl;
        		return true;
        	}
        	errorIntoMySQL();
        	cout<<"creat table fail!"<<endl;
        	return false;
}

//д��ָ��
bool MySQLInterface::writeDataToDB(string queryStr)
{
    	if(0==mysql_query(&mysqlInstance,queryStr.c_str()))
    	{
        	cout<<"write success!"<<endl;
    		return true;
        }
    	else
    	{
            cout<<"write fail!"<<endl;
    		errorIntoMySQL();
    		return false;
        }
}

//��ȡ����
bool MySQLInterface::getDatafromDB(string queryStr, std::vector<std::vector<std::string> >& data)
{
        	if(0!=mysql_query(&mysqlInstance,queryStr.c_str()))
        	{
        		cout<<"read fail!"<<endl;
        		errorIntoMySQL();
        		return false;
        	}

        	result=mysql_store_result(&mysqlInstance);

        	int row=mysql_num_rows(result);
        	int field=mysql_num_fields(result);

        	MYSQL_ROW line=NULL;
        	line=mysql_fetch_row(result);

        	int j=0;
        	std::string temp;
        	while(NULL!=line)
        	{
            		std::vector<std::string> linedata;
            		for(int i=0; i<field;i++)
            		{
                			if(line[i])
                			{
                				temp = line[i];
                				linedata.push_back(temp);
                			}
                			else
                			{
                				temp = "";
                				linedata.push_back(temp);
                			}
            		}
            		line=mysql_fetch_row(result);
            		data.push_back(linedata);
        	}
        return true;
}

//������Ϣ
void MySQLInterface::errorIntoMySQL()
{
    	errorNum=mysql_errno(&mysqlInstance);
    	errorInfo = mysql_error(&mysqlInstance);
        cout << errorNum << "::" << errorInfo <<endl;
}

//�Ͽ�����
void MySQLInterface::closeMySQL()
{
    	cout<<"mysql close!"<<endl;
    	mysql_close(&mysqlInstance);
}
