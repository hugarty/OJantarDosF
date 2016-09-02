#include <stdio.h>
#include <pthread.h>

int var = 0; // Criando a variavel global

void *imprime (void *id)
{
  int i;
  for(i = 0; i < 1000; i++)
  {
    var = var + 1;
  }
    printf("id: %d - Valor: %d\n", id,var);
}

int main()
{
  pthread_t thread1; // Criando primeira thread
  pthread_t thread2; // Criando segunda thread
  pthread_create(&thread1, NULL, imprime,(void*)1); // Executando primeira thread na função imprime()
  pthread_create(&thread2, NULL, imprime,(void*)2);// Executando segunda thread na função imprime()
  pthread_exit(NULL);//Deleta as threads
  return 0;
}
