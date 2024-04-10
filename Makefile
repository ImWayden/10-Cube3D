# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wayden <wayden@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 19:22:33 by wayden            #+#    #+#              #
#    Updated: 2024/04/09 12:14:50 by wayden           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = cc
CXXFLAGS = -Wall -Werror -Wextra -g3

SRCS = main_test.c debug.c \
	map_utils.c map_errorcheck.c map_errorcheck2.c map_parser2.c map_parser.c map_utils.c \
	error_manager.c singletons.c Logic_update.c hooks.c
	 
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))
NAME = Cub3D

LIBS_DIR = libs
LIB_MLX = libmlx_Linux
LIB_FT = libft

PATH_MLX = $(addprefix $(LIBS_DIR)/,$(LIB_MLX))
PATH_FT = $(addprefix $(LIBS_DIR)/,$(LIB_FT))
LIBS_MLX_A = $(addprefix $(PATH_MLX),/$(addsuffix .a,$(LIB_MLX)))
LIBS_FT_A = $(addprefix $(PATH_FT),/$(addsuffix .a,$(LIB_FT)))
LIBS_A = $(LIBS_MLX_A) $(LIBS_FT_A)

PATH_LIB = $(PATH_MLX) $(PATH_FT)

all: obj $(LIBS) $(NAME)

obj:
	mkdir -p obj

$(NAME): $(OBJS) $(LIBS_A)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBS_A):
	for path in $(PATH_LIB); do \
		$(MAKE) -C $$path; \
	done
	
re: fclean all

clean:
	rm -rf obj
	for lib in $(PATH_LIB); do \
		$(MAKE) -C $$lib clean; \
	done

fclean: clean
	rm -f $(NAME)
	for lib in $(PATH_LIB); do \
		$(MAKE) -C $$lib fclean; \
	done

.PHONY: all clean fclean re
