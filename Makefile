PROGNAME = code
ODIR = build
SDIR = src
IDIR = include
INCLUDES = -I./$(IDIR)
_OBJECTS = main.o Graph.o
OBJECTS = $(patsubst %, $(ODIR)/%,$(_OBJECTS))
CFLAGS = -Wall -Wextra -O3 -std=c++11 -pedantic

all: $(OBJECTS)
	@mkdir -p bin
	g++ $(CFLAGS) -o bin/$(PROGNAME) $(OBJECTS) $(INCLUDES)

$(ODIR)/%.o: $(SDIR)/%.cpp $(IDIR)/*.h
	@mkdir -p $(ODIR)
	g++ -c $(CFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	rm -f build/*.o core
