VERSION = 0.1.0
VERSION_REPLACE = @@VERSION@@

BUILDDIR = build
OBJECTDIR = objects
SOURCEDIR = src

CXX = g++
CXXFLAGS = -O3 -Wall -Weffc++ -ansi -pedantic -std=c++17 -I$(SOURCEDIR) -c -fPIC -g
LDFLAGS = -shared -L$(SOURCEDIR) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_fontcache -lstdc++fs -Wl,-rpath,'$$ORIGIN'

LIBRARY = simpleui
OBJ = simpleui logger classes/animation classes/base classes/cleanup classes/frame classes/text classes/texture
OBJECTS = $(patsubst %, $(OBJECTDIR)/%.o, $(OBJ))

PREFIX = lib
SUFFIX = .so.$(VERSION)

all: $(LIBRARY)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	mkdir -p `dirname $@`
	sed -i 's/$(VERSION_REPLACE)/$(VERSION)/g' $^
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LIBRARY): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CXX) -o $(BUILDDIR)/$(PREFIX)$@$(SUFFIX) $^ $(LDFLAGS)

clean:
	rm -rf $(OBJECTDIR)
	rm -rf $(BUILDDIR)

remake: clean $(LIBRARY)

packer:
	cd packer
	make
