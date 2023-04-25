# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helneff <helneff@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 09:05:28 by jonascim          #+#    #+#              #
#    Updated: 2023/04/25 13:42:39 by helneff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minirt
LIBFT		:= libft
INCLUDE		:= includes
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g -fsanitize=address
MLXFLAGS	:= -framework OpenGL -framework AppKit
RM			:= rm -f

SRC_DIR		:= srcs/
STRUCT_DIR	:= srcs/struct/
PARSER_DIR	:= srcs/parser/
RENDER_DIR	:= srcs/render/

SRC_FILES		:=	main.c window.c

STRUCT_FILES	:=	vec3_arithmetic.c vec3_utils.c

PARSER_FILES	:=	parser.c		parser_utils.c		parser_camera.c parser_ambient.c \
					parser_light.c	parser_sphere.c		parser_plane.c	parser_cylinder.c

RENDER_FILES	:=	camera.c image.c

SRC 		:= 	$(addprefix $(SRC_DIR), $(SRC_FILES))
STRUCT 		:= 	$(addprefix $(STRUCT_DIR), $(STRUCT_FILES))
PARSER 		:= 	$(addprefix $(PARSER_DIR), $(PARSER_FILES))
RENDER 		:= 	$(addprefix $(RENDER_DIR), $(RENDER_FILES))

all:		$(NAME)

$(NAME):	$(SRC)
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(SRC) $(STRUCT) $(PARSER) $(RENDER) -o$(NAME) -I$(INCLUDE) -I$(LIBFT) -L$(LIBFT) -lft -lmlx $(MLXFLAGS)

clean:
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)/libft.a

re:			fclean all

.PHONY:		all clean fclean re norm
