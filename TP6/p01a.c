// PROGRAMA p01.c 

#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h>
 
#define STDERR 2 
#define NUMITER 10000 

void * thrfunc(void * arg) 
{ 
  int i; 
  
  //FOR CHARS
  
  char c = *(char*) arg;
 
  	
  //FOR INTS
  //char c =  *(int*)arg + '0';
  
  fprintf(stderr, "Starting thread %c\n", c);  	
  
  for (i = 1; i <= NUMITER; i++) write(STDERR,&c,sizeof(char));
  
  return NULL; 
} 
int main() 
{
	int thread1 = 1, thread2 = 2;
	char t1 = '1';
	char t2 = '2';

 pthread_t ta, tb; 
 
 pthread_create(&ta, NULL, thrfunc, &t1);
 pthread_create(&tb, NULL, thrfunc, &t2);
 pthread_join(ta, NULL);
 pthread_join(tb, NULL);
 return 0; 
} 
