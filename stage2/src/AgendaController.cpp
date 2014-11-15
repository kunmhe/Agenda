#include "AgendaController.h"
#include <iostream>
#include <string>
#include <list>

AgendaController::AgendaController()
  : currentUser_(NULL) {
  startAgenda();
}

void AgendaController::getOperation(void) {
  if (currentUser_ == NULL) {
    printBefore();
  } else {
    printAfter();
  }
  std::string op;
  std::cin >> op;
  executeOperation(op);
}

void AgendaController::startAgenda(void) {
  agendaService_.startAgenda();
}

bool AgendaController::executeOperation(std::string op) {
  if (currentUser_ != NULL) {
    if (op == "o") {
      userLogOut();
    } else if (op == "dc") {
      deleteUser();
    } else if (op == "lu") {
      listAllUsers();
    } else if (op == "cm") {
      createMeeting();
    } else if (op == "la") {
      listAllMeetings();
    } else if (op == "las") {
      listAllSponsorMeetings();
    } else if (op == "lap") {
      listAllParticipateMeetings();
    } else if (op == "qm") {
      queryMeetingByTitle();
    } else if (op == "qt") {
      queryMeetingByTimeInterval();
    } else if (op == "dm") {
      deleteMeetingByTitle();
    } else if (op == "da") {
      deleteAllMeetings();
    } else {
      getOperation();
    }
  } else {
      if (op == "l") {
        userLogIn();
      } else if (op == "r") {
        userRegister();
      } else if (op == "q") {
        quitAgenda();
      } else {
        getOperation();
      }
    }
}

void AgendaController::userLogIn(void) {
  std::cout << "[log in] [user name] [password]\n"
            << "[log in] ";
  std::string name, password;
  std::cin >> name >> password;
  if (agendaService_.userLogIn(name, password)) {
    std::cout << "[log in] succeed!" << std::endl << std::endl;
    currentUser_ = agendaService_.userLogIn(name, password);
    getOperation();
  } else {
    std::cout << "[error] log in fail!" << std::endl << std::endl;
    currentUser_ = agendaService_.userLogIn(name, password);
    getOperation();
  }
}

void AgendaController::userRegister(void) {
  std::cout << "[register] [user name] [password] [email] [phone]" << std::endl;
  std::cout << "[register] ";
  std::string name, password, email, phone;
  std::cin >> name >> password >> email >> phone;
  if (agendaService_.userRegister(name, password, email, phone)) {
    std::cout << "[register] succeed!" << std::endl << std::endl;
    getOperation();
  } else {
    std::cout << "[error] register fail!"
              << std::endl << std::endl;
    getOperation();
  }
}

void AgendaController::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaController::userLogOut(void) {
  currentUser_ = NULL;
  getOperation();
}

void AgendaController::deleteUser(void) {
  if (agendaService_.deleteUser(*currentUser_)) {
    std::cout << "[delete agenda account] succeed!"
              << std::endl << std::endl;
    currentUser_ = NULL;
    getOperation();
  } else {
    std::cout << "[error] delete agenda account fail!"
              << std::endl << std::endl;
    getOperation();
  }
}

void AgendaController::listAllUsers(void) {
  std::cout << "[list all users]" << std::endl << std::endl;
  std::cout << "name       email       phone" << std::endl;
  std::list<User>::iterator it;
  for (it = agendaService_.listAllUsers().begin();
       it != agendaService_.listAllUsers().end();
       it++) {
    std::cout << (*it).getName() << "       " << (*it).getEmail()
              << "       " << (*it).getPhone() << std::endl;
  }
  getOperation();
}

void AgendaController::createMeeting(void) {
  std::cout << "[create meeting] "
            << "[title] [participator] [start time(yyyy-mm-dd/hh:mm)]"
            << " [end time(yyyy-mm-dd/hh:mm)]\n"
            << "[create meeting] ";
  std::string title, participator, stime, etime;
  std::cin >> title >> participator >> stime >> etime;
  if (!(agendaService_.createMeeting((*currentUser_).getName(),
                                     title, participator, stime, etime))) {
    std::cout << "[error] create meeting fail!" << std::endl << std::endl;
    getOperation();
  } else {
    std::cout << "[create meeting] succeed!" << std::endl << std::endl;
    getOperation();
  }
}

void AgendaController::listAllMeetings(void) {
  std::cout << "[list all meetings]" << std::endl << std::endl;
  std::cout << "title        sponsor        participator        "
            << "start time        end time" << std::endl;
  printMeetings(agendaService_.listAllMeetings((*currentUser_).getName()));
  getOperation();
}

