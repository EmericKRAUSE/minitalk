/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/13 15:18:58 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

char *string;
int	i = 0;

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		string = ft_strjoin(string, "1");
		i++;
	}
	else if (signum == SIGUSR2)
	{
		string = ft_strjoin(string, "0");
		i++;
	}
	if (i % 8 == 0)
	{
		int remainder;
		int base = 1;
		int number = 0;
		int binary = atoi(string);
		while (binary != 0)
		{
			remainder = binary % 10;
			number += remainder * base;
			base *= 2;
			binary /= 10;
		}
		char c = (int)number;
		write(1, &c, 1);
		string = ft_strdup(" ");
	}
}

int	main()
{
	pid_t	pid;

	pid = getpid();
	printf ("%d\n", pid);
	string = ft_strdup(" ");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		sleep(1);
	return (0);
}
