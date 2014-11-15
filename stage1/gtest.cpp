#include "gtest/gtest.h"
#include "UserManage.h"
#include "MeetingManage.h"

namespace {

TEST(Date, testDate) {
  Date d1;
  EXPECT_TRUE(Date::isValid(d1));
  Date d2(1000, 01, 01, 0, 0);
  EXPECT_TRUE(Date::isValid(d2));
  EXPECT_EQ(d1, d2);

  Date d3(9999, 12, 31, 23, 59);
  EXPECT_TRUE(Date::isValid(d3));

  Date d4(2003, 2, 29, 1, 1);
  EXPECT_TRUE(!Date::isValid(d4));

  Date d5(2000, 2, 29, 1, 1);
  EXPECT_TRUE(Date::isValid(d5));

  EXPECT_TRUE(d2 < d3);
  EXPECT_TRUE(d4 > d5);
  EXPECT_TRUE(d1 >= d2);

  EXPECT_EQ(d4, Date::stringToDate("2003-02-29/01:01"));

  EXPECT_EQ("2003-02-29/01:01", Date::dateToString(d4));

}

UserManage* uM = UserManage::getInstance();

TEST(UserManage, createUser) {
  EXPECT_TRUE(uM->createUser("a", "a", "a", "a"));
  EXPECT_TRUE(uM->createUser("b", "b", "b", "b"));
  EXPECT_TRUE(uM->createUser("c", "c", "c", "c"));
  EXPECT_TRUE(uM->createUser("d", "d", "d", "d"));
  EXPECT_TRUE(uM->createUser("e", "e", "e", "e"));
  EXPECT_FALSE(uM->createUser("e", "e", "e", "e"));
}

TEST(UserManage, acquireUsersList) {
  std::list<User> newList = uM->acquireUsersList();
  EXPECT_EQ(newList.front().getName(), "a");
  EXPECT_EQ(newList.back().getName(), "e");
}

TEST(UserManage, deleteUser) {
  uM->deleteUser(User("a", "a", "a", "a"));
  EXPECT_EQ(uM->acquireUsersList().front().getName(), "b");
}

TEST(UserManage, findUserByName) {
  EXPECT_FALSE(uM->findUserByName("a"));
  EXPECT_TRUE(uM->findUserByName("b"));
}

TEST(UserManage, updateUserInfo) {
  uM->updateUserPassword(User("b", "b", "b", "b"), "bb");
  EXPECT_EQ(uM->findUserByName("b")->getPassword(), "bb");
  uM->updateUserEmail(User("c", "c", "c", "c"), "cc");
  uM->updateUserPhone(User("d", "d", "d", "d"), "dd");

  EXPECT_EQ(uM->findUserByName("c")->getEmail(), "cc");
  EXPECT_EQ(uM->findUserByName("d")->getPhone(), "dd");
}

MeetingManage* mM = MeetingManage::getInstance();

TEST(MeetingManage, addMeeting) {
  EXPECT_FALSE(mM->addMeeting("a", "b", Date(), Date(), "WrongCase1"));
  EXPECT_FALSE(mM->addMeeting("b", "a", Date(), Date(), "WrongCase2"));
  EXPECT_FALSE(mM->addMeeting("b", "c", Date(1999, 12, 2, 12, 12),
               Date(1999, 12, 2, 12, 11), "WrongCase3"));
  EXPECT_TRUE(mM->addMeeting("b", "c", Date(1999, 12, 2, 12, 13),
              Date(1999, 12, 2, 12, 13), "RightCase1"));
  EXPECT_TRUE(mM->addMeeting("c", "d", Date(1999, 12, 2, 12, 14),
              Date(1999, 12, 2, 12, 14), "RightCase2"));
  EXPECT_TRUE(mM->addMeeting("d", "e", Date(1999, 12, 2, 12, 15),
              Date(1999, 12, 2, 12, 15), "RightCase3"));
  EXPECT_TRUE(mM->addMeeting("e", "b", Date(1999, 12, 2, 12, 16),
              Date(1999, 12, 2, 12, 16), "RightCase4"));
  EXPECT_TRUE(mM->addMeeting("b", "c", Date(1999, 12, 2, 12, 17),
              Date(1999, 12, 2, 12, 17), "RightCase5"));
  EXPECT_FALSE(mM->addMeeting("c", "d", Date(), Date(), "RightCase1"));
}

TEST(MeetingManage, queryTest) {
  EXPECT_EQ("b", mM->queryMeetingByTitle("RightCase1")->getSponsor());
  EXPECT_EQ("b", mM->queryMeetingByTitle("RightCase4")->getParticipator());
}

TEST(MeetingManage, deleteMeeting) {
  EXPECT_FALSE(mM->deleteMeeting("c", "RightCase5"));
  EXPECT_TRUE(mM->deleteMeeting("b", "RightCase5"));
  EXPECT_EQ(mM->acquireMeetingsList().size(), 4);
  EXPECT_TRUE(mM->deleteAllMeetings("b"));
  EXPECT_EQ(mM->acquireMeetingsList().size(), 3);
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

