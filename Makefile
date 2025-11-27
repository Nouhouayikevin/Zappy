##
## EPITECH PROJECT, 2025
## B-YEP-400-COT-4-1-zappy-julcinia.oke
## File description:
## Makefile
##
.ONESHELL:
GUI_DIR	=	./GUI/
GUI_BIN =	zappy_gui

AI_DIR	=	./AI/
AI_BIN =	zappy_ai

SERVER_DIR	=	./Serveur/
SERVER_BIN 	=	zappy_server

all		: SERVER AI zappy_gui

SERVER	:
	make -C $(SERVER_DIR) -f Makefile
	cp $(SERVER_DIR)/zappy_server .

AI		: ia

ia		:
	cp $(AI_DIR)main.py .
	mv main.py $(AI_BIN)
	chmod +x $(AI_BIN)

GUI		: zappy_gui

zappy_gui:
	make -C $(GUI_DIR) -f Makefile

clean	:
		rm -fr *~
		rm -fr *vgcore*
		rm -f *.gcno
		rm -f *.gcda
		rm -f *.gcov

fclean	:	clean
	    rm -fr $(SERVER_BIN)
	    rm -fr $(AI_BIN)
	    rm -fr $(GUI_BIN)
	    cd $(SERVER_DIR) && make fclean && cd -
	    cd $(GUI_DIR) && make fclean && cd -

re		:	fclean all
