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

filoEsta[id].
*/



struct estado{
  int comendo;
  int pensando;
  int stado; // igual a 1 Comendo | Igual a 0 pensando
};

struct binario{
  int estado; // igual a 1 ocupado| Igual a 0 Livre
};

sem_t semaforo;
int cont =0;
struct binario garfo[5];
struct estado filoEsta[5];

int garfoE(int id)
{
  if(id == 0){
    return 4;
  }
  if(id == 1){
    return 0;
  }
  if(id == 2){
    return 1;
  }
  if(id == 3){
    return 2;
  }
  if(id == 4){
    return 3;
  }
}
int garfoD(int id)
{
  if(id == 0)
  {
    return 0;
  }
  if(id == 1)
  {
    return 1;
  }
  if(id == 2)
  {
    return 2;
  }
  if(id == 3)
  {
    return 3;
  }
  if(id == 4)
  {
    return 4;
  }
}

void soltaGarfo(int id)
{
  garfo[garfoE(id)].estado = 0;
  garfo[garfoD(id)].estado = 0;
  filoEsta[id].pensando = 5;
}

void comer(int id)
{

  filoEsta[id].stado = 1;
  filoEsta[id].comendo = 2;
  garfo[garfoE(id)].estado = 1;
  garfo[garfoD(id)].estado = 1;

}

void tentaComer (int id)
{
  if(garfo[garfoE(id)].estado == 0)
  {
    if(garfo[garfoD(id)].estado == 0)
    {
      comer(id);
    }
    else
    {
      filoEsta[id].pensando ++;
    }
  }
  else
  {
    filoEsta[id].pensando ++;
  }
}

void verifica (int id)
{
  //Esta comendo
  if(filoEsta[id].stado == 1)
  {
    if(filoEsta[id].comendo >= 1)
    {
      filoEsta[id].comendo --;
    }
    else
    if(filoEsta[id].comendo == 0)
    {
      filoEsta[id].stado = 0;
      soltaGarfo(id);
    }
  }

  //Esta Pensando
  if(filoEsta[id].stado == 0)
  {
    if(filoEsta[id].pensando >= 1)
    {
      filoEsta[id].pensando --;
    }
    else
    if(filoEsta[id].pensando == 0)
    {
      tentaComer(id);
    }
  }
}
void mostraTudo (int id)
{
  printf("Filosofo %d ",id );
  if(filoEsta[id].stado == 0){
    printf("esta pensando\n");
    printf("Garfo direito %d\n", garfo[garfoD(id)].estado);
    printf("Garfo esquerdo %d\n", garfo[garfoE(id)].estado);
  }
  else
  {
    printf("esta comendo\n");
    printf("Garfo direito %d\n", garfo[garfoD(id)].estado);
    printf("Garfo esquerdo %d\n", garfo[garfoE(id)].estado);
  }
  printf("Status\n");
  printf("Cont. comendo: %d\n",filoEsta[id].comendo);
  printf("Cont. pensando: %d\n----------------\n",filoEsta[id].pensando);


}
void *funcao (void * id)
{
  while(1)//CICLO infinito
  {
    sleep(1);
    sem_wait(&semaforo);
    verifica((int)id);
    mostraTudo((int)id);
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
    filoEsta[i].comendo = 0;
    filoEsta[i].pensando = 5;
    filoEsta[i].stado = 0;
  }
  sem_init(&semaforo, 0, 1);

  pthread_t filo4;
  pthread_t filo3;
  pthread_t filo2;
  pthread_t filo1;
  pthread_t filo0;

  pthread_create(&filo0, NULL, funcao, (void *)(0));
  pthread_create(&filo1, NULL, funcao, (void *)(1));
  pthread_create(&filo2, NULL, funcao, (void *)(2));
  pthread_create(&filo3, NULL, funcao, (void *)(3));

  pthread_create(&filo4, NULL, funcao, (void *)(4));

  pthread_exit(NULL);
  sem_destroy(&semaforo);

  return 0;
}


/*
for(i = 0; i < 5; i++) {
  printf("\n----------\ngarfo:%d \nEstadoComendo: %d \nEstadoPensando: %d \nstd: %d "
  ,garfo[i].estado, filoEsta[i].comendo,
  filoEsta[i].pensando,filoEsta[i].stado);
}
printf("\n");
*/
