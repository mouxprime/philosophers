/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:02:40 by mianni            #+#    #+#             */
/*   Updated: 2024/10/10 11:39:23 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_utils/philosophers.h"

void	data_define(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(table->numbers_of_philos * sizeof(t_core));
	while (i < table->numbers_of_philos)
	{
		table->philo[i].id = i;
		table->philo[i].meal_eaten = 0;
		table->philo[i].eating = 0;
		table->dead_flag = 0;
		table->all_eaten = 0;
		table->philo[i].last_meal_time = getcurrenttime();
		table->start_time = getcurrenttime();
		table->philo[i].table = table;
		i++;
	}
	setup_semaphores(table);
	init_fork(table);
}

void	setup_semaphores(t_table *table)
{
	sem_unlink("/dead_lock");
	sem_unlink("/last_meal");
	sem_unlink("/write_lock");
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/meal");
	table->sem_meal = sem_open("/meal", O_CREAT, 644, 1);
	if (table->sem_meal == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	table->fork_semaphore = sem_open("/forks", O_CREAT, 644,
			table->number_of_forks);
	if (table->fork_semaphore == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	table->stop = sem_open("/stop", O_CREAT, 644, 1);
	if (table->stop == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	table->sem_write = sem_open("/write_lock", O_CREAT, 644, 1);
	if (table->sem_write == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	table->sem_last_meal = sem_open("/last_meal", O_CREAT, 644, 1);
	if (table->sem_last_meal == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	one_is_dead(table);
}

void	one_is_dead(t_table *table)
{
	sem_unlink("/one_is_dead");
	table->sem_dead = sem_open("/dead_lock", O_CREAT, 644, 1);
	if (table->sem_dead == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	table->one_is_dead = sem_open("/one_is_dead", O_CREAT, 644, 0);
	if (table->one_is_dead == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
	sem_unlink("/all_meal_eaten");
	table->all_meat_eaten = sem_open("/all_meal_eaten", O_CREAT, 644, 0);
	if (table->all_meat_eaten == SEM_FAILED)
		return (ft_putendl_fd("Error semaphores\n", 2));
}

void	init_fork(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numbers_of_philos)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
			return (ft_putendl_fd("Error, fork() error, returned -1\n", 2));
		if (table->philo[i].pid == 0)
		{
			pthread_create(&table->philo[i].thread_id, NULL, threads_philo,
				&table->philo[i]);
			routine(&table->philo[i]);
			pthread_join(table->philo[i].thread_id, NULL);
		}
		i++;
		usleep(100);
	}
}

void	*threads_philo(void *arg)
{
	t_core	*philo;

	while (1)
	{
		philo = (t_core *)arg;
		sem_wait(philo->table->sem_dead);
		if (philo->last_meal_time
			+ philo->table->time_to_die < getcurrenttime())
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
			sem_post(philo->table->one_is_dead);
			philo->table->all_eaten++;
			return (NULL);
		}
		sem_post(philo->table->sem_dead);
	}
	return (&philo->table);
}
