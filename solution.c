#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <stdbool.h>
#include<string.h>
long sum=0,count=0;
pthread_mutex_t lock;
int numOfRandomNumbers;
long c=0;
int * arr ;
int isPrime(int num){
int i;


if(num==2) return 1;


   
 if(num%2==0)
return 0;




   

      for (i = 0;i<c;i++){
		if (num%arr[i] == 0&&num!=arr[i])return 0;
            
	}
	return 1;
}

void* fuck(void * arg)
{  int size=*(int*) arg;
   int random;
   for(int i=0;i<size;i++)
    {    random=rand();
          if(isPrime(random))
           { pthread_mutex_lock(&lock);
             sum+=random;
           count+=1;
             pthread_mutex_unlock(&lock);
                   }
    }
}


void SieveOfEratosthenes(int n)
{  int s=0;
    // Create a boolean array
    // "prime[0..n]" and initialize
    // all entries it as true.
    // A value in prime[i] will
    // finally be false if i is
    // Not a prime, else true.
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
 
  if(n>=2)
   arr[s++]=2;



    for (int p = 2; p*p <= n; p++)
    {  
        // If prime[p] is not changed,
        // then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple
            // of p and are less than p^2
            // are already been marked.

            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }


    for(long p = 3; p <=n; p+=2)
{
        if (prime[p]){arr[s++]=p;
           c++;
          }

    }
}
int main(int argc, char *argv[])
{

if(pthread_mutex_init(&lock,NULL)!=0){
           printf("mutix init failed\n"); return 0;}
	if(argc != 3) {
	    printf("Too few arguments ");
	    printf("USAGE: ./primeCalc <prime pivot> <num of random numbers>");
            exit(0);
    	}
	pthread_t tids[4];
int i;
	int randomPivot = atoi(argv[1]);
 numOfRandomNumbers = atoi(argv[2]);
int random = rand();
srand(randomPivot);
arr=(int*) malloc (46340*sizeof(int));


long size1 =numOfRandomNumbers/4;
long size2=(2*numOfRandomNumbers/4)-numOfRandomNumbers/4;
long size3=(3*numOfRandomNumbers/4)-(2*numOfRandomNumbers/4);
long size4=numOfRandomNumbers-(3*numOfRandomNumbers/4);
SieveOfEratosthenes(46340);

pthread_create(&tids[0], NULL, fuck, &size1);
pthread_create(&tids[1], NULL, fuck, &size2);
pthread_create(&tids[2], NULL, fuck, &size3);
pthread_create(&tids[3], NULL, fuck, &size4);

pthread_join(tids[0], NULL);
pthread_join(tids[1], NULL);
pthread_join(tids[2], NULL);
pthread_join(tids[3], NULL);

       
         pthread_mutex_destroy(&lock);
	//keep the out format as this!!
	printf("%ld,%ld\n",sum,count);

    	exit(0);
}
