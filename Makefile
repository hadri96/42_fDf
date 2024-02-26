NAME		=	fdf
LIBFT		=	libft/
GNL			=	get_next_line/
MLX			=	minilibx_macos/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

CC			=	gcc
INCLUDE 	=	includes
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE) -Wno-deprecated -g
RM			=	rm -f
SRCS		=	srcs/parse.c \
                srcs/utils/memory.c \
				srcs/utils/parse_utils.c \
				srcs/utils/display_utils.c \
				srcs/utils/exception.c \
				srcs/rotate_basic.c \
				srcs/rotate_map.c \
				srcs/transform.c \
				srcs/translate.c \
				srcs/zoom.c \
				srcs/map_computation.c \
				srcs/draw.c \
				srcs/display.c

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(GNL_A) $(MLX_A)
				@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(GNL) -lgnl -L$(MLX) -lmlx -lm -o $(NAME) -framework OpenGL -framework AppKit
				@echo "Linked into executable \033[0;32mfdf\033[0m."

$(LIBFT_A):
				@$(MAKE) bonus -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

$(GNL_A):
				@$(MAKE) -s -C $(GNL)
				@echo "Compiled $(GNL_A)."

$(MLX_A):
				@$(MAKE) -s -C $(MLX)
				@echo "Compiled $(MLX_A)."

bonus:			all

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) $(OBJS)
				@echo "Removed object files."

clean:			localclean
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."

fclean:			localclean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus
