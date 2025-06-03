/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleite-j <fleite-j@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 03:42:21 by fleite-j          #+#    #+#             */
/*   Updated: 2025-05-21 03:42:21 by fleite-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	philo_status(t_data *data, unsigned int i, unsigned int *meals_done)
{
	long			last_meal;
	unsigned long	timestamp;

	pthread_mutex_lock(&data->state_mutex);
	if (data->is_dead || data->ate_enough)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	last_meal = data->philos[i].last_meal;
	if (get_time() - last_meal >= data->time_to_die + 6)
	{
		data->is_dead = 1;
		timestamp = get_time() - data->start_time;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lu %u died\n", timestamp, data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	if (*meals_done && data->philos[i].meals < data->nbr_of_meals)
		*meals_done = 0;
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

int	should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_mutex);
	stop = data->is_dead;
	if (!stop)
		stop = data->ate_enough;
	pthread_mutex_unlock(&data->state_mutex);
	return (stop);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
	unsigned int	i;
	unsigned int	meals_done;

	data = (t_data *)arg;
	while (6)
	{
		i = 0;
		meals_done = data->nbr_of_meals > 0;
		while (i < data->nbr_of_philos)
		{
			if (philo_status(data, i++, &meals_done))
				return (NULL);
		}
		if (meals_done && !data->is_dead)
		{
			pthread_mutex_lock(&data->state_mutex);
			data->ate_enough = 1;
			philo_behavior(&data->philos[0], "ate_enough");
			pthread_mutex_unlock(&data->state_mutex);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}
