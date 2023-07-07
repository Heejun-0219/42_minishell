NAME	=	minishell

cc 		= 	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
RM		=	rm -rf

READLINE_FLAGS		:= $(shell brew info readline | grep export | awk -F '"' '{print $$2}' | tr '\n' ' ')
READLINE_INCLUDE	:= $(shell brew info readline | grep CPPFLAGS | awk -F '"' '{print $$2}')
# READLINE_FLAGS		= -L/opt/homebrew/opt/readline/lib
# READLINE_INCLUDE	= -I/opt/homebrew/opt/readline/include
# READLINE_FLAGS		= -L$(HOME)/.brew/opt/readline/lib
# READLINE_INCLUDE	= -I$(HOME)/.brew/opt/readline/include

INCLUDES	=	includes/
LIBFT_DIR	=	srcs/Libft
LIBFT		= 	srcs/Libft/libft.a
LIBFT_INC	=	-L$(LIBFT_DIR) -lft


SRCS		=	srcs/main.c							\
				srcs/utils/init.c					\
				srcs/utils/error_free.c				\
				srcs/utils/sig.c					\
				srcs/lst/ft_lstclear.c				\
				srcs/lst/ft_lstinit.c				\
				srcs/lst/ft_lstdelone.c				\
				srcs/lst/ft_lstpush_back.c			\
				srcs/parsing/parsing.c				\
				srcs/parsing/quoter_utils.c			\
				srcs/make_cmd_info/make_cmd_info.c	\
				srcs/make_cmd_info/change_env.c		\
				srcs/make_cmd_info/make_pipe.c		\
				srcs/builtin/builtin.c				\
				srcs/exe_cmd/exe_cmd.c				\
				srcs/exe_cmd/here_doc.c				\
				srcs/builtin/exe_cd.c				\
				srcs/builtin/exe_echo.c				\
				srcs/builtin/exe_env.c				\
				srcs/builtin/exe_exit.c				\
				srcs/builtin/exe_export.c			\
				srcs/builtin/exe_pwd.c				\
				srcs/builtin/exe_unset.c			

OBJS 		= $(SRCS:.c=.o)

.PHONY	: all
all		: $(NAME)

$(NAME)	: $(OBJS) $(INCLUDES)
	$(MAKE) -C $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -lreadline -o $(NAME)

%.o		: %.c
			$(CC) $(CFLAGS) -g -c $< -o $@ -I$(INCLUDES) $(READLINE_INCLUDE)


.PHONY	: clean
clean	:
			@$(MAKE) -C $(LIBFT_DIR) clean
			rm -rf $(OBJS) 

.PHONY	: fclean
fclean	:
			@$(MAKE) -C $(LIBFT_DIR) fclean
			rm -rf $(OBJS)
			rm -rf $(NAME)

.PHONY	: re
re		:
			@make fclean
			@make all