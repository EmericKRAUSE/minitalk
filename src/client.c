/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:27 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/25 14:13:05 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"

int	g_control;

void	send_bit(char c, pid_t pid)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_putendl_fd ("ERROR : cant send sig to pid", 1);
			exit(EXIT_FAILURE);
		}
		g_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_control != 1)
			pause();
	}
}

void	send_pid(char c, pid_t pid)
{
	int bit;

	bit = 7;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_putendl_fd ("ERROR : cant send sig to pid", 1);
			exit(EXIT_FAILURE);
		}
		g_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
			usleep(1000);
	}
}

void	send_signal(char *my_pid, char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (my_pid[i])
	{
		send_pid(my_pid[i], pid);
		i++;
	}
	i = 0;
	while (str[i])
	{
		send_bit(str[i], pid);
		i++;
	}
}

void	sig_usr(int signal)
{
	if (signal == SIGUSR1)
		g_control = 1;
	else if (signal == SIGUSR2)
	{
		ft_putendl_fd("Message received !", 1);
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char **argv)
{
	pid_t	pid;
	char	*my_pid;

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client <pid> <string>", 1);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_putendl_fd("Invalid PID", 1);
		exit(EXIT_FAILURE);
	}
	my_pid = ft_itoa(getpid());
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	send_signal(my_pid, argv[2], pid);
	return (0);
}