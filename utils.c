/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:41:45 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/26 12:35:26 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_isspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

long timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// void	ft_usleep(long time, t_data *data)
// {
// 	long start = timestamp();

// 	while (!)
// 	{
// 		if (timestamp() - start >= time)
// 			break;
// 		usleep(500);
// 	}
// }

int	is_dead(t_data *data)
{
	int die;
	
	pthread_mutex_lock(&data->dead_mutex);
	die = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (die);
}

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

void	*monitor(void *ac)
{
	t_philo	*philo;
	int		i;
	long	last_meal;

	philo = (t_philo *)ac;
	while(!is_dead(philo[0].data))
	{
		i = 0;
		while (i < philo[0].data->nb_philo)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			last_meal = philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if (timestamp() - last_meal > philo[i].data->time_to_die)
			{
				pthread_mutex_lock(&philo[i].data->print_mutex);
				printf("%ld %d died\n",
					 timestamp() - philo[i].data->start_time
				, philo[i].id);
				pthread_mutex_unlock(&philo[i].data->print_mutex);
				set_death(philo[i].data);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);  
}