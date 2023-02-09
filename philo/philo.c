/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:02:11 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/07 21:49:34 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_memory(t_pro_d *pro_d)
{
	pro_d->ph_d = malloc(sizeof(t_ph_d) * pro_d->philos_num);
	pro_d->philo_thread = malloc(sizeof(pthread_t) * pro_d->philos_num);
	pro_d->forks = malloc(sizeof(pthread_mutex_t) * pro_d->philos_num);
	pro_d->printing_mutex = malloc(sizeof(pthread_mutex_t));
	pro_d->death = malloc(sizeof(pthread_mutex_t));
	pro_d->forks_state = ft_calloc(sizeof(int), pro_d->philos_num);
	pro_d->greedy_mutex = malloc(sizeof(pthread_mutex_t));
	pro_d->greedy_forks = ft_calloc(sizeof(int), pro_d->philos_num);
	if (!pro_d->ph_d || !pro_d->philo_thread || !pro_d->greedy_forks
		|| !pro_d->forks || !pro_d->printing_mutex || !pro_d->greedy_mutex
		|| !pro_d->death || !pro_d->forks_state)
	{
		printf("Allocation failed\n");
		return (0);
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// This function initializes the mutexes for a set of philosophers, represented by the struct t_pro_d. 
// The function initializes one mutex for each fork, as well as three additional mutexes for printing, death, and greed.
// If there is an error initializing any of the mutexes, the function will return 0 and print an error message. Otherwise,
// it will return 1 indicating success

static int	initialize_forks_mutexes(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	    // Initialize mutex for each fork
	while (i < pro_d->philos_num)
	{
		if (pthread_mutex_init(&pro_d->forks[i], NULL) != 0)
		{
			printf("Error Mutex initiation Failed\n");
			return (0);
		}
		i++;
	}
    // Initialize additional mutexes for printing, death, and greed
	if (pthread_mutex_init(pro_d->printing_mutex, NULL) != 0
		|| pthread_mutex_init(pro_d->death, NULL) != 0
		|| pthread_mutex_init(pro_d->greedy_mutex, NULL) != 0)
	{
		printf("Error Mutex initiation Failed\n");
		return (0);
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Set the philosopher's position
// Initialize the number of meals to 0
// Initialize the panic flag to 0
// Set the left fork position
// Set the right fork position

static void	init_philosophers_data(t_ph_d *ph_d, int i)
{
	ph_d->philo_pos = i + 1;
	ph_d->meals = 0;
	ph_d->panic = 0;
	ph_d->left_fork = i;
	ph_d->right_fork = (i + 1) % ph_d->pro_d->philos_num;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


static int	create_philo_threads(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	// Create a thread for each philosopher
	while (i < pro_d->philos_num)
	{
	// Create a thread and pass in the philosopher's data struct and the routine function
		pthread_create(&pro_d->philo_thread[i], NULL,
			philo_routine, (void *)&pro_d->ph_d[i]);
	// Sleep for 50 microseconds before creating the next thread to avoid overloading the system.
		usleep(50);
		i++;
	}
	i = 0;
	while (i < pro_d->philos_num)
	{
	    // Join all the threads
		if (pthread_join(pro_d->philo_thread[i], NULL) != 0)
		{
			printf("Error while joining the threads\n");
			return (0);
		}
		i++;
	}
	return (1);
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int	philosopher(t_pro_d *pro_d)
{
	int	i;

	i = 0;
	pro_d->stop = 0;
	allocate_memory(pro_d);
	if (!initialize_forks_mutexes(pro_d))
		return (0);
	while (i < pro_d->philos_num)
	{
		pro_d->ph_d[i].pro_d = pro_d;
		init_philosophers_data(&pro_d->ph_d[i], i);
		i++;
	}
	if (!create_philo_threads(pro_d))
		return (0);
	return (1);
}
