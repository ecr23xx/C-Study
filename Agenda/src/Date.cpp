#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <string>
// #include <initializer_list>
using namespace std;

Date::Date() {
  m_year = 0;
  m_month = 0;
  m_day = 0;
  m_hour = 0;
  m_minute = 0;
}

// ok
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
  m_year = t_year;
  m_month = t_month;
  m_day = t_day;
  m_hour = t_hour;
  m_minute = t_minute;
}

Date::Date(std::string dateString) { (*this) = stringToDate(dateString); }

bool isSpyear(int year) {
  if ((year % 4 == 0) && (year % 100 != 0))
    return (true);
  if ((year % 400 == 0))
    return (true);
  return (false);
}

bool isSpmonth(int month) {
  if ((month % 2) == 1 && month < 8)
    return (true);
  if ((month % 2) == 0 && month >= 8)
    return (true);
  return (false);
}

string tostring(int a) {
  stringstream ss;
  ss << a;
  return ss.str();
}

int Date::getYear(void) const { return m_year; }

void Date::setYear(const int t_year) { m_year = t_year; }

int Date::getMonth(void) const { return m_month; }

void Date::setMonth(const int t_month) { m_month = t_month; }

int Date::getDay(void) const { return m_day; }

void Date::setDay(const int t_day) { m_day = t_day; }

int Date::getHour(void) const { return m_hour; }

void Date::setHour(const int t_hour) { m_hour = t_hour; }

int Date::getMinute(void) const { return m_minute; }

void Date::setMinute(const int t_minute) { m_minute = t_minute; }

bool Date::isValid(const Date t_date) {
  if (t_date.getYear() > 9999 || t_date.getYear() < 1000)
    return (false);
  if (t_date.getMonth() > 12 || t_date.getMonth() <= 0)
    return (false);
  if (t_date.getDay() > 31 || t_date.getDay() <= 0)
    return (false);
  if (t_date.getHour() >= 24 || t_date.getHour() < 0)
    return (false);
  if (t_date.getMinute() >= 60 || t_date.getMinute() < 0)
    return (false);

  if (t_date.getMonth() == 2) {
    if (isSpyear(t_date.getYear())) {
      if (t_date.getDay() > 29)
        return (false);
    } else {
      if (t_date.getDay() > 28)
        return (false);
    }
  } else if (isSpmonth(t_date.getMonth()) == (false)) {
    if (t_date.getDay() > 30)
      return (false);
  }
  return (true);
}

Date Date::stringToDate(const std::string t_dateString) {
  int flag = 1;
  for (int i = 0; i < 4; i++) {
    if (t_dateString[i] > '9' || t_dateString[i] < '0')
      flag = 0;
  }
  if (t_dateString[4] != '-')
    flag = 0;
  for (int i = 5; i < 7; i++) {
    if (t_dateString[i] > '9' || t_dateString[i] < '0')
      flag = 0;
  }
  if (t_dateString[7] != '-')
    flag = 0;
  for (int i = 8; i < 10; i++) {
    if (t_dateString[i] > '9' || t_dateString[i] < '0')
      flag = 0;
  }
  if (t_dateString[10] != '/')
    flag = 0;
  for (int i = 11; i < 13; i++) {
    if (t_dateString[i] > '9' || t_dateString[i] < '0')
      flag = 0;
  }
  if (t_dateString[13] != ':')
    flag = 0;
  if (t_dateString.size() != 16)
    flag = 0;

  if (flag == 0)
    return Date(0, 0, 0, 0, 0);

  int t_year, t_month, t_day, t_hour, t_minute;

  t_year = (t_dateString[0] - '0') * 1000 + (t_dateString[1] - '0') * 100 +
           (t_dateString[2] - '0') * 10 + (t_dateString[3] - '0');
  t_month = (t_dateString[5] - '0') * 10 + (t_dateString[6] - '0');
  t_day = (t_dateString[8] - '0') * 10 + (t_dateString[9] - '0');
  t_hour = (t_dateString[11] - '0') * 10 + (t_dateString[12] - '0');
  t_minute = (t_dateString[14] - '0') * 10 + (t_dateString[15] - '0');

  Date ans(t_year, t_month, t_day, t_hour, t_minute);
  if (isValid(ans) == (false))
    return Date(0, 0, 0, 0, 0);
  else
    return ans;
}

std::string Date::dateToString(Date t_date) {
  if (isValid(t_date) == (false)) {
    return string("0000-00-00/00:00");
  } else {
    string result;
    result += tostring(t_date.getYear());

    result += "-";

    if (t_date.getMonth() < 10)
      result += "0";
    result += tostring(t_date.getMonth());

    result += "-";

    if (t_date.getDay() < 10)
      result += "0";
    result += tostring(t_date.getDay());

    result += "/";

    if (t_date.getHour() < 10)
      result += "0";
    result += tostring(t_date.getHour());

    result += ":";

    if (t_date.getMinute() < 10)
      result += "0";
    result += tostring(t_date.getMinute());

    return result;
  }
}

// ok
Date &Date::operator=(const Date &t_date) {
  m_year = t_date.getYear();
  m_month = t_date.getMonth();
  m_day = t_date.getDay();
  m_hour = t_date.getHour();
  m_minute = t_date.getMinute();
  return (*this);
}

bool Date::operator==(const Date &t_date) const {
  if (m_year != t_date.getYear())
    return (false);
  if (m_month != t_date.getMonth())
    return (false);
  if (m_day != t_date.getDay())
    return (false);
  if (m_hour != t_date.getHour())
    return (false);
  if (m_minute != t_date.getMinute())
    return (false);

  return (true);
}

bool Date::operator>(const Date &t_date) const {
  if ((*this) <= (t_date))
    return (false);
  else
    return (true);
}

bool Date::operator<(const Date &t_date) const {
  if ((*this) >= (t_date))
    return (false);
  else
    return (true);
}

bool Date::operator>=(const Date &t_date) const {
  if (m_year < t_date.getYear()) {
    return (false);
  } else if (m_year == t_date.getYear()) {
    if (m_month < t_date.getMonth()) {
      return (false);
    } else if (m_month == t_date.getMonth()) {
      if (m_day < t_date.getDay()) {
        return (false);
      } else if (m_day == t_date.getDay()) {
        if (m_hour < t_date.getHour()) {
          return (false);
        } else if (m_hour == t_date.getHour()) {
          if (m_minute < t_date.getMinute()) {
            return (false);
          }
        }
      }
    }
  }
  return (true);
}

bool Date::operator<=(const Date &t_date) const {
  if (m_year > t_date.getYear()) {
    return (false);
  } else if (m_year == t_date.getYear()) {
    if (m_month > t_date.getMonth()) {
      return (false);
    } else if (m_month == t_date.getMonth()) {
      if (m_day > t_date.getDay()) {
        return (false);
      } else if (m_day == t_date.getDay()) {
        if (m_hour > t_date.getHour()) {
          return (false);
        } else if (m_hour == t_date.getHour()) {
          if (m_minute > t_date.getMinute()) {
            return (false);
          }
        }
      }
    }
  }
  return (true);
}
