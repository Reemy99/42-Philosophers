/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:51 by realdahh          #+#    #+#             */
/*   Updated: 2023/02/09 22:21:36 by realdahh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

//~~~~~~~~~~~~~~~~~~ MAX NUMS ~~~~~~~~~~~~~~~~~~
# define MAX_PHILO_N 200
# define MIN_EAT_T 60
# define MIN_DIE_T 60
# define MIN_THINK_T 60
# define MIN_SLEEP_T 60
# define INT_MAX 2147483647

//~~~~~~~~~~~~~~~~~~ COLORES ~~~~~~~~~~~~~~~~~~
# define R "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define B "\033[0;34m"
# define P "\033[0;35m"
# define RESET "\033[0m"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct s_ph_d
{
	struct s_pro_d	*pro_d;
	int				panic;
	int				meals;
	int				philo_pos;
	int				left_fork;
	int				right_fork;
	unsigned int	last_eating;

}			t_ph_d;

typedef struct s_pro_d
{
	t_ph_d				*ph_d;
	int					stop;
	int					philos_num;
	int					meals_to_eat;
	int					*forks_state;
	int					*greedy_forks;
	pthread_t			*philo_thread;
	unsigned int		start_time;
	unsigned int		time_to_eat;
	unsigned int		time_to_die;
	unsigned int		time_to_sleep;
	unsigned int		time_to_start;
	pthread_mutex_t		*printing_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*greedy_mutex;
	pthread_mutex_t		*death;
}			t_pro_d;

int				usleep_pro(unsigned int time_to_delay, t_ph_d *ph_d);
unsigned int	current_time(void);
void			destroy_free(t_pro_d *pro_d);
void			printing_state(t_ph_d *ph_d, char *state, char *color);
void			handle_greedy_philo_eat(t_ph_d *ph_d);

int				philosopher(t_pro_d *pro_d);

int				parse_argument(char **av);
void			print_error(int num);
void			move_to_struct(char **av, t_pro_d *pro_d);

int				eating(t_ph_d *ph_d);
void			return_forks(t_ph_d *ph_d);

int				check_greedy_even(t_ph_d *ph_d);
int				check_greedy_odd(t_ph_d *ph_d);
int				still_alive(t_ph_d *ph_d);
int				sleeping(t_ph_d *ph_d);
void			*philo_routine(void *arg);

//~~~~~~~~~Libft~~~~~~~~~~~//
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *dest, size_t len);
int				ft_isdigit(int n);
int				ft_atoi(const char *str);

#endif