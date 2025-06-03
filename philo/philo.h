/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <fleite-j@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 03:42:55 by fleite-j          #+#    #+#             */
/*   Updated: 2025-05-21 03:42:55 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MSG "ERROR: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> Optional: \
<number_of_times_each_philosopher_must_eat>\n"

typedef struct s_philo
{
	unsigned int	id;
	struct s_data	*data;
	unsigned long	last_meal;
	unsigned int	meals;
}				t_philo;

typedef struct s_data
{
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	is_dead;
	unsigned long	start_time;
	unsigned int	nbr_of_meals;
	unsigned int	ate_enough;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
}				t_data;

//src
////data_handler
long	get_time(void);
void	safe_usleep(unsigned long duration, t_philo *philo);
int		create_resources(t_data *data);
void	free_all(t_data *data);
////philosopher_creation
int		init_data(t_data *data, int c, char **v);
int		philo_creation(t_data *data);
/////philo_behavior
int		philo_behavior(t_philo *philo, char *action);
int		eat_time(t_philo *philo);
int		sleep_time(t_philo *philo);
int		think_time(t_philo *philo);
////philo_monitoring
int		should_stop(t_data *data);
void	*monitor_routine(void *arg);
////fork
int		take_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);
int		release_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);
void	cleanup_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);
////philo_utils
int		parse_args(t_data *data, int c, char *v[]);
int		ft_strcmp(const char *s1, const char *s2);
#endif
