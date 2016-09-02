#include <stdio.h>
#include <pthread.h>



void *imprime2 (void *carac)
{
  char c = (char)carac;
  int i;
  for(i = 0; i < 1000; i++)
  {
    printf("%c\n", c);
  }
}


int main()
{
  pthread_t thread1;
  pthread_t thread2;
  pthread_create(&thread1, NULL, imprime, (void*)'c');
  pthread_create(&thread2, NULL, imprime, (void*)'.');


  pthread_exit(NULL);

  printf("\n");
  return 0;
}
