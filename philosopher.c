/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:28 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/27 17:16:49 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    think(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d is thinking\n",
        timestamp() - philo->data->start_time,
        philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }

    /* last_meal MIS A JOUR ICI */
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&philo->meal_mutex);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d is eating\n",
        timestamp() - philo->data->start_time,
        philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);

    usleep(philo->data->time_to_eat * 1000);

    pthread_mutex_lock(&philo->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
}

void    put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    sleep_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d is sleeping\n",
        timestamp() - philo->data->start_time,
        philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);

    usleep(philo->data->time_to_sleep * 1000);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d started routine\n",
        timestamp() - philo->data->start_time,
        philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);

    /* désynchronisation recommandée */
    if (philo->id % 2 == 0)
        usleep(100);

    if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time,
            philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }

    while (!is_dead(philo->data))
    {
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
    }
    return (NULL);
}
