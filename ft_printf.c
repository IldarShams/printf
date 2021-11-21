/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaegan <smaegan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:52:12 by smaegan           #+#    #+#             */
/*   Updated: 2021/11/21 18:22:40 by smaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*get_arr(long n2, long i, int size, int sign)
{
	char	*res;

	res = malloc(size + 1);
	if (res == NULL)
		return (NULL);
	size = 0;
	if (sign == -1)
		res[size++] = '-';
	while (i > 0)
	{
		res[size] = (n2 / i % 10) + 48;
		size++;
		i /= 10;
	}
	res[size] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	long		i;
	int			sign;
	char		*res;
	int			size;
	long		n2;

	n2 = n;
	size = 1;
	sign = 1;
	i = 10;
	if (n2 < 0)
	{
		n2 *= -1;
		sign = -1;
		size++;
	}
	while (n2 / i > 0)
	{
		i *= 10;
		size++;
	}
	i /= 10;
	res = get_arr(n2, i, size, sign);
	return (res);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	spec_proc(char *str, int *i, void *arg)
{
	char	*s;
	int		n;

	n = 0;
	printf("%u\n", (unsigned int)arg);
	if (str[*i] == '\0')
		return (i);
	i++;
	if (str[*i] == 'd' || str[*i] == 'i' || str[*i] == 'p' || str[*i] == 'u')
		ft_putstr_fd(ft_itoa((int)arg), 0);
	else if (str[*i] == 'c')
		ft_putchar_fd((char)arg, 0);
	else if (str[*i] == 's')
		ft_putstr_fd((char *)arg, 0);
	else if (str[*i] == 'p')
		ft_putstr_fd(ft_itoa((int)arg), 0);
	else if (str[*i] == 'u')
		ft_putstr_fd(ft_itoa((unsigned int)arg), 0);
	return (n);
}

int	ft_printf(const char *str, ...)
{
	size_t	n;
	int		i;
	va_list	args;

	va_start(args, str);
	n = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != '%' && str[i] != '\0')
			ft_putchar_fd(str[i++], 0);
		else if (str[i] != '\0' && (str[i + 1] == 'd' || str[i + 1] == 'i'
				|| str[i + 1] == 'c' || str[i + 1] == 's'
				|| str[i + 1] == 'p' || str[i + 1] == 'u' || str[i + 1] == 'x'
				|| str[i + 1] == 'X' || str[i + 1] == '%'))
			i = spec_proc(str, &i, va_arg(args, int));
	}
	va_end(args);
	return (n);
}

int	main(void)
{
	printf("///%u///%d\n", -12, 777);
	ft_printf("///%u///%d\n", -12, 777);
	return (0);
}
