/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:03:25 by mianni            #+#    #+#             */
/*   Updated: 2024/10/02 15:43:21 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	getcurrenttime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putendl_fd("Error function gettimeofday()\n", 2), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_sleep(size_t milliseconds)
{
	size_t	start_time;

	start_time = getcurrenttime();
	while ((getcurrenttime() - start_time) < milliseconds)
		usleep(500);
	return (0);
}

void	print_message(char *str, t_core *philos, int id)
{
	size_t	time;

	if (philos->table->dead_flag == 1)
		return ;
	pthread_mutex_lock(&philos->table->write_lock);
	time = getcurrenttime() - philos->table->start_time;
	if (id > -1)
		printf("\033[38;5;214m%zu %d %s\033[0m\n", time, id + 1, str);
	pthread_mutex_unlock(&philos->table->write_lock);
}
