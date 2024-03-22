/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:27 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/22 13:30:23 by ekrause          ###   ########.fr       */
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
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_control != 1)
			usleep(10);
	}
}

void	send_signal(char *str, pid_t pid)
{
	int	i;

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

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client <pid> <string>", 1);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_putendl_fd("Invalid PID", 1);
		exit(EXIT_FAILURE);
	}
	send_signal(argv[2], pid);
	while (1)
		sleep(1);
	return (0);
}