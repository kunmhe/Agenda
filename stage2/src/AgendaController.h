#ifndef AGENDACONTROLLER_H
#define AGENDACONTROLLER_H

#include "AgendaService.h"

class AgendaController {
 public:
  AgendaController();
  void getOperation(void);
  void printBefore();
  void printAfter();

 private:
  void startAgenda(void);
  bool executeOperation(std::string op);
  void userLogIn(void);
  void userRegister(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> meetings);
  User *currentUser_;
  AgendaService agendaService_;
};

#endif
