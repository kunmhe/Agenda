#include <string>
#include <cstdio>
#include "Date.h"

Date::Date() {
  year_ = 1000;
  month_ = 1;
  day_ = 1;
  hour_ = 0;
  minute_ = 0;
}

Date::Date(int year, int month, int day, int hour, int minute) {
  setYear(year);
  setMonth(month);
  setDay(day);
  setHour(hour);
  setMinute(minute);
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year_ = year;
}

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getDay(void) const  {
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

bool Date::isValid(Date date) {
  if (date.year_ < 1000 || date.year_ > 9999 || date.month_ < 1
     || date.month_ > 12 || date.hour_ < 0 || date.hour_ > 23 ||
     date.minute_ < 0 || date.minute_ > 59 || date.day_ < 1 )
    return false;
  else if (date.month_ == 1 || date.month_ == 3 || date.month_ == 5
          || date.month_ == 7 ||  date.month_ == 8 ||  date.month_ == 10
          || date.month_ == 12 ) {
    if ( date.day_ > 31 )
      return false;
  } else if (date.month_ == 4 || date.month_ == 6 || date.month_ == 9
    || date.month_ == 11 ) {
      if ( date.day_ > 30 )
        return false;
    } else if (date.month_ == 2) {
        if ((date.year_% 4 == 0 && date.year_% 100 != 0)
            || date.year_ % 400 == 0) {
          if (date.day_ > 29)
            return false;
        } else if (date.day_ > 28) {
            return false;
          }
    }
    return true;
}

Date Date::stringToDate(std::string dateString) {
  int y, mo, d, h, mi;
  sscanf(dateString.c_str(), "%d-%d-%d/%d:%d", &y, &mo, &d, &h, &mi);
  return Date(y, mo, d, h, mi);
}

std::string Date::dateToString(Date date) {
  char outStr[30];
  snprintf(outStr, sizeof(outStr), "%04d-%02d-%02d/%02d:%02d",
           date.year_, date.month_, date.day_, date.hour_, date.minute_);
  return std::string(outStr);
}

Date &Date::operator=(const Date& date) {
  if (isValid(date)) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;
  }
  return *this;
}

bool Date::operator==(const Date& date) const {
  if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_
     && hour_ == date.hour_ && minute_ == date.hour_)
    return true;
  else
    return false;
}

bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) return true;
  else if (year_ < date.year_) return false;
  else if (year_ == date.year_) {
    if (month_ > date.month_ ) return true;
    else if (month_ < date.month_) return false;
    else if (month_ == date.month_) {
        if (day_ > date.day_ ) return true;
        else if (day_ < date.day_) return false;
        else if (day_ == date.day_) {
          if (hour_ > date.hour_ ) return true;
          else if (hour_ < date.hour_) return false;
          else if (hour_ == date.hour_) {
              if (minute_ > date.minute_ ) return true;
              else
                return false;
          }
        }
    }
  }
}

bool Date::operator<(const Date& date) const {
  if (*this == date || *this > date) return false;
  else
    return true;
}

bool Date::operator>=(const Date& date) const {
  if (*this < date) return false;
  else
    return true;
}

bool Date::operator<=(const Date& date) const {
  if (*this > date) return false;
  else
    return true;
}
