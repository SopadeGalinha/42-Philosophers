/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:24:43 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/24 12:54:53 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

// Colors 
# define ESC_BOLD_RED		"\001\033[1;31m\002"
# define ESC_BOLD_GREEN		"\001\033[1;32m\002"
# define ESC_BOLD_YELLOW	"\001\033[1;33m\002"
# define ESC_BOLD_MAGENTA	"\001\033[1;35m\002"
# define ESC_BOLD_BLUE		"\001\033[1;34m\002"
# define ESC_BOLD_PURPLE	"\001\033[1;35m\002"
# define ESC_BOLD_CYAN		"\001\033[1;36m\002"
# define ESC_BOLD_WHITE		"\001\033[1;37m\002"
# define ESC_WHITE			"\001\033[0;37m\002"


// Error Messages
# define ERROR_ARG_TYPE		"Philo Error: arguments must be numeric"
# define ERROR_INV_NPHILO	"Error: Number of philosophers must be greater than 0"
# define ERROR_INV_TTDIE	"Error: Time to die must be greater than 0"
# define ERROR_INV_TTEAT	"Error: Time to eat must be greater than 0"
# define ERROR_INV_TTSLEEP	"Error: Time to sleep must be greater than 0"
# define ERROR_INV_NMEALS	"Error: Number of meals must be greater than 0"
# define ERROR_ARG_NUM		"Philo Error: invalid number of arguments\n"\
							"Try: ./philo <number_of_philos> <time_to_die> "\
							"<time_to_eat> <time_to_sleep> "\
							"\n[number_of_times_each_philosopher_must_eat] (optional)\n"

// actions 
enum actions{
	EAT,
	SLEEP,
	THINK
};

typedef struct s_table t_table;
typedef struct s_philo t_philo; 

// Struct to populate with arguments passed by user 
typedef struct s_args
{
	int				nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_meals;
}	t_args;

// Structure to represent a single philosopher
typedef struct s_philo
{
	int				id;
	int				meal_count;
	pthread_t		thread_id;
	pthread_mutex_t	*fork[2];
	t_args			args;
	void            (*ft[3])(struct s_philo *philo, t_table *table);
	long			last_meal;
	pthread_mutex_t	last_meal_lock;
	bool			is_done;
	pthread_mutex_t	is_done_lock;
	pthread_mutex_t	*print_zone;
	bool			*is_over;
	pthread_mutex_t	*is_over_lock;
}	t_philo;

// Struct to store all data to table settings
typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			**philos;
	t_args			args;
	struct timeval	start_time;
	bool			is_over;
	pthread_mutex_t	printzone;
	pthread_mutex_t	is_over_lock;
}	t_table;


int		ft_atoi(const char *str);
int		get_time(t_table *table);
int		check_args(int ac, char **av);
t_table	*init_table(int argc, char **argv);
int		create_philo(int i, t_table *table);
void    log_message(t_philo *philo, t_table *table, char *log_msg, char *color);
void	ft_think(t_philo *philo, t_table *table);
void	ft_sleep(t_philo *philo, t_table *table);
void	ft_eat(t_philo *philo, t_table *table);

#endif
