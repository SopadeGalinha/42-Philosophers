/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:58:56 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/20 20:58:56 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void set_philo_env(int i, t_philo *philo, t_table *table);
static void	set_fts(t_philo *philo);


int	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (printf("Error creating philo: malloc failed\n"));
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->meal_count = 0;
	set_philo_env(i, table->philos[i], table);
	set_fts(table->philos[i]);
	log_message(table->philos[i], table, "has joined the table", ESC_BOLD_WHITE);
	return (0);
}

static void set_philo_env(int i, t_philo *philo, t_table *table)
{
	philo->args.nb_philo = table->args.nb_philo;
	philo->args.time_die = table->args.time_die;
	philo->args.time_eat = table->args.time_eat;
	philo->args.time_sleep = table->args.time_sleep;
	philo->args.nb_meals = table->args.nb_meals;

	philo->fork[0] = &table->forks[i];
	philo->fork[1] = &table->forks[(i + 1) % table->args.nb_philo];
}

static void	set_fts(t_philo *philo)
{
	if (philo->id % 2 == 0)
		printf("0\n");
	// philo->ft[0] = ft_eat;
	// philo->ft[1] = ft_sleep;
	// philo->ft[2] = ft_think;
}

int	get_time(t_table *table)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000)\
		+ (time.tv_usec / 1000) - (table->start_time.tv_sec));
}

void	log_message(t_philo *philo, t_table *table, char *log_msg, char *color)
{
	int	ms_since_start;

	//Lock print
	ms_since_start = get_time(table);
	printf("%s%d %d %s%s\n", color, ms_since_start, philo->id, log_msg, ESC_WHITE);
	//Unlock print
}