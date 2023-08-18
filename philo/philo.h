/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:24:43 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/18 12:40:52 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>

typedef struct s_params
{
	int	n_philo;
	int	n_time_to_die;
	int	n_time_to_eat;
	int	n_time_to_sleep;
	int	n_meals;
}	t_params;

int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
bool	initialization(t_params *input, int argc, char **argv);

#endif
