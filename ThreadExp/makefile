CFLAGS = -std=c++20

src = $(wildcard *.cpp)
target = $(patsubst %.cpp, out/%.out, $(src))

out/%.out:%.cpp
	g++ $^ -o $@ $(CFLAGS) 


all:$(target)
	
.PHONY: clean 
clean:
	rm out/*
