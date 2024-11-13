# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: therodri <therodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 19:22:33 by wayden            #+#    #+#              #
#    Updated: 2024/04/21 20:43:25 by therodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = cc
CXXFLAGS = -Wall -Werror -Wextra

SRCDIR = source

SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(patsubst $(SRCDIR)/%.c,obj/%.o,$(SRCS))

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

all: obj $(NAME)

obj:
	mkdir -p obj
	
$(NAME): $(OBJS) $(LIBS_A) 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lX11 -lXext -lm

obj/%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBS_A):
	for path in $(PATH_LIB); do \
		$(MAKE) -C $$path; \
	done
re: fclean all

clean:
	rm -rf obj obj_debug
	for lib in $(PATH_LIB); do \
		$(MAKE) -C $$lib clean; \
	done

fclean: clean
	rm -f $(NAME) $(DEBUG)
	for lib in $(PATH_LIB); do \
		$(MAKE) -C $$lib fclean; \
	done

.PHONY: all clean fclean re
