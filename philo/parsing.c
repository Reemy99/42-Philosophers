/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:28:19 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/04 16:47:48 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		print_error(1);
		// destroy_free(pro_d);
		return (0);
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			print_error(1);
			// destroy_free(pro_d);
			return (0);
		}
	}
	return (1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static int	check_valid_integer(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILO_N || ft_atoi(argv[1]) < 1)
	{
		printf("Wrong arguments, philosopher number is wrong.\n");
		//destroy_free(pro_d);
		return (0);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("philo 1 has Died, there is just one fork\n");
		// destroy_free(pro_d);
		return (0);
	}
	if (ft_atoi(argv[2]) < MIN_DIE_T)
	{
		printf("Wrong arguments, Dying time is too small.\n");
		// destroy_free(pro_d);
		return (0);
	}
	if (ft_atoi(argv[4]) < MIN_SLEEP_T || ft_atoi(argv[3]) < MIN_EAT_T)
	{
		printf("Wrong arguments, Wrong time.\n");
		// destroy_free(pro_d);
		return (0);
	}
	return (1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int	parse_argument(char **av)
{
	int	i;

	i = 1;
	while (av && av[i])
	{

		if (is_num(av[i]) == 0)
			//  printf("hhh\n");
			return (0);
		i++;
	}
	if (check_valid_integer(av) == 0)
		return (0);
	return (1);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//given a value to the struct
void	move_to_struct(char **av, t_pro_d *pro_d)
{
	pro_d->philos_num = ft_atoi(av[1]);
	pro_d->time_to_die = ft_atoi(av[2]);
	pro_d->time_to_eat = ft_atoi(av[3]);
	pro_d->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		pro_d->meals_to_eat = ft_atoi(av[5]);
	else
		pro_d->meals_to_eat = -1;
}
