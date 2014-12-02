HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

all: driver

driver: $(OBJS)
	g++ -I./ -O3 -std=c++11 -o $@ $^

%.o: %.cpp $(HEADERS)
	g++ -I./ -O3 -std=c++11 -c -o $@ $<
