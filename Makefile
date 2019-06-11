BUILDDIR = build
OBJECTDIR = objects
SOURCEDIR = src

CXX = g++
CXXFLAGS = -O3 -Wall -Weffc++ -ansi -pedantic -std=c++17 -I$(SOURCEDIR) -c -fPIC -g
LDFLAGS = -shared -L$(SOURCEDIR) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_fontcache -lstdc++fs -Wl,-rpath,'$$ORIGIN'

LIBRARY = simpleui
OBJ = simpleui logger classes/animation classes/base classes/cleanup classes/frame classes/text classes/texture
OBJECTS = $(patsubst %, $(OBJECTDIR)/%.o, $(OBJ))

SHARED = lib$(LIBRARY).so
STATIC = lib$(LIBRARY).a

all: $(LIBRARY)

install: $(all)
	cp -f $(BUILDDIR)/* $(SDL_BINARIES)
	cp -f $(SOURCEDIR)/$(LIBRARY).h $(SDL_HEADERS)

uninstall:
	rm -f $(SDL_BINARIES)$(PREFIX)$(LIBRARY)*
	rm -f $(SDL_HEADERS)SDL_fontcache.h

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LIBRARY): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CXX) -o $(BUILDDIR)/$(SHARED) $^ $(LDFLAGS)
	ar rcs $(BUILDDIR)/$(STATIC) $^

clean:
	rm -rf $(OBJECTDIR)
	rm -rf $(BUILDDIR)

remake: clean $(LIBRARY)
