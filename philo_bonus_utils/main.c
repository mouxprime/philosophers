/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:27 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 16:23:27 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_utils/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Error, invalid arguments", 2), 0);
	if (parsing(argc, argv, &table) == false)
		return (0);
	data_define(&table);
	sem_wait(table.one_is_dead);
	kill_child(table.philo);
	close_sem(&table);
}

//5 600 150 150
// check segfault sur 5 800 200 200 7
//5 800 200 200 7