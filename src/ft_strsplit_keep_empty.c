
#include "libft.h"

static	int		ft_count_words(const char *str, char c)
{
    int	word;
    int	i;

    i = 0;
    word = 1;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == c)
            word++;
        i++;
    }
    if (str[0] != '\0')
        word++;
    return (word);
}

int		ft_strlen2(const char *str, char d)
{
    const char	*c;
    int		len;

    len = 0;
    c = str;
    if (!str)
        return (0);
    while (*c != '\0' && *c != d)
    {
        c++;
        len++;
    }
    return (len);
}

static	char	*ft_word(const char *str, char c, int *i)
{
    char	*s;
    int		k;

    if (!(s = (char *)malloc(sizeof(s) * (ft_strlen2(str + *i, c)))))
        return (NULL);
    k = 0;
    while (str[*i] != c && str[*i])
    {
        s[k] = str[*i];
        k++;
        *i += 1;
    }
    s[k] = '\0';
    return (s);
}

char			**ft_strsplit_keep_empty(const char *str, char c)
{
    int		i;
    int		j;
    int		wrd;
    char	**s;

    i = 0;
    j = 0;
    wrd = ft_count_words(str, c);
    if (!(s = (char **)malloc(sizeof(s) * (ft_count_words(str, c) + 2))))
        return (NULL);
    while (j < wrd && str[i])
    {
        s[j] = ft_word(str, c, &i);
        i++;
        j++;
    }
    s[j] = NULL;
    return (s);
}
