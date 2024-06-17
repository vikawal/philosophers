/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:52 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:30:54 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argument_digit(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_input(char *argv[])
{
	if (philo_ft_atoi(argv[1]) < 1 || check_argument_digit(argv[1]) == 1
		|| philo_ft_atoi(argv[1]) > 999)
		return (write(2, "Error: Invalid number of philosophers.\n", 40), 1);
	if (philo_ft_atoi(argv[2]) < 1
		|| check_argument_digit(argv[2]) == 1)
		return (write(2, "Error: Invalid time to DIE.\n", 29), 1);
	if (philo_ft_atoi(argv[3]) < 1 || check_argument_digit(argv[3]) == 1)
		return (write(2, "Error: Invalid time to EAT.\n", 29), 1);
	if (philo_ft_atoi(argv[4]) < 1 || check_argument_digit(argv[4]) == 1)
		return (write(2, "Error: Invalid time to SLEEP.\n", 31), 1);
	if (argv[5] && (philo_ft_atoi(argv[5]) < 1
			|| check_argument_digit(argv[5]) == 1))
		return (write(2, "Error: Invalid number of times to EAT \
			for each philosopher.\n", 61), 1);
	return (0);
}

void	allocation_error_free(t_philo *philos, pthread_mutex_t *forks)
{
	write(2, "Error: Failed to allocate memory.\n", 35);
	free(philos);
	free(forks);
}

int	main(int argc, char *argv[])
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				amount_of_philos;

	if (argc != 6 && argc != 5)
		return (write(2, "Error: Invalid number of arguments.\n", 36), 1);
	if (check_valid_input(argv) == 1)
		return (1);
	amount_of_philos = philo_ft_atoi(argv[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * amount_of_philos);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* amount_of_philos);
	if (!philos ||!forks)
		return (allocation_error_free(philos, forks), 1);
	start_program_init(&program, philos);
	start_forks_locks(forks, philo_ft_atoi(argv[1]));
	start_philosophers(philos, &program, forks, argv);
	creating_threads(&program, forks);
	finish_and_destroy(NULL, &program, forks);
	free(philos);
	free(forks);
	return (0);
}
