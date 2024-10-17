/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:56 by mianni            #+#    #+#             */
/*   Updated: 2024/10/10 11:40:04 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_utils/philosophers.h"

void	*ft_check_death(void *arg)
{
	t_core	*philo;
	int		i;

	philo = (t_core *)arg;
	i = philo->table->numbers_of_philos;
	while (1)
	{
		if (philo->table->one_is_dead > 0 || philo->table->all_eaten > i)
			break ;
	}
	sem_post(philo->table->one_is_dead);
	return (NULL);
}

void	*for_each_philo(t_core *philo)
{
	if (philo->table->one_is_dead > 0)
		return (NULL);
	sem_wait(philo->table->sem_dead);
	if (philo->last_meal_time + philo->table->time_to_die < getcurrenttime())
	{
		print_message("died	📌📌💀", philo, philo->id);
		sem_post(philo->table->one_is_dead);
		return (NULL);
	}
	sem_post(philo->table->sem_dead);
	sem_wait(philo->table->sem_dead);
	if ((philo->table->numbers_of_eats != -1)
		&& (philo->meal_eaten >= philo->table->numbers_of_eats))
	{
		philo->table->all_eaten++;
		return (NULL);
	}
	sem_post(philo->table->sem_dead);
	return (philo->table);
}

void	close_sem(t_table *table)
{
	free(table->philo);
	sem_close(table->sem_dead);
	sem_close(table->sem_last_meal);
	sem_close(table->sem_write);
	sem_close(table->stop);
	sem_close(table->fork_semaphore);
	sem_close(table->sem_meal);
	sem_close(table->one_is_dead);
	sem_close(table->all_meat_eaten);
	sem_unlink("/all_meal_eaten");
	sem_unlink("/one_is_dead");
	sem_unlink("/dead_lock");
	sem_unlink("/last_meal");
	sem_unlink("/write_lock");
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/meal");
}
