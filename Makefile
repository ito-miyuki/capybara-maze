# SMFL Makefile by github.com/doxakis1

# SFMLのディレクトリをHomebrewのインストールパスに設定
SFML_DIRECTORY := /usr/local/opt/sfml

COMPILER       := g++
NAME           := smfl_executable
COMPILER_FLAGS := -O3 -std=c++17
INCLUDES       := -I./src -I$(SFML_DIRECTORY)/include
LINKER_FLAGS   := -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIRECTORY)/lib
SOURCE_FILES   := $(wildcard src/*.cpp)
OBJECT_FILES   := $(SOURCE_FILES:.cpp=.o)

all: $(NAME)

.cpp.o:
	$(COMPILER) -c $(COMPILER_FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJECT_FILES) Makefile
	$(COMPILER) $(OBJECT_FILES) $(LINKER_FLAGS) -o ./bin/$(NAME)

clean:
	rm -rf $(OBJECT_FILES)

fclean:
	rm -rf $(OBJECT_FILES) ./bin/$(NAME)

test: $(NAME)
	./bin/$(NAME)
