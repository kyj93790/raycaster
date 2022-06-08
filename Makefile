# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejin <yejin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 14:02:09 by yejin             #+#    #+#              #
#    Updated: 2022/06/08 14:14:56 by yejin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
GL_FLAGS = -I $(MLX) -L $(MLX) -lmlx -framework OpenGL -framework AppKit 

NAME	= raycaster
MLX		= minilibx_opengl_20191021
RM		= rm -f

SRC_PATH	= src
OBJ_PATH	= OBJ
HEAD_PATH	= include

vpath %.c $(SRC_PATH)
vpath %.h $(HEAD_PATH)

SRC_FILE = $(notdir $(wildcard $(SRC_PATH)/*.c))
OBJ_FILE = $(SRC_FILE:.c=.o)

OBJ = $(OBJ_FILE)
OBJ	= $(addprefix $(OBJ_PATH)/, $(OBJ)

$(NAME) : $(OBJ)
	@echo "[+] Create minilibx"
	@make -C $(MLX)
	@echo "[+] Create raycaster"
	@$(CC) $(CFLAGS) $(GL_FLAGS) $^ -o $@

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