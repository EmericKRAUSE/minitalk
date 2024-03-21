/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:27 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/21 11:45:57 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"

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
		usleep(1000);
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

int main(int argc, char **argv)
{
	pid_t	pid;
	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	send_signal(argv[2], pid);
	return (0);
}