void AgendaController::listAllSponsorMeetings(void) {
  std::cout << "[list all sponsor meetings]" << std::endl << std::endl;
  std::cout << "title        sponsor        participator        "
            << "start time        end time" << std::endl;
  printMeetings(agendaService_.listAllSponsorMeetings
                            ((*currentUser_).getName()));
  getOperation();
}

void AgendaController::listAllParticipateMeetings(void) {
  std::cout << "[list all participator meetings]" << std::endl << std::endl;
  std::cout << "title        sponsor        participator        "
            << "start time        end time" << std::endl;
  printMeetings(agendaService_.listAllParticipateMeetings
                             ((*currentUser_).getName()));
  getOperation();
}

void AgendaController::queryMeetingByTitle(void) {
  std::cout << "[query meeting] [title]:" << std::endl;
  std::cout << "[query meeting] ";
  std::string title;
  std::cin >> title;
  std::cout << "title        sponsor        participator        "
            << "start time        end time" << std::endl;
  Meeting* p;
  p = agendaService_.meetingQuery(title);
  std::string s, e;
  s = Date::dateToString((*p).getStartDate());
  e = Date::dateToString((*p).getEndDate());
  std::cout << (*p).getTitle() << "        "
            << (*p).getSponsor() << "        "
            << (*p).getParticipator() << "        "
            << s << "        " << e
            << std::endl << std::endl;
  getOperation();
}

void AgendaController::queryMeetingByTimeInterval(void) {
  std::cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)]"
            << " [end time(yyyy-mm-dd/hh:mm)]"  << std::endl
            << "[query meeting] ";
  std::string s, e;
  std::cin >> s >> e;
  std::cout << "title        sponsor        participator        "
            << "start time        end time" << std::endl;
  printMeetings(agendaService_.meetingQuery((*currentUser_).getName(),
                                               s , e));
  getOperation();
}

void AgendaController::deleteMeetingByTitle(void) {
  std::cout << "[delete meeting] [title]" << std::endl
            << "[delete meeting] ";
  std::string title;
  std::cin >> title;
  std::cout << std::endl;
  if (agendaService_.deleteMeeting((*currentUser_).getName(), title))
    std::cout << "[delete meeting by title] succeed!" << std::endl
                                                      << std::endl;
  else
    std::cout << "[error] delete meeting fail!" << std::endl
                                                << std::endl;
  getOperation();
}

void AgendaController::deleteAllMeetings(void) {
  if (!(agendaService_.deleteAllMeetings((*currentUser_).getName()))) {
    std::cout << "[error] delete meeting fail!" << std::endl
                                                << std::endl;
    } else {
    std::cout << "[delete all meetings] succeed!" << std::endl
                                                  << std::endl;
    }
  getOperation();
}

void AgendaController::printMeetings(std::list<Meeting> meetings) {
  std::list<Meeting>::iterator it;
  for (it = meetings.begin(); it != meetings.end(); it++) {
    std::cout << (*it).getTitle().c_str() << "        "
              << (*it).getSponsor().c_str() << "        "
              << (*it).getParticipator().c_str() << "        "
              << Date::dateToString((*it).getStartDate()) << "        "
              << Date::dateToString((*it).getEndDate())
              << std::endl;
  }
}

void AgendaController::printBefore() {
  std::cout << "---------------------------------" << " Agenda "
            << "---------------------------------" << std::endl;
  std::cout << "Action::" <<  std::endl
            << " l   - log in Agenda by user name and password" <<  std::endl
            << " r   - register an Agenda account" <<  std::endl
            << " q   - quit Agenda" <<  std::endl;
  std::cout << "-----------------------------------------"
            << "---------------------------------"
            << std::endl << std::endl;
  std::cout << "Agenda : ~$ ";
}

void AgendaController::printAfter() {
  std::cout << "---------------------------------" << " Agenda "
            << "---------------------------------" << std::endl;
  std::cout << "Action::\n"
            << " o   - log out Agenda\n"
            << " dc  - delete Agenda account\n"
            << " lu  - list all Agenda users\n"
            << " cm  - create a meeting\n"
            << " la  - list all meetings\n"
            << " las - list all sponsor meetings\n"
            << " lap - list all participate meetings\n"
            << " qm  - query meeting by title\n"
            << " qt  - query meeting by time interval\n"
            << " dm  - delete meeting by title\n"
            << " da  - delete all meetings\n";
  std::cout << "-----------------------------------------"
            << "---------------------------------"
            << std::endl << std::endl;
  std::cout << "Agenda@" << currentUser_->getName() << " : # ";
}
