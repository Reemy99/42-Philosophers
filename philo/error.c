/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:48:59 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/04 13:49:36 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int num)
{
	if (num == 1)
		printf("Error Enter a valid number\n");
	else if (num == 2)
		printf("Error Negative argument\n");
	else if (num == 3)
		printf("Error Memory Allocation Failed\n");
	else if (num == 4)
		printf("Error Mutex initiation Failed\n");
	else if (num == 5)
		printf("philo 1 has Died, there is just one fork\n");
	else if (num == 6)
		printf("Error Thread Creation Failed\n");
	else if (num == 7)
		printf("Error: enter [4] arguments at least\n");
}
