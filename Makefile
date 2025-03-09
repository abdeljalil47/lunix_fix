SRC= minishell.c ./build_in/build_cmd/ft_cd.c ./build_in/build_cmd/ft_env.c ./build_in/build_cmd/ft_echo.c manage_error_free/error_exit.c\
	./build_in/handle_env.c ./build_in/build_cmd/ft_unset.c ./build_in/build_cmd/ft_exit.c ./build_in/build_cmd/ft_export.c\
	./build_in/build_cmd/ft_export_utils.c ./build_in/build_cmd/ft_pwd.c ./expand/expand.c ./build_in/manage_cmd.c ./excution/excution_1.c\
	./excution/excution_2.c

OBJ= $(SRC:.c=.o)
CC= cc
CFLAGS= 
#-Wall -Wextra -Werror
NAME= minishell

lib = libft/libft.a

all: $(NAME)

%.o:%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
#make all -C libft
	$(CC) $(OBJ) $(lib) -lreadline -fsanitize=address -o $(NAME)

clean:
#make clean -C libft
	rm -rf $(OBJ)

fclean: clean
#make fclean -C libft
	rm -rf $(NAME)

re: fclean all