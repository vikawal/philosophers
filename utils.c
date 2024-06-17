/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:51:53 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:47:27 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 't' && str[i] <= 'r'))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		if (number > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)number * sign);
}

// returns the timestamp in milliseconds by multiplying the number 
//of seconds (time.tv_sec) by 1000 to convert it to milliseconds 
//and adding the number of microseconds (time.tv_usec) divided by 1000 
//to convert them to milliseconds. The sum of these two values gives 
//the total time in milliseconds since the Unix epoch.
size_t	current_time_stamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: gettimeofday failed.\n", 27);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//The usleep(500) call within the sleeping function is used to 
//minimize CPU usage while waiting. It serves as a small sleep 
//interval to check if the desired amount of time has passed, 
//rather than continuously checking without any pause, 
//which would result in high CPU usage.
//________CHANGE BY YAN ISSUE___________________________________________________
int	new_usleep(t_philo *philo, size_t mil_sec)
{
	size_t	start;

	start = current_time_stamp();
	while ((current_time_stamp() - start) < mil_sec)
	{
		if (is_dead_loop(philo))
			return (1);
		usleep(500);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

void	finish_and_destroy(char *str, t_program *program,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->printing_lock);
	pthread_mutex_destroy(&program->eat_lock);
	pthread_mutex_destroy(&program->dead_check_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
