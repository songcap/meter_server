
#ifndef __DATE_H__
#define __DATE_H__

#include "Meter_protocl.h"
#include  <iostream>
class Date
{
	public:
	   Date(Meter_Message mes);
       ~Date();

	   bool isValidTime();
	private:
	   short  _year;
	   int _month;
	   int _day;
	   int _hour;
       int _minute;
       int _second;
	   int maxDay;
	   bool isLeapYear();
       bool isValidDate();
};


#endif /*__DATE_H__*/
