/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <fleite-j@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 03:41:58 by fleite-j          #+#    #+#             */
/*   Updated: 2025-05-21 03:41:58 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	pair_philo(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	*left_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
		return (1);
	if (philo->data->nbr_of_philos == 1)
		return (1);
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->nbr_of_philos]);
	*right_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
	{
		return (1);
	}
	return (0);
}

static int	odd_philo(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->nbr_of_philos]);
	*right_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
		return (1);
	if (philo->data->nbr_of_philos == 1)
		return (1);
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	*left_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
	{
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	if (philo->id % 2 == 0)
		return (pair_philo(philo, left_fork, right_fork));
	else
	{
		safe_usleep(5, philo);
		return (odd_philo(philo, left_fork, right_fork));
	}
}

int	release_fork(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	if (*left_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		*left_fork = 0;
	}
	if (*right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->nbr_of_philos]);
		*right_fork = 0;
	}
	return (0);
}

void	cleanup_fork(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	if (*left_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		*left_fork = 0;
	}
	if (*right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->nbr_of_philos]);
		*right_fork = 0;
	}
}
