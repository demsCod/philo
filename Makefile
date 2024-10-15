NAME = philo

CC = cc 

FLAGS = -Wall -Werror -Wextra -g3


LIBFTPATH = ./libft 

FILES = philosopher.c \
		init_program/init.c	\
		routine/routine.c \


OBJ = $(FILES:.c=.o)

LIBFT = $(LIBFTPATH)/libft.a



all : $(LIBFT) $(NAME)

$(NAME) : 	$(FILES)
			@$(CC) $(FLAGS)  $(FILES) ./libft/libft.a  -o $(NAME)
			@echo "$(GREEN)$(NAME) done ✅$(END)"

$(LIBFT) :
			@make -C $(LIBFTPATH)

clean :
			@make clean -C $(LIBFTPATH)

fclean : clean
			@make fclean -C $(LIBFTPATH)
			@rm $(NAME)
			@echo "$(RED)remove $(NAME) 🚮$(END)"

re:	fclean all