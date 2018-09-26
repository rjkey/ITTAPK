# Defines which compiler to use.
CXX=g++

# The list of flags to pass to the compilation command.
CXXFLAGS=

ODIR=bin

DEPS = SharedPtr.h
SOURCES = main.cpp

OBJECTS=$(SOURCES: .cpp=.o)

EXECUTABLE = main

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS)


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(EXECUTABLE)
