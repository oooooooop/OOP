#OOP Big Homework

CPP      = g++
OBJ      = main.o database.o table.o content.o
BIN      = main
CXXFLAGS = --std=c++14
RM       = rm -f

all: $(BIN)

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

database.o: database.cpp
	$(CPP) -c database.cpp -o database.o $(CXXFLAGS)

table.o: table.cpp
	$(CPP) -c table.cpp -o table.o $(CXXFLAGS)

content.o: content.cpp
	$(CPP) -c content.cpp -o content.o $(CXXFLAGS)
