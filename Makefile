# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acottier <acottier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 09:21:32 by acottier          #+#    #+#              #
#    Updated: 2018/04/13 15:39:02 by acottier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= avm

CC			= clang++
FLAGS		= -Wall -Wextra -Werror -std=c++11

SRC_PATH	= sources
OBJ_PATH	= objects

SRC_NAMES	= 	main.cpp \
				Token.class.cpp \
				input.cpp \
				lexer.cpp \
				parser.cpp \
				argumentParsing.cpp \
				operations.cpp \
				Factory.class.cpp \
				Error.class.cpp \
				execute.cpp
				
OBJ_NAMES	= $(SRC_NAMES:.cpp=.o)

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))

.PHONY: all re clean fclean

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	mkdir -p $(OBJ_PATH) && $(CC) $(FLAGS) $< -c -o $@

clean :
	rm -rf $(OBJ_PATH)

fclean : clean
	rm -rf $(NAME)

re : fclean all