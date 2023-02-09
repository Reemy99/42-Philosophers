/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:49:59 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/04 17:17:26 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Excute sleeping then thinking only after eating
int	sleeping(t_ph_d *ph_d)
{
	/* Check if the philosopher is still alive */
	if (!still_alive(ph_d))
		return (0);
	/* Print the state of the philosopher: sleeping */
	printing_state(ph_d, ": is sleeping 💤", B);

	/* Wait for the specified amount of time for sleep */
	if (!usleep_pro(ph_d->pro_d->time_to_sleep, ph_d))
		return (0);
	/* Check if the philosopher is still alive */
	if (!still_alive(ph_d))
		return (0);
	/* Print the state of the philosopher: thinking */
	printing_state(ph_d, ": is thinking 🧠", P);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_ph_d	*ph_d;

	ph_d = (t_ph_d *)arg;
	ph_d->last_eating = current_time();
	while (ph_d->meals != ph_d->pro_d->meals_to_eat && !ph_d->panic)
	{
		pthread_mutex_lock(ph_d->pro_d->death); //if it ont stop
		if (!ph_d->pro_d->stop)
		{
			pthread_mutex_unlock(ph_d->pro_d->death); // unlock then eat
			if (!eating(ph_d))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(ph_d->pro_d->death);
			return (NULL);
		}
	}
	return (arg);
}