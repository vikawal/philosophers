/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:11:05 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:36:40 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_input(t_philo *philo, char *argv[])
{
	philo->time_to_die = philo_ft_atoi (argv[2]);
	philo->time_to_eat = philo_ft_atoi (argv[3]);
	philo->time_to_sleep = philo_ft_atoi (argv[4]);
	philo->num_of_philos = philo_ft_atoi (argv[1]);
	if (argv[5])
		philo->num_times_to_eat = philo_ft_atoi (argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	start_philosophers(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char *argv[])
{
	int		i;

	i = 0;
	while (i < philo_ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating_now = 0;
		philos[i].times_eaten = 0;
		start_input(&philos[i], argv);
		philos[i].start_time = current_time_stamp();
		philos[i].last_meal = current_time_stamp();
		philos[i].printing_lock = &program->printing_lock;
		philos[i].dead_check_lock = &program->dead_check_lock;
		philos[i].eat_lock = &program->eat_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
		{
			philos[i].left_fork = &forks[philos[i].num_of_philos - 1];
			philos[i].right_fork = &forks[i];
		}
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	start_forks_locks(pthread_mutex_t *forks, int philo_number)
{
	int	i;

	i = 0;
	while (i < philo_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

//now all together
void	start_program_init(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->printing_lock, NULL);
	pthread_mutex_init(&program->dead_check_lock, NULL);
	pthread_mutex_init(&program->eat_lock, NULL);
}
