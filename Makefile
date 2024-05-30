NAME = cub3D
NAME_B = cub3D_bonus
LIBFT = ./shared/libft/libft.a
USER = mel-akhd
MAN_FOLDER = ./mandatory/
BON_FOLDER = ./bonus/

SRC_COMMON = main.c drawing_utils.c init.c render.c ft_math.c terminate.c shapes.c ft_hooks.c raycast.c

SRC_M = $(addprefix $(MAN_FOLDER), $(SRC_COMMON)) 
SRC_B = $(addprefix $(BON_FOLDER), $(SRC_COMMON))

OBJ_M = $(SRC_M:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

CFLAGS = -Wall -Wextra -Werror -ffast-math   # -fsanitize=address -g

all : $(NAME)

bonus : ${NAME_B}

$(NAME) : $(OBJ_M) ${MAN_FOLDER}cub3d.h
	@make -C ./shared/libft
	@$(CC) $(CFLAGS) $(OBJ_M) /Users/${USER}/mlx/build/libmlx42.a -Iinclude -lglfw -L"/Users/${USER}/goinfre/homebrew/Cellar/glfw/3.4/lib" ${LIBFT} -o $(NAME)
	@echo "-----Done Building cub3D!-----"


$(NAME_B) : $(OBJ_B)  ${BON_FOLDER}cub3d.h
	@make -C ./shared/libft
	@$(CC) $(CFLAGS) $(OBJ_B) /Users/${USER}/mlx/build/libmlx42.a -Iinclude -lglfw -L"/Users/${USER}/goinfre/homebrew/Cellar/glfw/3.4/lib" ${LIBFT} -o $(NAME_B)


clean:
	${RM} ${OBJ_M} ${OBJ_B}
	${MAKE} -C ./shared/libft clean

fclean: clean
	${RM} ${NAME} ${NAME_B} 
	${MAKE} -C ./shared/libft fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus ${LIBFT}
