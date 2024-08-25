# ======================= GLOSSARY ⊂(｡•́‿•̀｡⊃)

GCC = gcc -Wall -Werror -Wextra -pedantic -std=c11 -g 
GCOV=-fprofile-arcs -ftest-coverage

OS = $(shell uname -s)
ifeq ($(OS), Darwin)
LC = -lcheck
else ifeq ($(OS), Linux)
LC = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE
endif

LIB = s21_decimal.a
TESTS = tests/*.c
TESTN = test
CLANG = clang-format -style=Google

# ======================= TARGETS ⊂(｡•́‿•̀｡⊃)

all: $(LIB)

s21_decimal.a: 
	$(GCC) -c *.c && ar rc $(LIB) *.o && ranlib $(LIB)

test: $(LIB)
	$(GCC) --coverage $(TESTS) $(LIB) -o $(TESTN) $(LC) && ./$(TESTN)

clean:
	rm -rf $(TESTN) *.o *.a *.gch *.gcno *.log *.gcda report/ *.info *.dSYM/

gcov_report: clean
	$(GCC) $(GCOV) *.c  $(TESTS) -o $(TESTN) $(LC) && ./$(TESTN)
	lcov -t "$(TESTN)" -o $(TESTN).info -c -d .
	genhtml -o report $(TESTN).info
	open ./report/index.html
	rm -rf *.gcda *.gcno $(TESTN)

# ======================= CHECKS ⊂(｡•́‿•̀｡⊃)

style:
	$(CLANG) -n *.c *.h && $(CLANG) -i *.c *.h
	$(CLANG) -n */*.c *.h && $(CLANG) -i */*.c *.h

leaks: clean test
	CK_FORK=no leaks -atExit -- ./$(TESTN)  $t > testleaks.log
	open testleaks.log

instadock: 
	rm -rf ~/Library/Containers/com.docker.docker
	mkdir -p ~/goinfre/Docker/Data
	ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker

valgrind_mac: clean instadock
	open -a 'Docker'
	cd .. && cd materials/build/valgrind && bash run.sh 

valgrind_lin:
	valgrind --tool=memcheck --leak-check=full ./$(TESTN)