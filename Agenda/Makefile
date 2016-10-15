bin/main: build/Agenda.o build/AgendaUI.o build/AgendaService.o build/Storage.o build/Date.o build/User.o build/Meeting.o
	@mkdir -p bin
	g++ -std=c++11 -g -I./include build/Agenda.o build/AgendaUI.o build/AgendaService.o build/Storage.o build/Date.o build/User.o build/Meeting.o -o $@

build/Agenda.o: src/Agenda.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/Agenda.cpp -c -o build/Agenda.o
	
build/AgendaUI.o: src/AgendaUI.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/AgendaUI.cpp -c -o build/AgendaUI.o
	
build/AgendaService.o: src/AgendaService.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/AgendaService.cpp -c -o build/AgendaService.o
	
build/Storage.o: src/Storage.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/Storage.cpp -c -o build/Storage.o
	
build/User.o: src/User.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/User.cpp -c -o build/User.o
	
build/Meeting.o: src/Meeting.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/Meeting.cpp -c -o build/Meeting.o
	
build/Date.o: src/Date.cpp
	@mkdir -p build
	g++ -std=c++11 -g -I./include src/Date.cpp -c -o build/Date.o
	
clean:
	@rm -rf build
	@rm -rf bin
