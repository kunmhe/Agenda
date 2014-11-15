#include "User.h"
#include "Meeting.h"
#include "FileManage.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>

FileManage *FileManage::instance_ = NULL;
bool FileManage::instanceFlag_ = false;


FileManage::FileManage()
  : userFileName_("user.dat"), meetingFileName_("meeting.dat") {
}

FileManage::~FileManage() {
  if (instanceFlag_ == true)
    delete instance_;
}

FileManage *FileManage::getInstance(void) {
  if (instanceFlag_ == false) {
    instanceFlag_ = true;
    instance_ = new FileManage;
  }
  return instance_;
}

std::list<User> FileManage::readUsersFromFile(void) {
  std::ifstream read(userFileName_.c_str());
  std::list<User> users;
  if (read) {
  } else {
      std::string name, password, email, phone;
      while (read >> name >> password >> email >> phone) {
        users.push_back(User(name, password, email, phone));
      }
      read.close();
    }
  return users;
}

void FileManage::writeUsersToFile(std::list<User> users) {
  std::ofstream write(userFileName_.c_str());
  std::list<User>::iterator it;
  for (it = users.begin(); it != users.end(); it++) {
    write << (*it).getName() << " " << (*it).getPassword() << " "
          << (*it).getEmail() << " " << (*it).getPhone() << std::endl;
  }
  write.close();
}

std::list<Meeting> FileManage::readMeetingsFromFile(void) {
  std::ifstream read(meetingFileName_.c_str());
  std::list<Meeting> meetings;
  if (read) {
  } else {
      std::string sponsor, participator, stime, etime, title;
      while (read >> sponsor >> participator >> stime >> etime >> title) {
        meetings.push_back(Meeting(sponsor, participator,
                                   Date::stringToDate(stime),
                                   Date::stringToDate(etime), title));
      }
      read.close();
    }
  return meetings;
}

void FileManage::writeMeetingsToFile(std::list<Meeting> meetings) {
  std::ofstream write(meetingFileName_.c_str());
  std::list<Meeting>::iterator it;
  for (it = meetings.begin(); it != meetings.end(); it++) {
    write << (*it).getSponsor() << " " << (*it).getParticipator() << " "
          << Date::dateToString((*it).getStartDate())<< " "
          << Date::dateToString((*it).getEndDate()) << " "
          << (*it).getTitle() << std::endl;
  }
  write.close();
}
