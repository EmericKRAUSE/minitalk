/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:27 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/12 13:58:13 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int	ft_count(char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = (int)c;
	while (nb != 0)
	{
		nb /= 2;
		i++;
	}
	return (i);
}

char	*str_to_binary(char c)
{
	char	*result;
	int		i;
	int		nb;

	result = malloc(sizeof(char) * (ft_count(c) + 1));
	i = 0;
	nb = (int)c;
	while (nb != 0)
	{
		result[i] = (nb % 2) + 48;
		printf ("%c\n", result[i]);
		nb /= 2;
		i ++;
	}
	result[i] = '\0';
	return (result);
}

int main(int argc, char **argv)
{
	// if (argc != 2)
	// 	return (1);
	pid_t	pid = atoi(argv[1]);
	char	*str = str_to_binary(argv[2][0]);
	printf ("%s\n", str);
	kill(pid, SIGUSR1);
	return (0);
}