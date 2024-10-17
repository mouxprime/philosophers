/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:27 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 16:23:40 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Error, invalid arguments", 2), 0);
	if (parsing(argc, argv, &table) == false)
		return (0);
	init_mutex(&table);
	init_threads(&table);
	free(table.philo);
	free(table.forks);
}
