##
## EPITECH PROJECT, 2020
## B-CCP-400-LYN-4-1-theplazza-paul.gardien-master
## File description:
## Makefile
##

OBJS	:=	$(patsubst %.cpp, %.o, $(shell find src -type f -name "*.cpp"))

INCLUDE	=	include

HFILE	=	$(wildcard $(INCLUDE)/*.hpp)

NAME	=	babel_server

INC_FLAG	=	-I $(INCLUDE)

OBJ_FLAG	=	-g3
OBJ_FLAG	+=	-Weverything
OBJ_FLAG	+=	-Wno-gnu
OBJ_FLAG	+=	-march=native
OBJ_FLAG	+= 	-pthread
OBJ_FLAG	+=	-lboost_system
OBJ_FLAG	+=	-std=gnu11

DEBUG_FLAGS	=	-O0

CC	=	@clang++
RM	=	@rm -f

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(OBJ_FLAG)

$(OBJS): $(HFILE)

debug: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(OBJ_FLAG) $(DEBUG_FLAGS)

clean:
	@$(RM) $(OBJS)
	@echo "\e[32m[ DONE ]\033[0m  Cleanned *o"

fclean: clean
	@$(RM) $(NAME)
	@echo "\e[32m[ DONE ]\033[0m  Cleanned $(NAME)"

re:	fclean all

.cpp.o:	%.c
	@$(CC) -c $< -o $@ $(INC_FLAG) && echo "\e[32m[ DONE ] \033[0m" $< || echo "\e[91;5m[ FAIL ] \e[25m" $< "\033[0m"

.PHONY: all clean fclean re
