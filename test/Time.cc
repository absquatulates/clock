#include "Time.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>


//Konstruktor

Time::Time()
{}

Time::Time(int const h , int const m , int const s)
    : hour{h}, minute{m}, second{s}
{
    check_time();
}

Time::Time(std::string const& t_s)
{
    hour = stoi(t_s.substr(0,2));
    minute = stoi(t_s.substr(3,2));
    second = stoi(t_s.substr(6,2));

    if (t_s.size() > 8 )
    {
        if (hour > 12)
        {
            throw std::out_of_range{"I 12h-format måste timmar vara [0, 12]"};
        }

        if (t_s.substr(8,2) == "pm" && hour != 12) 
        {
            hour += 12;
        }
        else if (t_s.substr(8,2) == "am" && hour == 12)
        {
            hour = 0;
        } 
    }

    check_time();
}


//Funktioner

std::string Time::to_string(bool us) const
{
    std::ostringstream oss {};
    int tmp_hour {hour};
    Time tmp_time {*this};
    bool ampm; //true = am, false = pm

    if (us)
    {   
        if (hour >= 12)
        {          
            if (!(tmp_time.is_am()))
            {
                tmp_hour -= 12;
            } 
            
            ampm = false;
        }
        else
        {
            if (hour == 0)
            {
                tmp_hour += 12;
            }

            ampm = true;        
        }    
    }

    oss << std::setfill('0') << std::setw(2) << tmp_hour << ':' 
    << std::setw(2) << minute << ':' << std::setw(2) << second;
    
    if (us)
    {
        if (ampm)
        {
            return oss.str() + "am";
        }
        else
        {
            return oss.str() + "pm";
        }
    }    
    else
    {
        return oss.str();
    }
}

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


void Time::log_time()
{
    std::cout << (*this).to_string() << std::endl;
}

void Time::check_time() const
{
    if (hour >= 24 or hour < 0)
    {
        throw std::out_of_range{"Timmar måster vara [0, 23]"};
    }
    else if (minute >= 60 or minute < 0)
    {
        throw std::out_of_range{"Minuter måste vara [0,59]"};
    }
    else if (second >= 60 or second < 0)
    {
        throw std::out_of_range{"Sekunder måste vara [0.59]"};
    }
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


//Strömmar

std::ostream& operator<<(std::ostream& os, Time const& rhs)
{
    os << rhs.to_string();
    return os;
}

std::istream& operator>>(std::istream& is, Time & rhs)
{
    char c;
    int tmp_hour, tmp_minute, tmp_second;
    is >> tmp_hour >> c >> tmp_minute >> c >> tmp_second;

    try
    {
        rhs = Time{tmp_hour, tmp_minute, tmp_second};
    }
    catch(std::exception& e)
    {
      is.setstate(std::ios_base::failbit);
    }
  return is;
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