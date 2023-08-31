/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:01:17 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/24 11:01:17 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	log_message(t_philo *philo, char *log_msg, char *color)
{
	int	t_stmp;

	pthread_mutex_lock(philo->print_zone);
	t_stmp = get_time(philo->args.start);
	printf("%s%d %d %s%s\n", color, t_stmp, philo->id, log_msg, ESC_BOLD_WHITE);
	pthread_mutex_unlock(philo->print_zone);
}

int	get_time(int start_time)
{
	struct timeval	time;
	int				time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	time_ms -= start_time;
	return (time_ms);
}

void	*clean_table(t_table **table)
{
	int	i;

	if (!table)
		return (NULL);
	pthread_mutex_destroy(&(*table)->print_zone);
	pthread_mutex_destroy(&(*table)->is_over_lock);
	if ((*table)->forks)
	{
		i = -1;
		while (++i < (*table)->args.nb_philo)
			pthread_mutex_destroy(&(*table)->forks[i]);
		free((*table)->forks);
	}
	if ((*table)->philos)
	{
		i = -1;
		while (++i < (*table)->args.nb_philo)
		{
			pthread_mutex_destroy(&(*table)->philos[i]->is_done_lock);
			free((*table)->philos[i]);
		}
		free((*table)->philos);
	}
	free(*table);
	return (NULL);
}

bool	meal_over(t_philo *philo)
{
	bool	is_over;
	bool	is_done;

	pthread_mutex_lock(philo->is_over_lock);
	is_over = *philo->is_over;
	pthread_mutex_unlock(philo->is_over_lock);
	if (is_over)
		return (true);
	pthread_mutex_lock(&philo->is_done_lock);
	is_done = philo->is_done;
	pthread_mutex_unlock(&philo->is_done_lock);
	if (is_done)
		return (true);
	return (false);
}
