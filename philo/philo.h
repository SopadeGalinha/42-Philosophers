/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:24:43 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/29 13:41:02 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# include <unistd.h>

typedef struct s_params
{
	int	n_philo;
	int	n_time_to_die;
	int	n_time_to_eat;
	int	n_time_to_sleep;
	int	n_meals;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				time_lst_meal;
	pthread_t		thread;
    pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	t_params		*table;
}	t_philo;


int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
bool	initialization(t_params *input, int argc, char **argv);

#endif
