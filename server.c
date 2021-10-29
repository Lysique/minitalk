/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:36:29 by tamighi           #+#    #+#             */
/*   Updated: 2021/10/29 17:07:29 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	write_pid(pid_t	pid)
{
	unsigned int	length;
	char			c;

	length = 1;
	while (pid / length >= 10)
		length = length * 10;
	write(1, "pid : ", 6);
	while (length)
	{
		c = pid / length + '0';
		write(1, &c, 1);
		pid = pid % length;
		length = length / 10;
	}
	c = '\n';
	write(1, &c, 1);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 128;

	(void)context;
	if (sig == SIGUSR1)
		c += 0;
	else if (sig == SIGUSR2)
		c += i;
	i = i / 2;
	if (!i)
	{
		if (!c)
		{
			c = 10;
			kill(info->si_pid, SIGUSR1);
		}
		write(1, &c, 1);
		c = 0;
		i = 128;
	}
	usleep(75);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = &sig_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0))
		return (0);
	if (sigaction(SIGUSR2, &sa, 0))
		return (0);
	pid = getpid();
	write_pid(pid);
	while (1)
		pause();
}
