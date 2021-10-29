/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:28:22 by tamighi           #+#    #+#             */
/*   Updated: 2021/10/29 08:37:33 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (c[i])
	{
		nb = nb * 10;
		nb = nb + c[i] - '0';
		i++;
	}
	return (nb);
}

void	send_signals(int pid, unsigned char to_send)
{
	int	length;

	length = 128;
	while (length)
	{
		if (to_send / length == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		to_send = to_send % length;	
		length = length / 2;
	}
}

void	char_to_signal(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_signals(pid, str[i]);
		i++;
	}
	send_signals(pid, str[i]);
}

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Signals received\n", 17);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	pid = ft_atoi(argv[1]);
	char_to_signal(argv[2], pid);
}
