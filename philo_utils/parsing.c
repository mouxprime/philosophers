/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:29 by mianni            #+#    #+#             */
/*   Updated: 2024/09/27 12:00:44 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	parsing(int argc, char **argv, t_table *table)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (check_argv(argv[i]) == false)
			return (ft_putendl_fd("Error, invalid character in arguments.", 2),
				false);
		nb = ft_atol(argv[i]);
		if (ft_strlen(argv[i]) > 12)
			return (ft_putendl_fd("Error, invalid arguments\n", 2), false);
		if (nb < 0)
			return (ft_putendl_fd("Error, invalid arguments\n", 2), false);
		else if (i == 1 && nb > 200)
			return (ft_putendl_fd("Error, too much philos.", 2), false);
		i++;
	}
	setup_struct_data(argc, argv, table);
	return (true);
}

void	setup_struct_data(int argc, char **argv, t_table *table)
{
	int	i;
	int	nb;

	i = 0;
	while (i < argc && argv[i])
	{
		nb = ft_atol(argv[i]);
		if (i == 1 && nb <= 200)
			table->numbers_of_philos = nb;
		if (i == 2)
			table->time_to_die = nb;
		if (i == 3)
			table->time_to_eat = nb;
		if (i == 4)
			table->time_to_sleep = nb;
		table->numbers_of_eats = -1;
		if (i == 5)
			table->numbers_of_eats = nb;
		i++;
	}
}

bool	check_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}
