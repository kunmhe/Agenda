#include "AgendaService.h"
#include "gtest/gtest.h"
namespace {
    AgendaService hk;
  ///////////////////////////////////////////////test userRegister
    TEST(userRegister, registerUser){
    EXPECT_TRUE(hk.userRegister("hekun", "suzuran", "qq", "123"));
    }
    TEST(userRegister, nameTaken){
    EXPECT_TRUE(!(hk.userRegister("hekun", "suzu", "sina", "987")));
    }
  ///////////////////////////////////////////////test createMeeting
    TEST(createMeeting, createMeeting){
    hk.userRegister("user1","123","qq","12345678");
    hk.userRegister("user2","123","sina","12345678");
    EXPECT_TRUE(hk.createMeeting("user1","aa",
"user2","2013-11-30/11:30","2013-11-30/11:40"));
    }
    TEST(createMeeting, invalidTime){
    EXPECT_FALSE(hk.createMeeting("user1","cc",
"user2","2013-11-30/12:30","2013-11-40/65:40"));
    }
    TEST(createMeeting, invalidParticipator){
    EXPECT_FALSE(hk.createMeeting("user1","bb",
"user3","2013-11-30/11:30","2013-11-30/11:40"));
    }
    TEST(createMeeting, sTimeLargerThaneTime){
    EXPECT_FALSE(hk.createMeeting("user1","dd",
"user2","2013-11-30/16:40","2013-11-30/12:40"));
    }
    TEST(createMeeting, duplicateMeetingName){
    EXPECT_FALSE(hk.createMeeting("user1","aa",
"user2","2013-11-30/12:30","2013-11-30/12:40"));
    }
  ////////////////////////////////////////////////test deleteMeeting
    TEST(deleteMeeting, deleteMeeting){
    hk.createMeeting("user1","aa",
"user2","2013-11-30/11:30","2013-11-30/11:40");
    EXPECT_TRUE(hk.deleteMeeting("user1","aa"));
    EXPECT_TRUE(hk.meetingQuery("aa") == NULL);
    }
    TEST(deleteMeeting, titleNotFound){
    hk.createMeeting("user1","aa","user2",
"2013-11-11/11:11","2013-11-11/11:15");
    EXPECT_FALSE(hk.deleteMeeting("user1","Afghanistan"));
    EXPECT_TRUE(hk.meetingQuery("aa") != NULL);
    }
    TEST(deleteMeeting, invalidSponsor){
    hk.createMeeting("user1","aa","user2",
"2013-11-11/11:30","2013-11-30/11:40");
    EXPECT_FALSE(hk.deleteMeeting("user2","aa"));
    EXPECT_TRUE(hk.meetingQuery("aa") != NULL);
    }
}

int main(int argc, char **argv) {
    hk.userRegister("user1","aa","bb","cc");
    hk.userRegister("user2","aa","bb","cc");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

