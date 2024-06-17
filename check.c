/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:04 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:25:58 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//how we check if the 1 philosopher is dead
int	dead_or_not(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (current_time_stamp() - philo->last_meal >= time_to_die
		&& philo->eating_now == 0)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

//how we check if any of philosophers died
int	if_any_philo_died(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (dead_or_not(&philos[i], philos[i].time_to_die))
		{
			info_message_print("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_check_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_check_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate_check(t_philo *philos)
{
	int	i;
	int	done_with_eating;

	i = 0;
	done_with_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].times_eaten >= philos[i].num_times_to_eat)
			done_with_eating++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (done_with_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_check_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_check_lock);
		return (1);
	}
	return (0);
}

//checking all routine tohether
void	*check_routine_monitor(void *pointer)
{
	t_philo		*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (if_any_philo_died(philos) == 1 || everyone_ate_check(philos) == 1)
			break ;
	}
	return (pointer);
}
