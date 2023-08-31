/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:58:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/20 14:58:23 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	get_args(int ac, char **av, t_table *table);
static bool	get_forks_and_philos(t_table *table);

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	if (check_args(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (pthread_mutex_init(&table->print_zone, NULL) != 0)
		return (clean_table(&table));
	if (pthread_mutex_init(&table->is_over_lock, NULL) != 0)
		return (clean_table(&table));
	get_args(ac, av, table);
	if (!get_forks_and_philos(table))
		return (clean_table(&table));
	table->is_over = false;
	if (table->args.nb_philo == 1)
		table->is_over = true;
	return (table);
}

static void	get_args(int ac, char **av, t_table *table)
{
	table->args.start = get_time(0);
	table->args.nb_philo = ft_atoi(av[1]);
	table->args.time_die = ft_atoi(av[2]);
	table->args.time_eat = ft_atoi(av[3]);
	table->args.time_sleep = ft_atoi(av[4]);
	table->args.nb_meals = -1;
	if (ac == 6)
		table->args.nb_meals = ft_atoi(av[5]);
}

static void	set_env(t_philo *philo, t_table *table, int i)
{
	philo->args.start = table->args.start;
	philo->args.nb_philo = table->args.nb_philo;
	philo->args.time_die = table->args.time_die;
	philo->args.time_eat = table->args.time_eat;
	philo->args.time_sleep = table->args.time_sleep;
	philo->args.nb_meals = table->args.nb_meals;
	philo->print_zone = &table->print_zone;
	philo->fork[LEFT] = &table->forks[i];
	philo->fork[RIGHT] = &table->forks[(i + 1) % table->args.nb_philo];
	philo->is_over = &table->is_over;
	philo->is_over_lock = &table->is_over_lock;
	philo->ft[EAT] = ft_eat;
	philo->ft[SLEEP] = ft_sleep;
	philo->ft[THINK] = ft_think;
}

static bool	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (false);
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->meal_count = 0;
	table->philos[i]->is_done = false;
	if (pthread_mutex_init(&table->philos[i]->is_done_lock, NULL) != 0)
		return (false);
	set_env(table->philos[i], table, i);
	table->philos[i]->last_meal = get_time(table->args.start);
	if (pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL) != 0)
		return (false);
	log_message(table->philos[i], "has started the simulation", ESC_BOLD_WHITE);
	return (true);
}

static bool	get_forks_and_philos(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.nb_philo);
	if (!table->forks)
		return (false);
	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (false);
	table->philos = malloc(sizeof(t_philo) * table->args.nb_philo);
	if (!table->philos)
		return (false);
	i = -1;
	while (++i < table->args.nb_philo)
		if (!create_philo(i, table))
			return (false);
	return (true);
}
