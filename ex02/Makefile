# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 16:22:46 by omoreno-          #+#    #+#              #
#    Updated: 2023/10/20 11:01:16 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= PmergeMe

CLASSSRC	:=	PmergeMe.cpp

MAINSRC		:=	main.cpp

BUILD_PATH	:= .build/

MAINOBJ		:= $(addprefix $(BUILD_PATH), $(MAINSRC:.cpp=.o))
MAINDEPS	:= $(addprefix $(BUILD_PATH), $(MAINSRC:.cpp=.d))
CLASSOBJ	:= $(addprefix $(BUILD_PATH), $(CLASSSRC:.cpp=.o))
CLASSDEPS	:= $(addprefix $(BUILD_PATH), $(CLASSSRC:.cpp=.d))

HEADER		:= $(CLASSSRC:.cpp=.hpp)

CC			:=	c++
RM			:=	@rm -Rf
CFLAGS		:=	-Wall -Werror -Wextra -std=c++98 -pedantic -g

folder_create 	= $(shell mkdir -p $(1))

.SECONDEXPANSION:

$(BUILD_PATH)%.o : %.cpp ${HEADER} Makefile | $$(call folder_create,$$(dir $$@))
	@echo "Compiling" $@
	${CC} ${CFLAGS} -c -I. $< -o $@

all : $(NAME)

$(NAME) : ${MAINOBJ} ${HEADER} Makefile
	@echo "Linking" $@
	${CC} ${CFLAGS} ${MAINOBJ} -o $@

clean :
	@echo "Cleaning $(BUILD_PATH) ..."
	$(RM) $(BUILD_PATH)

reference: reference.cpp
	${CC} ${CFLAGS} reference.cpp -o reference

reference2: reference2.cpp
	${CC} ${CFLAGS} reference2.cpp -o reference2

cleanref:
	$(RM) ./reference
	$(RM) ./reference2
.PHONY : cleanref

fclean : clean  cleanref
	$(RM) $(NAME)
	@echo "Cleaned executable"

test:
	./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
#./reference `/usr/bin/shuf -i 1-1000 -n 500 | tr "\n" " "`;
.PHONY : test

test2:
	./reference2 `jot -r 3000 1 100000 | tr '\n' ' '`
#./reference2 `/usr/bin/shuf -i 1-1000 -n 500 | tr "\n" " "`;
.PHONY : test2

re: fclean all

.PHONY : clean fclean re all
