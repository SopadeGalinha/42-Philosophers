#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - 48);
		c++;
	}
	return (res * s);
}

int main(int argc, char **argv)
{
    int n_meals;

    n_meals = 0;
    if (argc < 5 || argc > 6)
        return (printf("error na quantidade de argumentos"));
    if (ft_atoi(argv[1]) < 1)
        return (printf("Quantidade de filosofo invalida"));
    if (ft_atoi(argv[2]) < 1)
        return (printf("Tempo de vida invalido"));
    if (ft_atoi(argv[3]) < 1)
        return (printf("Tempo para comer invalido"));
    if (ft_atoi(argv[4]) < 1)
        return (printf("Tempo para dormir invalido"));
    if (argc == 6)
        n_meals = ft_atoi(argv[5]);
    
	printf("Numero de filosofos: %dms\n", ft_atoi(argv[1]));
	printf("Tempo ate morrer: %dms\n", ft_atoi(argv[2]));
	printf("Tempo para a refeicao: %dms\n", ft_atoi(argv[3]));
	printf("Tempo para dormir: %dms\n", ft_atoi(argv[4]));
    return (0);
}
