# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejin <yejin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 14:02:09 by yejin             #+#    #+#              #
#    Updated: 2022/06/10 01:38:21 by yejin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -I $(HEAD_PATH) -I $(MLX) -Wall -Wextra -Werror -g
GL_LINK = -L $(MLX) -lmlx -framework OpenGL -framework AppKit

NAME	= raycaster
MLX		= minilibx_opengl_20191021
RM		= rm -f

SRC_PATH	= src
OBJ_PATH	= obj
HEAD_PATH	= include

vpath %.c $(SRC_PATH)

SRC_FILE = $(notdir $(wildcard $(SRC_PATH)/*.c))
OBJ_FILE = $(SRC_FILE:.c=.o)

OBJ := $(OBJ_FILE)
OBJ	:= $(addprefix $(OBJ_PATH)/, $(OBJ))

$(OBJ_PATH)/%.o : %.c
	@echo "echo $(OBJ)"
	@$(CC) $(CFLAGS) -c -o $@ $^

$(NAME) : $(OBJ)
	@echo "[+] Create minilibx"
	@make -C $(MLX)
	@echo "[+] Create raycaster"
	@$(CC) $(CFLAGS) $(GL_LINK) $^ -o $@

all : $(NAME)

clean :
	@echo "[-] Delete object files"
	@$(RM) $(OBJ)
	@echo "[-] Delete minilibx"
	@make clean -C $(MLX)
	@$(RM) $(MLX)/libmlx

fclean : clean
	@echo "[-] Delete target file"
	@$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re