# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 16:22:46 by omoreno-          #+#    #+#              #
#    Updated: 2023/10/26 11:14:07 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= btc

CLASSSRC	:=	BitcoinExchange.cpp \
				Date.cpp \
				ScalarConverter.cpp \
				CustomExcepts.cpp \
				LogError.cpp

MAINSRC		:=	main.cpp

BUILD_PATH	:= .build/

MAINOBJ		:= $(addprefix $(BUILD_PATH), $(MAINSRC:.cpp=.o))
MAINDEPS	:= $(addprefix $(BUILD_PATH), $(MAINSRC:.cpp=.d))
CLASSOBJ	:= $(addprefix $(BUILD_PATH), $(CLASSSRC:.cpp=.o))
CLASSDEPS	:= $(addprefix $(BUILD_PATH), $(CLASSSRC:.cpp=.d))
HEADER		:= $(CLASSSRC:.cpp=.hpp)
HEADER		+= CustomDefs.hpp Colors.hpp 

CC			:=	c++
RM			:=	@rm -Rf
CFLAGS		:=	-Wall -Werror -Wextra -std=c++98 -pedantic

folder_create 	= $(shell mkdir -p $(1))

.SECONDEXPANSION:

$(BUILD_PATH)%.o : %.cpp ${HEADER} Makefile | $$(call folder_create,$$(dir $$@))
	@echo "Compiling" $@
	${CC} ${CFLAGS} -c -I. $< -o $@

all : $(NAME)

$(NAME) : ${MAINOBJ} ${CLASSOBJ} ${HEADER} Makefile
	@echo "Linking" $@
	${CC} ${CFLAGS} ${MAINOBJ} ${CLASSOBJ} -o $@

clean :
	@echo "Cleaning $(BUILD_PATH) ..."
	$(RM) $(BUILD_PATH)

fclean : clean
	$(RM) $(NAME)
	@echo "Cleaned executable"

re: fclean all

.PHONY : clean fclean re all
