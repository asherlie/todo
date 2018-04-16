CXX=gcc
all: td
td:
	$(CXX) todo.c -Wall -Wextra -Werror -O2 -o td
clean:
	rm -f td
