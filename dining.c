#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<string.h>
int *forks=0;
sem_t *mutex=0;
void think(int id)
{
char buff[50]={0};
sprintf(buff,"\nPhilosoper:%d,Thinking\n",id);
write(1,buff,strlen(buff));
}

struct philo
{
int id;
sem_t *Lmutex;
sem_t *Rmutex;
};
void func(void *ptr)
{
int id=(((struct philo*)ptr)->id);
struct philo *leftFork=((struct philo*)ptr)->Lmutex;
struct philo *rightFork=((struct philo*)ptr)->Rmutex;
think(id);
sem_wait(leftFork);
char buff[50]={0};
sprintf(buff,"\nPicked left fork,id:%d",id);
write(1,buff,strlen(buff));
sleep(1);
sem_wait(rightFork);
char buff2[50]={0};
sprintf(buff2,"\nPicked right fork,id:%d",id);
write(1,buff2,strlen(buff2));
char buff3[50]={0};
sprintf(buff3,"\nPhilosoper:%d is Eating",id);
write(1,buff3,strlen(buff3));
sem_post(leftFork);
sem_post(rightFork);
pthread_exit(1);
}

int main()
{
int n=0;
printf("Enter the No. of philosophers:");
scanf("%d",&n);
pthread_t *thds=(pthread_t*) calloc(n,sizeof(pthread_t));
forks=(int*) calloc(n,sizeof(int));
mutex=(sem_t*) calloc(n,sizeof(sem_t));
for(int i=0;i<n;i++)
{forks[i]=1;
sem_init(&mutex[i],0,1);
}
struct philo *ptr=(struct philo*) calloc(n,sizeof(struct philo));
for(int i=0;i<n-1;i++)
{
ptr[i].id=i;ptr[i].Lmutex=&mutex[i];ptr[i].Rmutex=&mutex[(i+1)%n];
pthread_create(&thds[i],0,(void*)func,(void*)&ptr[i]);
}
ptr[n-1].id=n-1;ptr[n-1].Lmutex=&mutex[0];ptr[n-1].Rmutex=&mutex[n-1];
pthread_create(&thds[n-1],0,(void*)func,(void*)&ptr[n-1]);
for(int i=0;i<n;i++){
pthread_join(thds[i],0);
}
return 0;
}
