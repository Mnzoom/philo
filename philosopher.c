/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:28 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/25 14:02:08 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    think(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is thinking\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
void    take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n", timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n", timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
    else 
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n", timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n", timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}
void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = timestamp();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    usleep(philo->data->time_to_eat * 1000);
}
void    put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
void    sleep_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is sleeping\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    usleep(philo->data->time_to_sleep * 1000);
}

void    *routine(void *ac)
{
    t_philo *philo;
    philo = (t_philo *)ac;
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