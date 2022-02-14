# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echuong <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 15:02:28 by echuong           #+#    #+#              #
#    Updated: 2022/02/07 15:19:43 by echuong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c \
       srcs/ft_builtins.c \
       srcs/ft_cd.c \
       srcs/ft_check_cmds.c \
       srcs/ft_check_env_var.c \
       srcs/ft_check_syntax.c \
       srcs/ft_check_syntax_utils.c \
       srcs/ft_cmd_not_found.c \
       srcs/ft_conv_ascii.c \
       srcs/ft_count.c \
       srcs/ft_cpy.c \
       srcs/ft_echo.c \
       srcs/ft_env.c \
       srcs/ft_errors.c \
       srcs/ft_exec.c \
       srcs/ft_exit.c \
       srcs/ft_exit_status.c \
       srcs/ft_expand_var.c \
       srcs/ft_export.c \
       srcs/ft_export_utils.c \
       srcs/ft_first_cmd.c \
       srcs/ft_free.c \
       srcs/ft_handle_cmds.c \
       srcs/ft_handle_list.c \
       srcs/ft_handle_path.c \
       srcs/ft_heredoc_get_line.c \
       srcs/ft_init.c \
       srcs/ft_inter_cmds.c \
       srcs/ft_itoa.c \
       srcs/ft_last_cmd.c \
       srcs/ft_modif_input_heredoc.c \
       srcs/ft_parsing.c \
       srcs/ft_pwd.c \
       srcs/ft_redirect.c \
       srcs/ft_redirect_heredoc.c \
       srcs/ft_signals.c \
       srcs/ft_split_elem.c \
       srcs/ft_split_path.c \
       srcs/ft_split_token.c \
       srcs/ft_supp_quotes.c \
       srcs/ft_unset.c \
       srcs/ft_utils.c \
       srcs/ft_utils_t.c

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ./includes

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) -lreadline $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
