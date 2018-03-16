#include "sh.h"

void    ft_sredir(t_shell *sh, int i)
{
    
}

int     redirection(t_shell *sh)
{
    int i;

    i = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == '>' && (i == 0 || sh->line[i - 1] != '\\'))
        {
            ft_sredir(sh, i);
        }
        i++;
    }
    return (0);
}