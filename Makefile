CPP = g++
%.o:%.cpp
	$(CPP) -o $@ -c $<

snake : main_snake.o keyboard-event.o
	$(CPP) $^ -o $@

keyboard-event.o : keyboard-event.cpp keyboard-event.h
main_snake.o : main_snake.cpp keyboard-event.h