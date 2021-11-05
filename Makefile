# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 11:48:14 by amaach            #+#    #+#              #
#    Updated: 2021/11/05 12:00:21 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Werror -Wextra -Wall
NAME = philo
SRC = philo.c outils.c outils_libft.c working.c

all:	$(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	

fclean:	clean
	rm -f $(NAME)

re:		fclean all