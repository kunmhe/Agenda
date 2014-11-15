#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
  User();
  User(std::string userName, std::string userPassword,
       std::string userEmail, std::string userPhone);
  std::string getName(void);
  void setName(std::string name);
  std::string getPassword(void);
  void setPassword(std::string password);
  std::string getEmail(void);
  void setEmail(std::string email);
  std::string getPhone(void);
  void setPhone(std::string phone);

 private:
  std::string name_;
  std::string password_;
  std::string email_;
  std::string phone_;
};

#endif
