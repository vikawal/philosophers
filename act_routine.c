/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:54:38 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:23:37 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	info_message_print(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->printing_lock);
	time = current_time_stamp() - philo->start_time;
	if (!is_dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->printing_lock);
}

void	thinking_routine(t_philo *philo)
{
	info_message_print ("is thinking", philo, philo->id);
}

void	sleeping_routine(t_philo *philo)
{
	info_message_print ("is sleeping", philo, philo->id);
	new_usleep(philo, philo->time_to_sleep);
}

void	check_if_too_long_to_die(t_philo *philo)
{
	size_t	time_to_die_remaining;

	time_to_die_remaining = philo->time_to_die - (current_time_stamp()
			- philo->last_meal);
	if (time_to_die_remaining >= 2 * philo->time_to_eat
		&& philo->times_eaten != 0)
		new_usleep(philo, philo->time_to_eat);
}

//eating_routine -all forks & locks used here
void	eating_routine(t_philo *philo)
{
	if (philo->num_of_philos != 1)
		check_if_too_long_to_die(philo);
	pthread_mutex_lock(philo->right_fork);
	info_message_print ("took right fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		new_usleep(philo, philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	info_message_print ("took left fork", philo, philo->id);
	pthread_mutex_lock(philo->eat_lock);
	philo->times_eaten++;
	philo->last_meal = current_time_stamp();
	info_message_print ("is eating", philo, philo->id);
	pthread_mutex_unlock(philo->eat_lock);
	new_usleep(philo, philo->time_to_eat);
	philo->eating_now = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
