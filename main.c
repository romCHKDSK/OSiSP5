#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <time.h>

#define SIZE 3
char *msg1 = "ADD";
char *msg2 = "DEL";
char *msg3 = "EST";
char *msg4 = "DLT";


void DO(int* p, int* q) {
    write(p[1],msg1,SIZE);
	char ch[SIZE];
	read(q[0],ch,SIZE);
	printf("%d send ADD\n",getpid());
	
	if(ch[0]=='E'){
		printf("new added by %d\n",getpid());
	}
	write(p[1],msg4,SIZE);
	
	read(q[0],ch,SIZE);
	if(ch[0]=='D'&&ch[1]=='E'){
		printf("to del by %d\n",getpid());
		return;
	}
	
}


int main(int argc, char **argv) {
	int p[2],q[2];
	if(pipe(p)==-1) return -1;
	if(pipe(q)==-1) return -1;
	pid_t pid;
	if((pid=fork())==0){
		DO(p,q);
		return 0;
	}
	sleep(1);
	while(1) {
        char ch[SIZE];
        read(p[0],ch,SIZE);
        if(ch[0]=='A'){
            printf("%d Read ADD \n",getpid());
            if((pid=fork())==0){
                DO(p,q);
                return 0;
            }
            write(q[1],msg3,SIZE);
        }else if(ch[0]=='D'&&ch[1]=='L'){
            printf("%d Read DLT \n",getpid());
            write(q[1],msg2,SIZE);
        }
	}
	return 0;
}
