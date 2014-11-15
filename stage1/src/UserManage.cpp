#include <algorithm>
#include <string>
#include <list>
#include "User.h"
#include "UserManage.h"

bool UserManage::instanceFlag_ = false;
UserManage *UserManage::instance_ = NULL;

UserManage::~UserManage() {
  if (instanceFlag_ == true)
    delete instance_;
}

UserManage::UserManage() {
}

UserManage *UserManage::getInstance(void) {
  if (instanceFlag_ == false) {
    instanceFlag_ = true;
    instance_ = new UserManage();
  }
  return instance_;
}

void UserManage::initUsersList(std::list<User> users) {
  users_ = users;
}

std::list<User> UserManage::acquireUsersList(void) {
  return users_;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
                            std::string userEmail, std::string userPhone) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == userName )
      return false;
  }
  users_.push_back(User(userName, userPassword, userEmail, userPhone));
  return true;
}

bool UserManage::deleteUser(User user) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == user.getName()) {
      users_.erase(it);
      it--;
      return true;
    }
  }
  return false;
}

bool UserManage::updateUserPassword(User user, std::string newPassword) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == user.getName()) {
      (*it).setPassword(newPassword);
      return true;
    }
  }
  return false;
}

bool UserManage::updateUserEmail(User user, std::string newEmail) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == user.getName()) {
      (*it).setEmail(newEmail);
      return true;
    }
  }
  return false;
}

bool UserManage::updateUserPhone(User user, std::string newPhone) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == user.getName()) {
      (*it).setPhone(newPhone);
      return true;
    }
  }
  return false;
}

User* UserManage::findUserByName(std::string userName) {
  std::list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    if ((*it).getName() == userName )
      return &(*it);
  }
  return NULL;
}

std::list<User> UserManage::listAllUsers(void) {
  return users_;
}
