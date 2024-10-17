/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:04:30 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 15:40:54 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_utils/philosophers.h"

void	thinking_bonus(t_core *philos)
{
	if (philos->table->dead_flag == 1)
		return ;
	print_message("is thinking 📖", philos, philos->id);
}

void	sleeping_bonus(t_core *philos)
{
	if (philos->table->dead_flag == 1)
		return ;
	print_message("is sleeping 😴", philos, philos->id);
	ft_sleep(philos->table->time_to_sleep);
}

bool	eating_bonus(t_core *philo)
{
	if (philo->meal_eaten >= philo->table->numbers_of_eats
		&& philo->table->numbers_of_eats != -1)
		return (philo->table->dead_flag = 1, false);
	sem_wait(philo->table->fork_semaphore);
	print_message("has taken a fork", philo, philo->id);
	if (philo->table->numbers_of_philos == 1)
	{
		ft_sleep(philo->table->time_to_die);
		sem_post(philo->table->fork_semaphore);
		return (false);
	}
	sem_wait(philo->table->fork_semaphore);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating 🍝", philo, philo->id);
	sem_wait(philo->table->sem_last_meal);
	philo->last_meal_time = getcurrenttime();
	philo->meal_eaten++;
	sem_post(philo->table->sem_last_meal);
	ft_sleep(philo->table->time_to_eat);
	philo->eating = 0;
	sem_post(philo->table->fork_semaphore);
	return (sem_post(philo->table->fork_semaphore), true);
}
