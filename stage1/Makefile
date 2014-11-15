CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpthread -lgtest
SOURCES=User.cpp\
        Meeting.cpp\
        UserManage.cpp\
        MeetingManage.cpp\
        Date.cpp\
        gtest.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
