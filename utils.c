/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:48:18 by maabdull          #+#    #+#             */
/*   Updated: 2023/11/13 13:07:48 by maabdull         ###   ########.fr       */
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
