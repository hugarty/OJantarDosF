#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

/*
Cada filosofo possui um prato cheio de macarrão. Além
disso um garfo é posicionado entre cada par adjacente
de filosofos( portanto, cada filosofo tem exatamente
um garfo à sua direita e esquerda)
Cada filosofo pode estar ou pesando ou comendo. Para
comer são necessarios dois garfos, Se ele pegar um
dos garfos e o outro não está disponivel, devolve-o à
mesa e continua pensando até que consiga pegar os dois
garfos de uma vez só, Quando conseguir pegar os dois
garfos o filósofo come e logo depois devolve ambos
garfos à mesa.
*/

//comendo
//pensando até ter os 2 garfos
// verificar se tem garfo
//// Comer
// -lpthread -lrt
/*verificaFome (int numero)
{
  if()
  {
    podeComer();
  }
  else
  {
    fome--;
  }
}

*/
struct binario{
  int estado;
};
struct binario garfo[5];

sem_t semaforo;

void *funcao (void * filo)
{
  int *num = (int *)filo; // NUMERO DO FILOSOFO
  while(1)//CICLO infinito
  {
    sleep(1);
    if()
    {

    }
    sem_wait(&semaforo);
    printf("Teste %d\n", num);

    sem_post(&semaforo);
  }
}

int main ()
{
  int i;
  for(i = 0; i < 5; i++) //Setando valor 1 nos garfos
  { // Quando garfo está com valor 0 ele não esta
    //  sendo utilizado
    garfo[i].estado = 0;
  }

  sem_init(&semaforo, 0, 1);

  pthread_t filo5;
  pthread_t filo4;
  pthread_t filo3;
  pthread_t filo2;
  pthread_t filo1;

  pthread_create(&filo1, NULL, funcao, (void*)1);
  pthread_create(&filo2, NULL, funcao, (void*)2);
  pthread_create(&filo3, NULL, funcao, (void*)3);
  pthread_create(&filo4, NULL, funcao, (void*)4);
  pthread_create(&filo5, NULL, funcao, (void*)5);

  pthread_exit(NULL);
  sem_destroy(&semaforo);

  return 0;
}
