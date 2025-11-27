##
## EPITECH PROJECT, 2024
## minishell1
## File description:
## makefile
##

SRC	=	src/*.c

all	:
	gcc -g3 $(SRC) -lm -o zappy_server

clean	:
	rm -f ./src/*~
	rm -f ./src/*#
	rm -f *vgcore*
	rm -f *.gcno
	rm -f *.gcda
	rm -f *~
	rm -f *.vgcore
	rm -f *vgcore.*
	find "." -type f -name '*~' -exec rm -f {} \;

fclean	:clean
	rm -f myftp

re	:fclean all

code	: fclean
	clear
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log
