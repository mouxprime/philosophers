/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:11:17 by mianni            #+#    #+#             */
/*   Updated: 2024/10/10 11:40:32 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *data)
{
	t_core	*philo;

	philo = (t_core *)data;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (dead_loop(philo) != 1)
	{
		if (eating(philo) == false)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	dead_loop(t_core *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->table->dead_flag == 1)
		return (pthread_mutex_unlock(&philo->dead_lock), 1);
	pthread_mutex_unlock(&philo->dead_lock);
	return (0);
}

void	kill_thread(t_core *philo)
{
	pthread_detach(philo->thread_id);
}
