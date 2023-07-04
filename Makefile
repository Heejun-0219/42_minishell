NAME	=	minishell

cc 		= 	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

READLINE_FLAGS		:= $(shell brew info readline | grep export | awk -F '"' '{print $$2}' | tr '\n' ' ')
READLINE_INCLUDE	:= $(shell brew info readline | grep CPPFLAGS | awk -F '"' '{print $$2}')

INCLUDES	=	includes/
LIBFT_DIR	=	srcs/Libft
LIBFT		= 	srcs/Libft/libft.a
LIBFT_INC	=	-L$(LIBFT_DIR) -lft

SRCS		=	srcs/main.c					\
				srcs/init.c					\
				srcs/lst/ft_lstclear.c		\
				srcs/lst/ft_lstinit.c		\
				srcs/lst/ft_lstdelone.c		\
				srcs/lst/ft_lstpush_back.c	

OBJS 		= $(SRCS:.c=.o)


.PHONY	: all
all		: $(NAME)

$(NAME)	: $(OBJS) $(INCLUDES)
			$(MAKE) -C $(LIBFT_DIR) all
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline $(READLINE_FLAGS)

%.o		: %.c
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) $(READLINE_INCLUDE)


.PHONY	: clean
clean	:
			@$(MAKE) -C $(LIBFT_DIR) clean
			@rm -rf $(OBJS) 

.PHONY	: fclean
fclean	: clean
			@$(MAKE) -C $(LIBFT_DIR) fclean
			@rm -rf $(NAME)

.PHONY	: re
re		:
			@make fclean
			@make all