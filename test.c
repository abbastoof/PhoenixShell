#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex[1];

void	*routine(void *data)
{
	int	*n = (int *)data;

	if (*n == 0)
		printf("thread one\n");
	else
		printf("second thread\n");
	return (NULL);
}

int	main()
{
	pthread_t tr[2];
	int	i = 0;

	pthread_mutex_init(mutex, NULL);
	pthread_mutex_lock(mutex);
	pthread_create(&tr[i],NULL,&routine, &i);
	pthread_mutex_unlock(mutex);
	i += 1;
	pthread_create(&tr[i],NULL,&routine, &i);
	pthread_join(tr[0], NULL);
	pthread_join(tr[1], NULL);
	pthread_mutex_destroy(mutex);
}