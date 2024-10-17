/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:11:17 by mianni            #+#    #+#             */
/*   Updated: 2024/10/08 15:13:32 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_utils/philosophers.h"

void	*routine(void *data)
{
	t_core	*philo;

	philo = (t_core *)data;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (dead_loop(philo) != 1)
	{
		eating_bonus(philo);
		sleeping_bonus(philo);
		thinking_bonus(philo);
	}
	sem_post(philo->table->one_is_dead);
	return (NULL);
}

int	dead_loop(t_core *philo)
{
	sem_wait(philo->table->sem_dead);
	if (philo->table->dead_flag == 1)
		return (sem_post(philo->table->sem_dead), 1);
	sem_post(philo->table->sem_dead);
	return (0);
}

void	kill_thread(t_core *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->numbers_of_philos)
	{
		pthread_detach(philo[i].thread_id);
		i++;
	}
}

void	kill_child(t_core *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->numbers_of_philos)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}
