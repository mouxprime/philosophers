/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:12:20 by mianni            #+#    #+#             */
/*   Updated: 2024/10/02 15:32:34 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->numbers_of_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (ft_putendl_fd("Error\n", 2), false);
	while (i < table->numbers_of_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		if (!&table->forks[i])
			return (ft_putendl_fd("Error mutex\n", 2), false);
		i++;
	}
	attribution_mutex(table);
	return (true);
}

void	attribution_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(table->numbers_of_philos * sizeof(t_core));
	pthread_mutex_init(&table->write_lock, NULL);
	while (i < table->numbers_of_philos)
	{
		table->philo[i].id = i;
		table->philo[i].meal_eaten = 0;
		table->philo[i].eating = 0;
		table->dead_flag = 0;
		table->philo[i].last_meal_time = getcurrenttime();
		table->start_time = getcurrenttime();
		table->philo[i].table = table;
		table->philo[i].l_fork = &table->forks[i];
		if (i + 1 < table->numbers_of_philos)
			table->philo[i].r_fork = &table->forks[i + 1];
		else
			table->philo[i].r_fork = &table->forks[0];
		pthread_mutex_init(&table->philo[i].last_meal_time_m, NULL);
		pthread_mutex_init(&table->philo[i].meal_lock, NULL);
		pthread_mutex_init(&table->philo[i].dead_lock, NULL);
		i++;
	}
}

void	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers_of_philos)
	{
		pthread_create(&table->philo[i].thread_id, NULL, routine,
			&table->philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&table->monitor, NULL, monitor, table);
	while (i < table->numbers_of_philos)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
