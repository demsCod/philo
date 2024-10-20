NAME = philo

CC = cc 

FLAGS = -Wall -Werror -Wextra  -g3 # -fsanitize=thread


LIBFTPATH = ./libft 

FILES = philosopher.c \
		init_program/init.c	\
		routine/routine.c \
		routine/philo_action.c \
		routine/philo_utils.c \
		routine/philo_utils2.c \
		routine/routine_utils.c \
		routine/times_utils.c \
		free_erro/free_and_exit.c \


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