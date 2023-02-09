/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:24:06 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/05 21:20:28 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Resetting the statue of the forks to (0) after finish eating.
void	return_forks(t_ph_d *ph_d)
{
	/* Handle the case where the philosopher is eating more than the number of times specified */
	handle_greedy_philo_eat(ph_d);
	
	/* Lock the left fork */
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
	
	/* Set the state of the left fork to be not in use */
	ph_d->pro_d->forks_state[ph_d->left_fork] = 0;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	
	/* Lock the right fork */
	pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
	
	/* Set the state of the right fork to be not in use */
	ph_d->pro_d->forks_state[ph_d->right_fork] = 0;
	pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


static int	start_eating(t_ph_d *ph_d, int flag)
{
	ph_d->pro_d->forks_state[ph_d->right_fork] = ph_d->philo_pos;
	ph_d->pro_d->forks_state[ph_d->left_fork] = ph_d->philo_pos;
	// Check the value of `flag` and unlock the right and left forks accordingly
	if (flag == 1)
	{
		// Unlock the left fork first and then unlock the right fork
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	}
	else if (flag == 2)
	{
		// Unlock the right fork first Then unlock the left fork
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
	}
	// Check if the philosopher is still alive
	if (!still_alive(ph_d))
		return (0);
	printing_state(ph_d, ": has taken a fork 🍴", Y);
	printing_state(ph_d, ": has taken a fork 🍴🍴", Y);
	printing_state(ph_d, ": is eating 🍝", G);
	// Assign the time of the eating action to `last_eating`
	ph_d->last_eating = current_time();
	// Pause the program for the time required to eat
	if (!usleep_pro(ph_d->pro_d->time_to_eat, ph_d))
		return (0);
	ph_d->meals++;
	return (1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Check if the philosopher is still alive
	// Check if the philosopher is trying to grab greedy forks
	// Lock the right and left forks 
	// Check if both forks are available
	// Start eating if both forks are available
	// Return the forks after eating
	// Sleep after eating
static int one_way(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	if (!check_greedy_odd(ph_d))
	{
		pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
		pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
		if (ph_d->pro_d->forks_state[ph_d->right_fork] == 0
			&& ph_d->pro_d->forks_state[ph_d->left_fork] == 0)
		{
			if (!start_eating(ph_d, 1))
				return (0);
			return_forks(ph_d);
			if (!sleeping(ph_d))
				return (0);
			return (1);
		}
		else
		{
			// Unlock the forks if they're not available
			pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
			pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
			// Check if the philosopher is still alive
			if (!still_alive(ph_d))
				return (0);
		}
		// pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
		// pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
	}
	return (1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static int	other_way(t_ph_d *ph_d)
{
	if (!still_alive(ph_d))
		return (0);
	if (!check_greedy_even(ph_d))
	{
		pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->left_fork]);
		pthread_mutex_lock(&ph_d->pro_d->forks[ph_d->right_fork]);
		if (ph_d->pro_d->forks_state[ph_d->right_fork] == 0
			&& ph_d->pro_d->forks_state[ph_d->left_fork] == 0)
		{
			if (!start_eating(ph_d, 2))
				return (0);
			return_forks(ph_d);
			if (!sleeping(ph_d))
				return (0);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->right_fork]);
			pthread_mutex_unlock(&ph_d->pro_d->forks[ph_d->left_fork]);
			if (!still_alive(ph_d))
				return (0);
		}
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int	eating(t_ph_d *ph_d)
{
	if (ph_d->philo_pos % 2 == 0)
	{
		if (one_way(ph_d) == 0)
			return (0);
	}
	else
	{
		if (other_way(ph_d) == 0)
			return (0);
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
