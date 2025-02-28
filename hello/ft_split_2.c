#include "./parser.h"

static int _is_include(char c, char *charset)
{
    while (*charset)
    {
        if (*charset == c)
            return 1;
        charset++;
    }
    return 0;
}

static int	count_words(char const *str, char *c)
{
	int	in_word;
	int	counter;

	counter = 0;
	in_word = 0;
	while (*str)
	{
		while (*str && _is_include(*str, c))
			str++;
		while (*str && !_is_include(*str, c))
		{
			str++;
			in_word = 1;
		}
		if (in_word)
		{
			counter++;
			in_word = 0;
		}
	}
	return (counter);
}


static char	**zero_last(char **splited_strings, int index)
{
	splited_strings[index] = 0;
	return (splited_strings);
}

char	**ft_split_2(char const *s, char *charset)
{
	char	**splited_string;
	int		start_index;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	start_index = 0;
	splited_string = (char **)malloc((count_words(s, charset) + 1) * sizeof(char *));
	if (!splited_string)
		return (NULL);
	while (s && *s)
	{
		start_index = 0;
		while (*s && _is_include(*s, charset))
			s++;
		if (!*s)
			break ;
		while (*s && !_is_include(*s, charset) && ++start_index)
			s++;
		splited_string[index] = ft_substr(s - start_index, 0, start_index);
		if (!splited_string[index++])
			return (NULL);
	}
	return (zero_last(splited_string, index));
}
