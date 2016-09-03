//Hugarty Pedro
//RA 21450285

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

struct estado{ // estrutura para auxiliar a manipulação dos FILOSOFOS
  int comendo; // Aqui é atribuido um valor que funciona como um contador; Quando chega a 0 o filosofo para de comer
  int pensando; // Parecido com o comendo
  int stado; // igual a 1 Comendo | Igual a 0 pensando
};

struct binario{// Strutura para auxiliar o a manipulação dos garfos
  int estado; // igual a 1 ocupado| Igual a 0 Livre
};

sem_t semaforo;// Criando um semaforo

struct binario garfo[5]; // Criando um vetor binario com 5 espaços, um para cada garfo
struct estado filoEsta[5]; //Criando um vetor estado com 5 espaços, um para cada filosofo


//Essa função e a outra logo após essa é usada dentro do indice de e garfos[]; EX: garfos[garfoE(id)].estado
int garfoE(int id) // Função pega o id do filosofo e retorna o garfo que está a sua esquerda
{
  if(id == 0){ // O garfo 4 sempre vai estar ao lado esquerdo do filosofo 0 - rotação ante horaria
    return 4; // Retorna inteiro 4
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
  if(id == 4){ // O garfo 3 sempre vai estar ao lado esquerdo do filosofo 4 - rotação ante horaria
    return 3;
  }
}
int garfoD(int id) // Função pega o id do filosofo e retorna o garfo que está a sua direita
{
  if(id == 0) //Quer dizer que o garfo a direita do id 0 é o garfo 0
  {
    return 0;
  }
  if(id == 1)//Quer dizer que o garfo a direita do id 1 é o garfo 1
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

void soltaGarfo(int id) // Função que é chamada logo ap os um filosofo terminar de comer
{
  garfo[garfoE(id)].estado = 0;// Libera o garfo da esquerda para uso dos outros filosofos
  garfo[garfoD(id)].estado = 0;// Libera o garfo da direita
  filoEsta[id].pensando = 5; // Diz que pelos proximos 5 turnos o filosofo só vai pensar
}

//Função altera os valores das variaveis fazendo a magia acontecer
void comer(int id)
{
  filoEsta[id].stado = 1; //Essa linha diz que o Filosofo está comendo
  filoEsta[id].comendo = 2; //Aqui é definido quantos turnos ele irá ficar comendo
  garfo[garfoE(id)].estado = 1; // Aqui ele diz que o garfo da esquerda do filosofo está sendo usado
  garfo[garfoD(id)].estado = 1; // Aqui a mesma coisa só que com o garfo da direita

}

//Função que verifica se os garfos estão livre para uso e chama  a função comer
void tentaComer (int id)
{
  if(garfo[garfoE(id)].estado == 0) //Verifica se o garfo da esquerda está livre
  {
    if(garfo[garfoD(id)].estado == 0)//Verifica se o garfo da direita está livre
    {
      comer(id); // Se os dois garfos estiverem livres ele chama função comer
    }
    else// Se não ele volta a pensar até poder comer
    {
      filoEsta[id].pensando ++;
    }
  }
  else// Se não ele volta a pensar até poder comer
  {
    filoEsta[id].pensando ++;
  }
}

//Função recebe um inteiro representando o ID do Filosofo
//Ela verifica o que o filosofo está fazendo e o que ele vai fazer a partir desse momento, pode ser tentar comer, comer, pensar, largar o garfo.
void verifica (int id)
{
  //Esta comendo
  if(filoEsta[id].stado == 1) //Verifica qual o estado que o filosofo se encontra comendo ou pensando
  {
    //Se o valor de comendo for maior ou igual a 1 ele subtrai 1
    if(filoEsta[id].comendo >= 1)// Enquanto não chega a 0 ele não pode parar de comer
    {
      filoEsta[id].comendo --;
    }
    else
    if(filoEsta[id].comendo == 0)// Quando chega a zero ele altera o status do filosofo
    {
      filoEsta[id].stado = 0; // Essa parte diz que o Filosofo voltou a pensar
      soltaGarfo(id); //Chama essa função que  libera os garfos ques estavam sendo usados
    }
  }
  else
  //Esta Pensando
  if(filoEsta[id].stado == 0)//Verifica qual o estado que o filosofo se encontra comendo ou pensando
  {
    // Se o valor de pensando for maior ou igual a 1 ele subtrai 1
    if(filoEsta[id].pensando >= 1)// Enquanto não chegar a zero ele não pode comer
    {
      filoEsta[id].pensando --;
    }
    else
    if(filoEsta[id].pensando == 0) // Se o valor for 0 ele tenta comer
    {
      tentaComer(id); //Chama a função onde ele tenta comer
    }
  }
}

//Este metodo só serve para printar o que está acontecendo a cada ciclo
void mostraTudo (int id)
{
  printf("Filosofo %d ",id );
  if(filoEsta[id].stado == 0){ // Se o estado for 0 ele fala que o filosofo está pensando
    printf("esta pensando\n");
    printf("Garfo direito %d\n", garfo[garfoD(id)].estado);
    printf("Garfo esquerdo %d\n", garfo[garfoE(id)].estado);
  }
  else //Se o estado for 1 ele diz que o filosofo está comendo
  {
    printf("esta comendo\n");
    printf("Garfo direito %d\n", garfo[garfoD(id)].estado);  //Mostra qual valor do garfo direito
    printf("Garfo esquerdo %d\n", garfo[garfoE(id)].estado); //Mostra qual valor do garfo esquerdo
  }
  printf("Status\n");
  printf("Cont. comendo: %d\n",filoEsta[id].comendo); // PRINTA O CONTADOR DE COMENDO
  printf("Cont. pensando: %d\n----------------\n",filoEsta[id].pensando); //PEINTA O CONTADOR DE PENSANDO


}

//função que inicia o ciclo sem fim e chama função  verifica
void *funcao (void * id)
{
  while(1)//CICLO infinito
  {
    // Quando se usa sleep fica mais facil de entender o que está acontecendo
    sleep(1);

    //Essa função ativa o semaforo. Só uma thread pode entrar ai dentro
    sem_wait(&semaforo);

    // Função que chama toda a execução do código
    verifica((int)id); // É preciso fazer um cast para inteiro pq a pthread só recebe tipo void

    // Função que mostra os status das threads
    mostraTudo((int)id); // É preciso fazer um cast para inteiro pq a pthread só recebe tipo void


    //Essa função desativa o semaforo.
    sem_post(&semaforo);
  }
}


//Função principal do programa
//Criar as threads e inicia elas
//Inicia o semaforo
int main ()
{
  int i;

  //Setando os valores das variaveis iniciais.
  for(i = 0; i < 5; i++)
  {
    garfo[i].estado = 0;      // Quando o estado de garfo é 0 ele não está sendo usado

    // O valor que está aqui representa quantos ciclos vai demorar para parar de comer
    filoEsta[i].comendo = 0;

    // O valor que está aqui representa quantos ciclos vai demorar para parar de pensar
    filoEsta[i].pensando = 5;

    //Esse valor quando em 0 significa que o filosofo está pensando e 1 quando comendo
    filoEsta[i].stado = 0;
  }
  sem_init(&semaforo, 0, 1);// INICIANDO O SEMAFORO


  //Criando 5 threads os 5 filosofos
  pthread_t filo4; // O id desse filosofo é o valor 4
  pthread_t filo3; // O id desse filosofo é o valor 3
  pthread_t filo2; // O id desse filosofo é o valor 2
  pthread_t filo1; // O id desse filosofo é o valor 1
  pthread_t filo0; // O id desse filosofo é o valor 0

  //Executando cada thread na função funcao e enviado um paremetro para representar seu ID
  pthread_create(&filo0, NULL, funcao, (void *)(0));
  pthread_create(&filo1, NULL, funcao, (void *)(1));
  pthread_create(&filo2, NULL, funcao, (void *)(2));
  pthread_create(&filo3, NULL, funcao, (void *)(3));
  pthread_create(&filo4, NULL, funcao, (void *)(4));

  //O código provavelmente nunca chegará aqui mas esses metodos destroem threads e semaforos
  pthread_exit(NULL);
  sem_destroy(&semaforo);

  return 0;// acabou? será? 
}
