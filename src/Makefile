CC                    := gcc
CXX                   := g++

CFLAGS                := -Wall -Wextra -Werror -std=c11 -pedantic -c
CXXFLAGS              := -Wall -Wextra -Werror -std=c++17 -pedantic
GTEST_FLAG            := -lgtest
LCHECK_FLAG 		  := -lcheck -lm -lsubunit
COVERAGE_FLAGS        := -fprofile-arcs -ftest-coverage
LDGUI                 := -lncurses
VALGRIND              := valgrind -q -s --leak-check=full --trace-children=yes --track-origins=yes 
LICK_LOG_FILE		  := --log-file=
GCOV_FLAGS			  := -lgcov --coverage

TETRIS_PATH 		  :=brick_game/tetris
SNAKE_PATH  		  :=brick_game/snake
CLI_PATH			  :=gui
CONTROLLER_PATH		  :=controller
VALGRIND_RES 		  :=tests/RESULT_VALGRIND.txt
COMMON_PATH           :=common_objects

TETRIS_SOURCES		  :=$(wildcard $(TETRIS_PATH)/*.c)
TETRIS_OBJECTS		  :=$(TETRIS_SOURCES:.c=.o)
TETRIS_LIBNAME 		  :=tetris.a
TETRIS_TEST_SRC		  :=$(wildcard $(TETRIS_PATH)/tests/*.c)

SNAKE_SOURCES		  :=$(wildcard $(SNAKE_PATH)/*.cpp)
SNAKE_OBJECTS		  :=$(SNAKE_SOURCES:.cpp=.o)
SNAKE_LIBNAME		  :=snake.a
SNAKE_TEST_SRC		  :=$(wildcard $(SNAKE_PATH)/tests/*.cpp)

CLI_SOURCES			  :=$(wildcard $(CLI_PATH)/*.c)
CLI_OBJECTS			  :=$(CLI_SOURCES:.c=.o)
CLI_LIBNAME			  :=cli.a

CLI_VIEW_SOURCES	  :=$(wildcard $(CLI_PATH)/*.cpp)
CLI_VIEW_OBJECTS	  :=$(CLI_VIEW_SOURCES:.cc=.o)

CONTROLLER_SOURCES	  :=$(wildcard $(CONTROLLER_PATH)/*.cpp)
CONTROLLER_OBJECTS	  :=$(CONTROLLER_SOURCES:.cc=.o)

.PHONY: all
all: install

.PHONY: install
install: uninstall install_cli_brick_game
	rm -f $(TETRIS_LIBNAME) $(CLI_LIBNAME) $(SNAKE_LIBNAME)

.PHONY: install_cli_brick_game
install_cli_brick_game: build_cli build_snake build_tetris $(CONTROLLER_SOURCES) $(CLI_VIEW_SOURCES)
	$(CXX) $(CXXFLAGS) app/cli_brick_game.cpp  $(CONTROLLER_SOURCES) $(CLI_VIEW_SOURCES) $(SNAKE_LIBNAME) $(TETRIS_LIBNAME) $(CLI_LIBNAME) -o cli_brick_game $(LDGUI) 
	rm -f $(CONTROLLER_PATH)/*.o

.PHONY: uninstall
uninstall: 
	rm -f cli_brick_game

.PHONY: build_tetris
build_tetris: $(TETRIS_OBJECTS)
	ar rcs $(TETRIS_LIBNAME) $(TETRIS_OBJECTS) $(LDGUI)
	rm -f $(TETRIS_PATH)/*.o

.PHONY: build_snake
build_snake: $(SNAKE_OBJECTS)
	ar rcs $(SNAKE_LIBNAME) $(SNAKE_OBJECTS) 
	rm -f $(SNAKE_PATH)/*.o

.PHONY: build_cli
build_cli:  $(CLI_OBJECTS)
	ar rcs $(CLI_LIBNAME) $(CLI_OBJECTS) $(LDGUI)
	rm -f $(CLI_PATH)/*.o

.PHONY: clean
clean: uninstall
	rm -f ./*.o brick_game/*/*.o brick_game/*/tests/*.o gui/cli/*.o controller/*.o
	rm -f brick_game/*/*.gcda brick_game/*/*.gcno
	rm -f brick_game/*/tests/*.gcda brick_game/*/tests/*.gcno
	rm -f ./*.gcda ./*.gcno
	rm -f brick_game/*/tests/*.txt brick_game/*/tests/*.info
	rm -f brick_game/*/tests/test brick_game/*/tests/tests
	rm -f brick_game/*/*.txt
	rm -rf report
	rm -f tetris.install.tar.gz snake.install.tar.gz

.PHONY: dvi
dvi: 
	# Вариант, если установлена библиотека doxygen
	# doxygen brick_game/tetris/doxygen_config
	# doxygen brick_game/snake/doxygen_config


.PHONY: dist
dist: 
	tar -czf tetris.install.tar.gz ./* 
	tar -czf snake.install.tar.gz ./* 

.PHONY: test
test: clean test_tetris test_snake

.PHONY: test_tetris
test_tetris: CFLAGS += $(COVERAGE_FLAGS)
test_tetris: clean build_tetris 
	$(CC) $(subst -c ,,$(CFLAGS)) $(DEBUG_FLAGS) $(TETRIS_TEST_SRC) $(TETRIS_LIBNAME) -o $(TETRIS_PATH)/tests/tests $(LCHECK_FLAG) $(LDGUI)
	$(VALGRIND) $(LICK_LOG_FILE)$(TETRIS_PATH)/$(VALGRIND_RES) $(TETRIS_PATH)/tests/tests 

.PHONY: test_snake
test_snake: CXXFLAGS += $(COVERAGE_FLAGS)
test_snake: clean build_snake 
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SNAKE_TEST_SRC) $(SNAKE_LIBNAME) -o $(SNAKE_PATH)/tests/tests $(GTEST_FLAG)  
	$(VALGRIND) $(LICK_LOG_FILE)$(SNAKE_PATH)/$(VALGRIND_RES) $(SNAKE_PATH)/tests/tests

.PHONY: check
check:
	cppcheck -I./ .
	clang-format -n $(TETRIS_PATH)/*.c $(TETRIS_PATH)/*.h
	clang-format -n $(SNAKE_PATH)/*.cpp
	clang-format -n $(TETRIS_PATH)/tests/*.c $(TETRIS_PATH)/tests/*.h
	clang-format -n $(SNAKE_PATH)/tests/*.cpp $(SNAKE_PATH)/tests/*.h
	clang-format -n $(CLI_PATH)/*.c $(CLI_PATH)/*.h $(CLI_PATH)/*.cpp
	clang-format -n $(CONTROLLER_PATH)/*.cpp $(CONTROLLER_PATH)/*.h
	clang-format -n $(COMMON_PATH)/*.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
