#include "Date.h"


/*
public:
	   Date(meter_message mes):_year(mes.year),_month(mes.month),_day(mes.day),_hour(mes.hour),_minute(mes.minute),_second(mes.second)
       bool isValidDate();
	   bool isValidTime();
	private:
	   short _year;
	   char _month;
	   char _day;
	   char _hour;
       char _minute;
       char _second;
	   int maxDay;
	   bool isLeapYear();
*/

Date::Date(Meter_Message mes):_year(mes.year),_month(mes.month),_day(mes.day),_hour(mes.hour),_minute(mes.minute),_second(mes.second)
{
     std::cout << "Date ::" << _year << ' ' << _month << ' '  << _day << ' ' << _hour <<' ' << _minute  << "::"<<_second << std::endl;
}

bool Date::isValidDate()
{
    	int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    	if(this->_year > 2000 && this->_year < 3000)
        {
            // month range
             if(_month <= 12 && _month >= 1)
             {
                         //是闰年的话
                  		if(isLeapYear())
                  	    {
                                  if(_month == 2)
                                  {
                      				      maxDay = day[_month]++;
                      			   }
                  		}
                       //每个月的最大日期
                       maxDay = day[_month];
                       if(_day <= maxDay && _day >= 1)
                       {
                           return true;
                       }
             }
    	}
        return  false;
}

bool Date::isValidTime()
{
        if(isValidDate())
       {
           if(_minute < 60 && _minute >=0 && _second < 60 && _second >= 0 && _hour >= 0 && _hour < 24)
               return true;
       }
          return false;
}


bool Date::isLeapYear()
{
        return    (!(_year % 400) || !(_year % 4) )  ?  true : false;
}
