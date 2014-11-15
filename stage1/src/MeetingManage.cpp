#include <iostream>
#include <string>
#include <list>
#include "Meeting.h"
#include "MeetingManage.h"
#include "UserManage.h"

bool MeetingManage::instanceFlag_ = false;
MeetingManage *MeetingManage::instance_ = NULL;

MeetingManage::~MeetingManage() {
  if (instanceFlag_ == true)
    delete instance_;
}

MeetingManage::MeetingManage() {
}

MeetingManage *MeetingManage::getInstance() {
  if (instanceFlag_ == false) {
    instanceFlag_ = true;
    instance_ = new MeetingManage;
  }
  return instance_;
}

void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
  meetings_ = meetings;
}

std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
  return meetings_;
}

bool MeetingManage::addMeeting(std::string sponsor, std::string participator,
                               Date stime, Date etime, std::string title) {
  UserManage* u = UserManage::getInstance();
  if (!(*u).findUserByName(sponsor) || !(*u).findUserByName(participator)
     || stime > etime || !queryMeetingsByTime(sponsor, stime, etime).empty())
    return false;
        std::list<Meeting>::iterator it;
        for (it = meetings_.begin(); it != meetings_.end(); it++) {
          if ((*it).getTitle() == title)
            return false;
        }
  meetings_.push_back(Meeting(sponsor, participator, stime, etime, title));
  return true;
}

bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getSponsor() == userName && (*it).getTitle() == title) {
      meetings_.erase(it);
      return true;
    }
  }
    return false;
}

bool MeetingManage::deleteAllMeetings(std::string userName) {
  std::list<Meeting>::iterator it;
  int x = 0;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getSponsor() == userName) {
      meetings_.erase(it);
      it--;
      x = 1;
    }
  }
  if (x)
    return true;
  else
    return false;
}

bool MeetingManage::updateMeetingParticipator(std::string title,
                                              std::string newParticipator) {
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getTitle() == title)
      (*it).setParticipator(newParticipator);
    return true;
  }
  return false;
}

bool MeetingManage::updateMeetingStartDate(std::string title,
                                           Date newStartDate) {
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getTitle() == title)
      (*it).setStartDate(newStartDate);
    return true;
  }
  return false;
}

bool MeetingManage::updateMeetingEndDate(std::string title, Date newEndDate) {
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getTitle() == title)
      (*it).setEndDate(newEndDate);
    return true;
  }
  return false;
}

Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getTitle() == title)
      return &(*it);
  }
  return NULL;
}

std::list<Meeting> MeetingManage::queryMeetingsByTime(std::string userName,
                                                      Date stime, Date etime) {
  std::list<Meeting> allMeetings = listAllMeetings(userName);
  std::list<Meeting> queryMeetings;
  std::list<Meeting>::iterator it;
  for (it = allMeetings.begin(); it != allMeetings.end(); it++) {
    if ((*it).getStartDate() < stime && (*it).getEndDate() > etime)
      queryMeetings.push_back(*it);
  }
  return queryMeetings;
}

std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
  std::list<Meeting> allMeetings;
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getSponsor() == userName || (*it).getParticipator() == userName )
      allMeetings.push_back(*it);
  }
  return allMeetings;
}

std::list<Meeting> MeetingManage::listAllSponsorMeetings(std::string userName) {
  std::list<Meeting> allMeetings;
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getSponsor() == userName)
      allMeetings.push_back(*it);
  }
  return allMeetings;
}

std::list<Meeting> MeetingManage::listAllParticipateMeetings
                                                  (std::string userName) {
  std::list<Meeting> allMeetings;
  std::list<Meeting>::iterator it;
  for (it = meetings_.begin(); it != meetings_.end(); it++) {
    if ((*it).getParticipator() == userName )
      allMeetings.push_back(*it);
  }
  return allMeetings;
}
