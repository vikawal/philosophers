/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:41:54 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/12 12:27:50 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//how we check if the philosopher is dead
int	is_dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_check_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_check_lock), 1);
	pthread_mutex_unlock(philo->dead_check_lock);
	return (0);
}

void	*routine_of_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		new_usleep(philo, philo->time_to_eat / 2);
	while (!is_dead_loop(philo))
	{
		eating_routine(philo);
		sleeping_routine(philo);
		thinking_routine(philo);
	}
	return (pointer);
}

//Arguments:
// - &checker: Pointer to the pthread_t variable that will hold the thread ID 
//of the created thread.
// - NULL: Default thread attributes.
//  -&check_routine_monitor: Function to be executed by the thread.
// -program->philos: Argument passed to the check_routine_monitor function, 
//which is array of philosopher structures.

int	creating_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	checker;
	int			i;

	if (pthread_create(&checker, NULL, &check_routine_monitor,
			program->philos) != 0)
		finish_and_destroy("ERROR: creating thread failed", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine_of_philo,
				&program->philos[i]) != 0)
			finish_and_destroy("ERROR: creating thread failed",
				program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(checker, NULL) != 0)
		finish_and_destroy("ERROR: joining thread failed", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			finish_and_destroy("ERROR: joining thread failed", program, forks);
		i++;
	}
	return (0);
}
