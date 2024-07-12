CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
OBJ = backend/s21_parser.c
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
TESTFLAGS = -lcheck -coverage -lpthread -pthread  
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage
TARGET := SmartCalc
ALL_FILES_TEST = $(shell find ./tests -name "*.c")
SRC= $(shell find ./backend -name "*.c")

C_F=$(wildcard $(addsuffix /*.c, $(DIRS)))
H_F=$(wildcard $(addsuffix /*.h, $(DIRS)))
CPP_F=$(wildcard $(addsuffix /*.cpp, $(DIRS)))

DIRS:=$(shell find ./ -type d)

OS := $(shell uname -s)

ifeq  ($(OS), Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS), Darwin)
	OPEN_CMD = open
endif

all: clean

install: uninstall
	mkdir build
	cd front/ui && qmake && make && make clean && rm Makefile

uninstall:
	rm -fr build

dvi:
	open ../README_RUS.md

run:
	open build/ui.app

view.a:
	gcc -c backend/s21*.c
	ar rc $@ *.o
	ranlib $@
	cp $@ lib$@
	rm -rf *.o

dist:
	mkdir 3DViewer_V1.0/
	mkdir 3DViewer_V1.0/src
	cp -R backend figures Makefile front 3DViewer_V1.0/src
	tar cvzf 3DViewer_V1.0.tgz 3DViewer_V1.0/
	rm -rf 3DViewer_V1.0

tests: clean unarchive
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) tests/test.c backend/s21*.c -o test $(TESTFLAGS) -lm
else
	$(CC) $(CFLAGS) tests/test.c backend/s21*.c -o test -lcheck $(LINUX_FLAGS)
endif
	./test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/test.c backend/s21*.c -o test $(TESTFLAGS) -lm
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/test.c backend/s21*.c -o test -lcheck $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info --no-external --filter range -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.

style:
	cp ../materials/linters/.clang-format .
	clang-format -n $(C_F) $(H_F) $(CPP_H)

style_improve:
	cp ../materials/linters/.clang-format .
	clang-format -i $(C_F) $(H_F) $(CPP_H)	
	rm -rf .clang-format
	
unarchive:
	unzip figures/correct.zip -d figures
	unzip figures/incorrect.zip -d figures

clean:
	rm -rf debug
	rm -rf *.o
	rm -rf *.a
	rm -rf test
	rm -rf *.gcda *.gcno
	rm -rf report
	rm -rf *.info
	rm -rf *.tgz

