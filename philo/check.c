/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:19:49 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/05 21:21:29 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_greedy_odd(t_ph_d *ph_d)
{
	// Lock the right fork and lock the left fork
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	//Check if either the left | right fork was taken by the philos with same pos
	if (ph_d->pro_d->greedy_forks[ph_d->left_fork] == ph_d->philo_pos
		|| ph_d->pro_d->greedy_forks[ph_d->right_fork] == ph_d->philo_pos)
	{
		// If yes, then unlock the left and right fork
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		// Return 1 indicating that the philosopher is greedy
		return (1);
	}
	// If not, then unlock the left and right fork
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	// Return 0 if the philosopher is not greedy
	return (0);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//checks if the philosopher is greedy or not
//If not, they unlock the left and right fork and return 0

int	check_greedy_even(t_ph_d *ph_d)
{
	// Lock the right fork and lock the left fork
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	//Check if either the left | right fork was taken by the philos with same pos
	if (ph_d->pro_d->greedy_forks[ph_d->left_fork] == ph_d->philo_pos
		|| ph_d->pro_d->greedy_forks[ph_d->right_fork] == ph_d->philo_pos)
	{
		// If yes, then unlock the left and right fork
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	return (0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int	still_alive(t_ph_d *ph_d)
{
	unsigned int	from_last_meal;
	pthread_mutex_lock(ph_d->pro_d->death);
	// Check if the program should stop or the philosopher has eaten enough */
	if (ph_d->pro_d->stop != 0 || ph_d->meals == ph_d->pro_d->meals_to_eat)
	{
		ph_d->panic = 1;	
		pthread_mutex_unlock(ph_d->pro_d->death);	
		return (0);
	}
	pthread_mutex_unlock(ph_d->pro_d->death);
	// Calculate the time passed since last meal */
	from_last_meal = current_time() - ph_d->last_eating;
	pthread_mutex_lock(ph_d->pro_d->death);
	// Check if enough time has passed since last meal and the program should not stop
	if (from_last_meal >= ph_d->pro_d->time_to_die
		&& ph_d->pro_d->stop == 0)
	{
		pthread_mutex_unlock(ph_d->pro_d->death);
		printing_state(ph_d, ": died ", R);
		pthread_mutex_lock(ph_d->pro_d->death);
		ph_d->pro_d->stop = 1;
		ph_d->panic = 1;
		pthread_mutex_unlock(ph_d->pro_d->death);
		return (0);
	}
	pthread_mutex_unlock(ph_d->pro_d->death);
	return (1);
}