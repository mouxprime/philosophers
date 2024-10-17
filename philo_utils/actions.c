/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:04:30 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 16:05:04 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_core *philos)
{
	if (philos->table->dead_flag == 1)
		return ;
	print_message("is thinking 📖", philos, philos->id);
}

void	sleeping(t_core *philos)
{
	if (philos->table->dead_flag == 1)
		return ;
	print_message("is sleeping 😴", philos, philos->id);
	ft_sleep(philos->table->time_to_sleep);
}

bool	eating(t_core *philo)
{
	if (philo->table->dead_flag == 1)
		return (false);
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->table->numbers_of_philos == 1)
	{
		ft_sleep(philo->table->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating 🍝", philo, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(&philo->last_meal_time_m);
	philo->last_meal_time = getcurrenttime();
	pthread_mutex_unlock(&philo->last_meal_time_m);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_sleep(philo->table->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}
