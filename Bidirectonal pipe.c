#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
int pid;
int fd1[2]={0};
int fd2[2]={0};
pipe(fd1);
pipe(fd2);
pid=fork();
if(pid>0)
{
char msg[]={"Msg from parent"};
char rmsg[50]={0};
write(fd1[1],msg,sizeof(msg));
read(fd2[0],rmsg,sizeof(rmsg));
printf("PP:%s\n",rmsg);
wait(NULL);
}
else if(pid==0)
{
char msg[]={"Msg From Child"};
char rmsg[50]={0};
write(fd2[1],msg,sizeof(msg));
read(fd1[0],rmsg,sizeof(rmsg));
printf(",CP:%s\n",rmsg);
}
return 0;
}
