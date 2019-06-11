BUILDDIR = build
OBJECTDIR = objects
SOURCEDIR = src

CXX = g++
CXXFLAGS = -O3 -Wall -Weffc++ -ansi -pedantic -std=c++17 -I$(SOURCEDIR) -c -fPIC -g
LDFLAGS = -shared -L$(SOURCEDIR) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_fontcache -lstdc++fs -Wl,-rpath,'$$ORIGIN'

LIBRARY = simpleui
OBJ = simpleui simpleui_logger classes/animation classes/base classes/cleanup classes/frame classes/text classes/texture
OBJECTS = $(patsubst %, $(OBJECTDIR)/%.o, $(OBJ))

BINARIES = /usr/lib/x86_64-linux-gnu/
HEADERS = /usr/include/

SHARED = lib$(LIBRARY).so
STATIC = lib$(LIBRARY).a

all: $(LIBRARY)

install: $(all)
	cp -f $(BUILDDIR)/* $(BINARIES)
	cp -f $(SOURCEDIR)/*.h $(HEADERS)

uninstall:
	rm -f $(SDL_BINARIES)$(PREFIX)$(LIBRARY)*
	rm -f $(SDL_HEADERS)simpleui.h
	rm -f $(SDL_HEADERS)simpleui_log.h

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
