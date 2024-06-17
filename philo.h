/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:50:42 by vmyshko           #+#    #+#             */
/*   Updated: 2024/06/10 17:33:03 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id; //used
	int				eating_now; //used
	int				times_eaten; // used
	size_t			last_meal; //used
	size_t			time_to_die; //used, from input
	size_t			time_to_eat; // used, from input
	size_t			time_to_sleep; //used, from input
	size_t			start_time; //used
	int				num_of_philos; //used, from input
	int				num_times_to_eat; //used. optional. from input
	int				*dead; //used
	pthread_mutex_t	*right_fork; //used
	pthread_mutex_t	*left_fork; //used
	pthread_mutex_t	*printing_lock; //used
	pthread_mutex_t	*dead_check_lock; //used
	pthread_mutex_t	*eat_lock; //used
}					t_philo;
typedef struct s_program
{
	int				dead_flag; //used, how later?
	pthread_mutex_t	dead_check_lock; //used initialiazation
	pthread_mutex_t	eat_lock; //used initializatiojn
	pthread_mutex_t	printing_lock; //used initializatiojn
	t_philo			*philos; //used, more to undrstand
}					t_program;

int		philo_ft_atoi(char *str);
int		ft_strlen(char *str);
int		check_valid_input(char *argv[]);
size_t	current_time_stamp(void);
void	start_program_init(t_program *program, t_philo *philos);
void	start_forks_locks(pthread_mutex_t *forks, int philo_number);
void	start_philosophers(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char *argv[]);
void	info_message_print(char *str, t_philo *philo, int id);
int		new_usleep(t_philo *philo, size_t mil_sec);
void	thinking_routine(t_philo *philo);
void	sleeping_routine(t_philo *philo);
void	eating_routine(t_philo *philo);
void	*check_routine_monitor(void *pointer);
int		creating_threads(t_program *program, pthread_mutex_t *forks);
void	finish_and_destroy(char *str, t_program *program,
			pthread_mutex_t *forks);
int		is_dead_loop(t_philo *philo);

#endif