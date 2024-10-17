/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:56 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 16:10:12 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat(t_core *philo)
{
	int	i;
	int	all_meal_eaten;

	i = 0;
	all_meal_eaten = 0;
	if (philo->table->numbers_of_eats == -1)
		return (0);
	while (i <= philo->table->numbers_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].meal_eaten >= philo->table->numbers_of_eats)
			all_meal_eaten++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	if (all_meal_eaten >= philo->table->numbers_of_philos)
	{
		pthread_mutex_lock(&philo->dead_lock);
		philo->table->dead_flag = 1;
		pthread_mutex_unlock(&philo->dead_lock);
		return (1);
	}
	return (0);
}

int	check_if_dead(t_core *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].table->numbers_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[0].table->time_to_die))
		{
			print_message("died	📌📌💀", &philos[i], i);
			pthread_mutex_lock(&philos[0].dead_lock);
			philos[0].table->dead_flag = 1;
			pthread_mutex_unlock(&philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philosopher_dead(t_core *philo, size_t time_to_die)
{
	size_t	current_time;

	current_time = getcurrenttime();
	pthread_mutex_lock(&philo->last_meal_time_m);
	if (current_time - philo->last_meal_time >= time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_time_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_time_m);
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_if_dead(table->philo) == 1 || check_eat(table->philo) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}
