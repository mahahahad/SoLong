/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:48:18 by maabdull          #+#    #+#             */
/*   Updated: 2024/02/18 18:44:51 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(int n)
{
	char	result;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10);
		result = '0' + (n % 10);
		write(1, &result, 1);
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == (char)c)
			return ((char *)s + i);
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	final_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!final_str)
		return (NULL);
	while (s1[++i])
		final_str[i] = s1[i];
	while (s2[j])
		final_str[i++] = s2[j++];
	final_str[i] = '\0';
	return (final_str);
}

/// @brief
// Creates a substring from the string 's' starting from 'start' with the
// length 'len'
/// @param s
// The string to create a substring from
/// @param start
// The index from which to start creating the substring
/// @param len
// The number of characters to include in the substring
/// @return
// The newly created substring
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i != len)
		substr[i++] = s[start++];
	substr[len] = '\0';
	return (substr);
}

static int	count_words(const char *s, const char c)
{
	int	words;
	int	word_found;
	int	i;

	words = 0;
	word_found = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && !word_found)
		{
			word_found = 1;
			words++;
		}
		if (s[i] == c)
			word_found = 0;
	}
	return (words);
}

/// @brief
// Splits a string 's' by using 'c' as a delimiter
// All instances of the char 'c' are ignored
/// @param s
// The string to split
/// @param c
// The character to split based on
/// @return
// An array of the newly obtained strings
char	**ft_split(char const *s, char c)
{
	int		word_start_index;
	size_t	i;
	int		j;
	char	**strings;

	if (!s)
		return (NULL);
	strings = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	word_start_index = -1;
	i = -1;
	j = 0;
	while (++i != ft_strlen(s) + 1)
	{
		if ((s[i] == c || i == ft_strlen(s)) && word_start_index >= 0)
		{
			strings[j++] = ft_substr(s, word_start_index, i - word_start_index);
			word_start_index = -1;
		}
		if (s[i] != c && word_start_index < 0)
			word_start_index = i;
	}
	strings[j] = NULL;
	return (strings);
}

static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n)
	{
		n /= 10;
		digits++;
	}
	if (!digits)
		digits = 1;
	return (digits);
}

static int	check_sign(int n, char *str)
{
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	if (!n)
		str[0] = '0';
	return (n);
}

static int	last_digit(int n)
{
	if (n < 0)
		return (0 - (n % 10));
	else
		return (n % 10);
}

/// @brief
	// Fills 'n' bytes of 's' with the 0 character
	// Like memset but with 0 instead of a specific user provided character
/// @param s
	// The string to replace
/// @param n
	// The number of characters to replace
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	i = 0;
	if (n)
		while (i != n)
			str[i++] = '\0';
}

/// @brief
	// Dynamically allocate memory for 'count' elements with 'size' size
/// @param count
	// The number of elements to allocate
/// @param size
	// The size of each element
/// @return
	// A void pointer to this newly allocated memory
void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	// if (count < 0 || size < 0)
	// 	return (NULL);
	if ((size * count) > INT_MAX)
		return (NULL);
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}

/// @brief
	// Converts the integer 'n' into a string and returns it
/// @param n
	// The integer to convert
/// @return
	// The converted string value
char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		digits;

	digits = count_digits(n);
	i = digits;
	str = ft_calloc(digits + 1, sizeof(char));
	str[0] = '\0';
	if (!str)
		return (NULL);
	n = check_sign(n, str);
	while (i-- && n)
	{
		str[i] = last_digit(n) + '0';
		n /= 10;
	}
	return (str);
}

void	print_arr(char **arr, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
