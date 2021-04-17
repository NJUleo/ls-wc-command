INCLUDE = include
TEST = test
SRC = src
FLAGS = -g -Wall -Werror -Wfatal-errors
ls: ls.o get_file_info.o
	gcc $(FLAGS) -o ls ls.o get_file_info.o -I $(INCLUDE)

ls.o: src/ls.c $(INCLUDE)/ls.h
	gcc $(FLAGS) -c $(SRC)/ls.c -I $(INCLUDE)

test_get_file_info: test_get_file_info.o get_file_info.o
	gcc $(FLAGS) -o test_get_file_info get_file_info.o test_get_file_info.o -I $(INCLUDE)

test_get_file_info.o: $(TEST)/test_get_file_info.c $(INCLUDE)/get_file_info.h
	gcc $(FLAGS) -c $(TEST)/test_get_file_info.c -I $(INCLUDE)

get_file_info.o: $(SRC)/get_file_info.c $(INCLUDE)/get_file_info.h
	gcc $(FLAGS) -c $(SRC)/get_file_info.c -I $(INCLUDE)

clean:
	rm -rf ls
	rm -rf *.o