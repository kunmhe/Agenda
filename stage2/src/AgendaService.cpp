#include <list>
#include <string>
#include "AgendaService.h"

AgendaService::AgendaService() {
  userManage_ = UserManage::getInstance();
  meetingManage_ = MeetingManage::getInstance();
  fileManage_ = FileManage::getInstance();
}

User* AgendaService::userLogIn(std::string userName, std::string password) {
  if ((*userManage_).findUserByName(userName)) {
    if (userManage_->findUserByName(userName)->getPassword() == password) {
      return userManage_->findUserByName(userName);
    }
  }
  return NULL;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
    return userManage_->createUser(userName, password, email, phone);
}

bool AgendaService::deleteUser(User user) {
    return userManage_->deleteUser(user);
}

std::list<User> AgendaService::listAllUsers(void) {
  return userManage_->listAllUsers();
}

bool AgendaService::createMeeting(std::string userName, std::string title,
  std::string participator, std::string startDate, std::string endDate) {
  return meetingManage_->addMeeting(userName,  participator,
    Date::stringToDate(startDate), Date::stringToDate(endDate), title);
}

Meeting* AgendaService::meetingQuery(std::string title) {
  return meetingManage_->queryMeetingByTitle(title);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                         std::string startDate, std::string endDate) {
  return meetingManage_->queryMeetingsByTime(userName,
    Date::stringToDate(startDate), Date::stringToDate(endDate));
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings
                                  (std::string userName) {
  return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  return meetingManage_->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  return meetingManage_->deleteAllMeetings(userName);
}

void AgendaService::startAgenda(void) {
  std::list<User> users_ = fileManage_->readUsersFromFile();
  userManage_->initUsersList(users_);

  std::list<Meeting> meetings_ = fileManage_->readMeetingsFromFile();
  meetingManage_->initMeetingsList(meetings_);
}

void AgendaService::quitAgenda(void) {
  std::list<User> users_ = userManage_->acquireUsersList();
  fileManage_->writeUsersToFile(users_);

  std::list<Meeting> meetings_ = meetingManage_->acquireMeetingsList();
  fileManage_->writeMeetingsToFile(meetings_);
}
