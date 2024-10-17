# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mianni <mianni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 14:02:48 by mianni            #+#    #+#              #
#    Updated: 2024/10/02 16:03:05 by mianni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BONUS_NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = ./philo_utils
BONUS_DIR = ./philo_bonus_utils

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/philo_routine.c \
		$(SRC_DIR)/threads_mutex_init.c \
		$(SRC_DIR)/philo_utils.c \
		$(SRC_DIR)/check_all_data.c \
		$(SRC_DIR)/libft_utils.c \
		$(SRC_DIR)/actions.c

BONUS_SRCS = $(BONUS_DIR)/main.c \
		$(BONUS_DIR)/parsing.c \
		$(BONUS_DIR)/philo_utils.c \
		$(BONUS_DIR)/libft_utils.c \
		$(BONUS_DIR)/init_process.c \
		$(BONUS_DIR)/actions.c \
		$(BONUS_DIR)/philo_routine.c \
		$(BONUS_DIR)/check_all_data.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
