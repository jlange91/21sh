#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>


typedef struct		s_fd
{
	int				fd;
	int				oldfd;
	struct s_fd		*next;
}					t_fd;


typedef struct		t_redir
{
	t_fd			*replace;
	t_fd			*save;
}					t_redir;

void test_fd()
{
	for(int i = 3; i < 10000; i++)
	{
		if (close(i)) {
		} else {
			    dprintf(2, "%d, ", i);
				 }
	}
	dprintf(2, "etait ouvert\n");
}



t_fd	*ft_create_fd(int value1, int value2)
{
	t_fd *fd;

	fd = (t_fd*)malloc(sizeof(t_fd) * 1);
	if (!fd)
		return (NULL);
	fd->fd = value1;
	fd->oldfd = value2;
	fd->next = NULL;
	return (fd);
}

void	ft_add_fd(t_fd **fd, int value1, int value2)
{
	t_fd *begin;
	t_fd *new;

	begin = *fd;
	new = ft_create_fd(value1, value2);
	if (!begin)
		*fd = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
}

void		ft_tmp(t_fd *fd, int oldfd, int newfd)
{
	fd->fd = oldfd;
	oldfd = dup2(oldfd, newfd);
}

int main()
{
	t_redir	r;
	t_fd *tmp;
	t_fd *begin;

	r.replace = NULL;
	r.save = NULL;

	ft_add_fd(&r.save, dup(1), 1);
	ft_add_fd(&r.save, dup(1), 1);
	ft_add_fd(&r.replace, open("test", O_RDWR | O_CREAT, 0644), 0);
	ft_add_fd(&r.replace, open("test1", O_RDWR | O_CREAT, 0644), 0);
	ft_add_fd(&r.replace, open("test2", O_RDWR | O_CREAT, 0644), 0);
	ft_add_fd(&r.replace, open("test3", O_RDWR | O_CREAT, 0644), 0);
	ft_add_fd(&r.replace, open("test4", O_RDWR | O_CREAT, 0644), 0);
	ft_add_fd(&r.replace, open("test5", O_RDWR | O_CREAT, 0644), 0);
	begin = r.replace;
	while (begin)
	{
		ft_tmp(begin, begin->fd, 1);
		begin = begin->next;
	}

	begin = r.replace;	
	while (begin)
	{
		printf("{%d}\n", begin->fd);
		begin = begin->next;
	}

	begin = r.replace;	
	while (begin)
	{
		close(begin->fd);
		begin = begin->next;
	}
	write(1, "test", 4);
	
	begin = r.save;
	while (begin)
	{
		dup2(begin->fd, begin->oldfd);
		close(begin->fd);
		begin = begin->next;
	}
	test_fd();
	write(1, "test", 4);
}
