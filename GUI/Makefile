##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## Makefile
##

FLAGS	=	-g3 -std=c++20 -Wall -Wextra \
			-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC		=	src/client.cpp \
			src/guimanager.cpp \
			src/main.cpp \
			src/loadingbar.cpp	\
			src/dashboard.cpp	\
			src/audioManager.cpp	\
			src/message_box.cpp


OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	g++ -Iinclude -Iraylib_extra -c $(FLAGS) $< -o $@

DIREC	= ../

NAME	=	$(DIREC)zappy_gui
CPY_NAME	=	zappy_gui

all		: $(SRC)  $(OBJ)
		g++ -Iinclude -Iraylib_extra -o $(NAME) $(OBJ) $(FLAGS)

clean	:
		rm -fr *~
		rm -fr *.o
		rm -fr *vgcore*
		rm -f $(OBJ)
		rm -f *.gcno
		rm -f *.gcda
		rm -f *.gcov
		rm -f *.txt
		rm -f unit_tests
		@rm -f $(NAME)

fclean	: clean
	    rm -fr $(NAME)
	    rm -fr $(CPY_NAME)

re	: fclean all
