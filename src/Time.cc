#include "Time.h"
#include <Arduino.h>

//Konstruktor

Time::Time()
{}

Time::Time(int const h , int const m , int const s)
    : hour{h}, minute{m}, second{s}
{
    check_time();
}


void Time::check_time() const
{
    if (hour >= 24 or hour < 0)
    {
        Serial.print("ERROR: Hours have to be [0,23]");
    }
    else if (minute >= 60 or minute < 0)
    {
        Serial.print("ERROR: Minutes have to be [0,59]");
    }
    else if (second >= 60 or second < 0)
    {
        Serial.print("ERROR: Seconds have to be [0,59]");
    }
}

//Funktioner

bool Time::is_am() const
{
    return hour < 12;
}

int Time::get_hour() const
{
    return hour;
}
int Time::get_minute() const
{
    return minute;
}
int Time::get_second() const
{
    return second;
}


Time Time::inc_hour()
{
    if ((*this).hour == 23)
		(*this).hour = 0;
	else
		(*this).hour++;
    	
	return *this;

}

Time Time::inc_minute()
{
    if ((*this).minute == 59)
		(*this).minute = 0;
	else
		(*this).minute++;
    	
	return *this;
}

Time Time::inc_second()
{
    if ((*this).second == 59)
		(*this).second = 0;
	else
		(*this)++;
    	
	return *this;
}



//Operatorer

Time& Time::operator++()
{
    return *this += 1;
}

Time Time::operator++(int)
{
    Time tmp {*this};
    ++(*this);
    return tmp;
}

Time& Time::operator--()
{
    return *this -= 1;
}

Time Time::operator--(int)
{
    Time tmp {*this};
    --(*this);
    return tmp;
}

bool Time::operator<(Time const& rhs) const
{   
    if (hour == rhs.hour && minute == rhs.minute)
    {
        return second < rhs.second;
    }
    else if (hour == rhs.hour && minute != rhs.minute)
    {
        return minute < rhs.minute;
    }
    else
    {
        return hour < rhs.hour;
    }
}

bool Time::operator>(Time const& rhs) const
{
    return rhs < *this;
}

bool Time::operator==(Time const& rhs) const
{
    return !(rhs < *this) && !(rhs > *this);
}

bool Time::operator<=(Time const& rhs) const
{
    return (*this < rhs || *this == rhs);
}

bool Time::operator>=(Time const& rhs) const
{
    return (*this > rhs || *this == rhs);
}

bool Time::operator!=(Time const& rhs) const
{
    return !(*this == rhs);   
}


//Bonus

Time Time::operator+(int const& i)
{
  Time tmp{*this};
  if (i < 0)
  {
    tmp = (tmp - (i*(-1)));
  }
  else
  {
    tmp.second += i;
    if (tmp.second > 59)
    {
      tmp.minute += tmp.second/60;
      tmp.second = tmp.second % 60;
      if (tmp.minute > 59)
      {
        tmp.hour += tmp.minute/60;
        tmp.minute = tmp.minute % 60;
        if (tmp.hour > 23)
        {
          tmp.hour = tmp.hour % 24;
        }
      }
    }
  }
  return tmp;
}

Time operator+(int const& i, Time const& time)
{
    Time tmp{time};
    return tmp + i;
}

Time Time::operator-(int const& i)
{
  Time tmp{*this};
  if (i < 0)
  {
    tmp = (tmp + (i*(-1)));
  }
  else
  {
    tmp.second -= i;
    if (tmp.second < 0) 
    {
      tmp.minute += ((tmp.second/60) - 1);
      tmp.second = 60 + (tmp.second % 60);
      if (60 + (tmp.second % 60) == 60)
      {
        tmp.minute ++;
        tmp.second = 0;
      }
      if (tmp.minute < 0)
      {
        tmp.hour += ((tmp.minute/60) - 1);
        tmp.minute = 60 + (tmp.minute % 60);
        if (60 + (tmp.minute % 60) == 60)
        {
          tmp.hour++;
          tmp.minute = 0;
        }
        if (tmp.hour < 0)
        {
          tmp.hour = 24 + (tmp.hour % 24);
          if (tmp.hour == 24)
          {
            tmp.hour = 0;
          }
        }
      }
    }
  }
  return tmp;
}

Time& Time::operator+=(int const& i)
{
    *this = *this + i;
    return *this;
}

Time& Time::operator-=(int const& i)
{
    *this = *this - i;
    return *this;
}