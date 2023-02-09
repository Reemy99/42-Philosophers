/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:27:59 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/05 21:18:13 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_pro_d	pro_d;

	pro_d.time_to_start = current_time();
	if (ac < 4)
	{
		print_error(7);
		return (0);
	}
	else if (ac == 5 || ac == 6)
	{
		if (!parse_argument(av))
			return (0);
		move_to_struct(av, &pro_d);
		if (!philosopher(&pro_d))
			return (0);
		destroy_free(&pro_d);
	}
	else
		print_error(7);
	return (EXIT_SUCCESS);
}
