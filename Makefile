# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wayden <wayden@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 19:22:33 by wayden            #+#    #+#              #
#    Updated: 2024/04/15 12:17:17 by wayden           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = cc
CXXFLAGS = -g3

SRCS = main.c\
	map_errorcheck.c map_errorcheck2.c map_parser2.c map_parser.c map_utils.c \
	error_manager.c singletons.c raytracing.c hooks.c
	
SRCS_DEBUG = main_debug.c\
	map_errorcheck.c map_errorcheck2.c map_parser2.c map_parser.c map_utils.c\
	error_manager.c singletons.c vec2_utils.c mlx_utils.c math_utils.c\
	error_manager.c singletons.c raytracing.c hooks.c 
 
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))

OBJS_DEBUG = $(patsubst %.c,obj_debug/%.o,$(SRCS_DEBUG))

NAME = Cub3D
NAME_DEBUG = Cub3D_DebugBuild

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

debug: obj_debug $(NAME_DEBUG)

obj:
	mkdir -p obj
	
obj_debug:
	mkdir -p obj_debug
	
$(NAME): $(OBJS) $(LIBS_A) 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lmlx -lX11 -lXext -lm

$(NAME_DEBUG): $(OBJS_DEBUG) $(LIBS_A) 
	$(CXX) $(CXXFLAGS) -g3 -DDEBUG=0 -o $@ $^ libs/libmlx_Linux/mlx_xpm.c -lmlx -lX11 -lXext -lm

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) -g3 -c $< -o $@

obj_debug/%.o: %.c
	$(CXX) $(CXXFLAGS) -g3 -c $< -o $@ 

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
