SOURCE	= src/lmcd.c
NAME	= microshell

all: $(SOURCE) 
	gcc -g3 -Wall -Werror -Wextra $< -o $(NAME)

norma: 
	norminette $(SOURCE)

test:
	cp $(NAME) tests
	$(MAKE)  -C tests test

clean:
	rm -f $(NAME)

.PHONY: all norma test clean
