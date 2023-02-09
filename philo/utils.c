/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:38:16 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/05 12:38:50 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_greedy_philo_eat(t_ph_d *ph_d)
{
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	ph_d->pro_d->greedy_forks[ph_d->left_fork] = ph_d->philo_pos;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	ph_d->pro_d->greedy_forks[ph_d->right_fork] = ph_d->philo_pos;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//function returns the current time in milliseconds.
//The function converts the current time to milliseconds by multiplying 
//number of seconds by 1000 and adding the number of microseconds divided by 1000
//The resulting value, in milliseconds, is returned by the function.
unsigned int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void	printing_state(t_ph_d *ph_d, char *state, char *color)
{
	unsigned int	start_time;

	start_time = ph_d->pro_d->start_time;
	pthread_mutex_lock(ph_d->pro_d->death);
	pthread_mutex_lock(ph_d->pro_d->printing_mutex);
	if (!ph_d->panic && !ph_d->pro_d->stop
		&& ph_d->meals != ph_d->pro_d->meals_to_eat)
	{	
		printf("%s\033[1m %d [%d] %s\n", color, (current_time() - start_time),
			ph_d->philo_pos, state);
	}
	pthread_mutex_unlock(ph_d->pro_d->printing_mutex);
	pthread_mutex_unlock(ph_d->pro_d->death);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int	usleep_pro(unsigned int time_to_delay, t_ph_d *ph_d)
{
	unsigned int	now_time;

	now_time = current_time();
	if (!still_alive(ph_d))
		return (0);
	while ((current_time() - now_time) < (time_to_delay))
	{
		if (!still_alive(ph_d))
			return (0);
		usleep(100);
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Destroy and free the forks mutexes, and the print mutex.

void	destroy_free(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	while (i < pro_d->philos_num)
	{
		pthread_mutex_destroy(&pro_d->forks[i]);
		i++;
	}
	pthread_mutex_destroy(pro_d->printing_mutex);
	pthread_mutex_destroy(pro_d->death);
	pthread_mutex_destroy(pro_d->greedy_mutex);
	free(pro_d->forks);
	free(pro_d->ph_d);
	free(pro_d->printing_mutex);
	free(pro_d->death);
	free(pro_d->greedy_mutex);
	free(pro_d->forks_state);
	free(pro_d->greedy_forks);
	free(pro_d->philo_thread);
}
