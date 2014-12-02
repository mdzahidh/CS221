HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

all: driver

driver: $(OBJS)
	g++ -O3 -std=c++11 -o $@ $^

%.o: %.cpp $(HEADERS)
	g++ -O3 -I. -std=c++11 -c -o $@ $<
