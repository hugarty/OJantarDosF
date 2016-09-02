#include <stdio.h>
int var = 0; // Criando a variavel global

void imprime (int id)
{
  int i;
  for(i = 0; i < 1000; i++)
  {
    var = var + 1; //Incrementando a variavel GLOBAL
  }
    //Mostra o valor da variavel global depois dos incrementos
    //Tambem mostra o id do Processo
    printf("id: %d - Valor: %d\n", id,var);
}
int main ()
{
  fork(); //Criando o processo filho
  imprime (getpid()); //Chamando a função imprime e dando o ID do Pai e do Filho
}
