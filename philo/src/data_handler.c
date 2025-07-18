/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <fleite-j@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 03:41:44 by fleite-j          #+#    #+#             */
/*   Updated: 2025-05-21 03:41:44 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	safe_usleep(unsigned long duration, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		usleep(5);
		if (should_stop(philo->data))
			return ;
	}
}

int	create_resources(t_data *data)
{
	unsigned int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	data->threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!data->philos || !data->threads || !data->forks)
	{
		printf("Error: failure to allocate memory!\n");
		free_all(data);
		return (1);
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i > 0)
				pthread_mutex_destroy(&data->forks[i]);
			free_all(data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_all(t_data *data)
{
	unsigned int	i;

	if (data)
	{
		if (data->philos)
			free(data->philos);
		data->philos = NULL;
		if (data->threads)
			free(data->threads);
		data->threads = NULL;
		if (data->forks)
		{
			i = 0;
			while (i < data->nbr_of_philos)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		data->forks = NULL;
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->state_mutex);
	}
}
