#ifndef PHILO_H
#define  PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_data
{
	int		nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meals;
	long	start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_mutex;
	
}	t_data;

typedef struct s_philo
{
	int	id;
	int	meals_eaten;
	long	last_meal;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
}	t_philo;

int	ft_atoi(const char	*str);
int	ft_isspace(int c);
long timestamp(void);
int init_fork(t_data *data);
t_philo	*init_philo(t_data *data);
void	*routine(void *ac);
void	think(t_philo *philo);
void	take_forks(t_philo	*philo);
void	eat(t_philo *philo);
void	put_forks(t_philo *philo);
void	sleep_philo(t_philo *philo);

#endif 