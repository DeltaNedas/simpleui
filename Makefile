MAJOR = 0
MINOR = 1
PATCH = 1
VERSION = $(MAJOR).$(MINOR).$(PATCH)
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

SHARED = lib$(LIBRARY).so
SHARED_MAJOR = $(SHARED).$(MAJOR)
SHARED_MINOR = $(SHARED).$(MAJOR).$(MINOR)
SHARED_PATCH = $(SHARED).$(VERSION)
STATIC = lib$(LIBRARY).a

all: $(LIBRARY)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	mkdir -p $(shell dirname $@)
	sed -i 's/$(VERSION_REPLACE)/$(VERSION)/g' $^ # Replace @@VERSION@@ with the version.
	$(CXX) $(CXXFLAGS) -o $@ $^
	sed -i 's/$(VERSION)/$(VERSION_REPLACE)/g' $^ # Replace the version with @@VERSION@@ to not break it.

$(LIBRARY): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CXX) -o $(BUILDDIR)/$(SHARED_PATCH) $^ $(LDFLAGS)
	ar rcs $(BUILDDIR)/$(STATIC) $^

clean:
	rm -rf $(OBJECTDIR)
	rm -rf $(BUILDDIR)

remake: clean $(LIBRARY)

packer:
	cd packer
	make
