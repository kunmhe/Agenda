#include <string>
#include "Date.h"
#include "Meeting.h"

Meeting::Meeting() {
  setSponsor("");
  setParticipator("");
  setTitle("");
}

Meeting::Meeting(std::string sponsor, std::string participator,
                Date startTime, Date endTime, std::string title) {
  setSponsor(sponsor);
  setParticipator(participator);
  setStartDate(startTime);
  setEndDate(endTime);
  setTitle(title);
}

std::string Meeting::getSponsor(void) {
  return sponsor_;
}

void Meeting::setSponsor(std::string sponsor) {
  sponsor_ = sponsor;
}

std::string Meeting::getParticipator(void) {
  return participator_;
}

void Meeting::setParticipator(std::string participator) {
  participator_ = participator;
}

Date Meeting::getStartDate(void) {
  return startDate_;
}

void Meeting::setStartDate(Date startTime) {
  startDate_ = startTime;
}

Date Meeting::getEndDate(void) {
  return endDate_;
}

void Meeting::setEndDate(Date endTime) {
  endDate_ = endTime;
}

std::string Meeting::getTitle(void) {
  return title_;
}

void Meeting::setTitle(std::string title) {
  title_ = title;
}
