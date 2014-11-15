
agenda:Date.o User.o Meeting.o UserManage.o MeetingManage.o AgendaService.o FileManage.o
	g++ -o agenda -I~/gtest-1.6.0/include Date.o User.o Meeting.o UserManage.o MeetingManage.o  AgendaService.o FileManage.o gtest.cpp -lgtest -lpthread

Date.o:Date.h Date.cpp
	g++ -c Date.cpp

User.o:User.h User.cpp
	g++ -c User.cpp

Meeting.o:Meeting.h Meeting.cpp
	g++ -c Meeting.cpp

UserManage.o:UserManage.h UserManage.cpp
	g++ -c UserManage.cpp

MeetingManage.o:MeetingManage.h MeetingManage.cpp
	g++ -c MeetingManage.cpp

AgendaService.o:AgendaService.h AgendaService.cpp
	g++ -c AgendaService.cpp

FileManage.o:FileManage.h FileManage.cpp
	g++ -c FileManage.cpp

clean:
	rm *.o agenda
