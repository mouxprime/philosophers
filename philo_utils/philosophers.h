/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:04:51 by mianni            #+#    #+#             */
/*   Updated: 2024/10/10 11:23:15 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	pthread_t		monitor;
	size_t			time_to_eat;
	size_t			time_to_think;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			start_time;
	int				numbers_of_philos;
	int				numbers_of_eats;
	int				dead_flag;
	int				number_of_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*dead_lock;
	sem_t			*fork_semaphore;
	sem_t			*sem_write;
	sem_t			*sem_dead;
	sem_t			*sem_meal;
	sem_t			*sem_last_meal;
	struct s_core	*philo;
	sem_t			*stop;
	pid_t			*process;
	sem_t			*one_is_dead;
	sem_t			*all_meat_eaten;
	int				all_eaten;
}					t_table;

typedef struct s_core
{
	int				meal_eaten;
	int				id;
	int				pid;
	int				eating;
	size_t			last_meal_time;
	pthread_mutex_t	last_meal_time_m;
	pthread_t		thread_id;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_table			*table;
	pthread_mutex_t	dead_lock;
}					t_core;

void				*setup_struct(void);

bool				check_argv(char *argv);

bool				parsing(int argc, char **argv, t_table *data);

void				*routine(void *data);

void				create_threads(t_table *table, t_core *core);

bool				init_mutex(t_table *table);

void				init_threads(t_table *table);

int					ft_sleep(size_t milliseconds);

void				print_message(char *str, t_core *philos, int id);

void				sleeping(t_core *philos);

void				thinking(t_core *philos);

size_t				getcurrenttime(void);

bool				eating(t_core *philo);

void				setup_struct_data(int argc, char **argv, t_table *table);

int					check_eat(t_core *philo);

void				attribution_mutex(t_table *table);

void				*monitor(void *arg);

void				kill_thread(t_core *philo);

bool				check_die(t_core *philo);

int					check_if_dead(t_core *philos);

int					philosopher_dead(t_core *philo, size_t time_to_die);

int					dead_loop(t_core *philo);

void				ft_putendl_fd(char *s, int fd);

long				ft_atol(const char *nptr);

size_t				ft_strlen(const char *str);

int					ft_isdigit(int c);

void				clear_all(t_table *table);

void				destroy_all(t_table *table);
/////////////// BONUS //////////////////////
void				init_fork(t_table *table);

void				data_define(t_table *table);

void				setup_semaphores(t_table *table);

void				kill_child(t_core *philo);

void				*ft_check_death(void *arg);

void				*for_each_philo(t_core *philo);

void				close_sem(t_table *table);

void				*threads_philo(void *arg);

void				one_is_dead(t_table *table);

void				sleeping_bonus(t_core *philos);

void				thinking_bonus(t_core *philos);

bool				eating_bonus(t_core *philo);

#endif
