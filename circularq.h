#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CIRCULAR 10

// enum para GPIO
typedef enum gpio{
    CS = 0xA0,
    INT1,
    INT2,
    INT3,
    INT4,

}GPIO;
//Def de item
typedef struct {
    GPIO gpio;
}GPIO_ITEM;

//Def de cola circular
typedef struct{
    int inicio;
    int final;
    GPIO_ITEM vector [MAX_CIRCULAR];
}Cola_cirq;
//Iniciar cola
void new_cq (Cola_cirq *cola) {
    cola->inicio = -1;
    cola->final = -1;
}
//Esta vacia?

bool isEmpty_cq (Cola_cirq *Cola) {
    if (Cola->final == -1){
        return true;
    }else {
        return false;
    }
}
//Esta full la cola
bool isFull_cq (Cola_cirq *cola){
    if((cola->inicio == ((cola->final +1) % MAX_CIRCULAR))){ 
         return true;
    }else{
      
        return false; 
    }

}
//Encolar elementos
void enqueue_cq (Cola_cirq *cola, GPIO_ITEM a){
    if (isFull_cq (cola)){
        printf ("la cola esta full\n");
       
    }else{
        if ((cola->inicio) == -1){ //se comprueba si la cola estaba vacía
            cola->inicio = 0; 
        }
        cola->final = (cola->final +1) % MAX_CIRCULAR;
        cola->vector[cola->final] = a;
    }
}
//Desencolar elementos
GPIO_ITEM dequeue_cq (Cola_cirq*cola) {
    if (!isEmpty_cq(cola)){
        GPIO_ITEM aux = cola->vector [cola->inicio]; //se salva item en posicion de inicio
        if (cola->inicio == cola->final){  //si la cola tiene un solo elemento, se resetea a valores iniciales
            cola->inicio = -1;
            cola->final = -1;
        }else{
            cola->inicio = (cola->inicio +1) % MAX_CIRCULAR;  //se mueve inicio a la siguiente posición circular 
        }
        return aux;
    }else {
        printf ("La cola circular esta vacia\n"); 
        exit (0);///ver
    }
}
//Ver elemento en inicio de la cola
GPIO_ITEM peek_cq (Cola_cirq*cola) {
    if (!isEmpty_cq(cola)){
        GPIO_ITEM aux = cola->vector [cola->inicio]; //se salva item en posicion de inicio
        return aux;
    }else {
        printf ("La cola esta vacia\n"); ///ver
    }
}
//Recorrer cola
void run_cq (Cola_cirq *cola) {
    if (!isEmpty_cq){
        if (cola->inicio == cola->final){ //en caso q tenga un solo elemento
            printf ("Valor del item: %d\n", cola->vector[cola->inicio]);
        }else{
            for (int i = cola->inicio; i != cola->final; (i +1) % MAX_CIRCULAR){
                printf ("Valor del item: %d\n", cola->vector[cola->inicio]);
            }
        }       
    }else{
        printf("la cola esta vacia");
    }
}
//Manejar vector de interrupciones en la cola
void handler_cq (Cola_cirq* cola_cirq) {
GPIO inst;
GPIO_ITEM aux;
for (int j=0; j<MAX_CIRCULAR; j++){ 
    if (isEmpty_cq(cola_cirq)){
      printf ("La cola está vacía\n"); 
      exit (1);
    }else {
      aux = dequeue_cq (cola_cirq);
      inst = aux.gpio;
      switch (inst){
        case INT1:
          printf("Interrupcion por toque\n");
        break;

        case INT2:
          printf("Interrupcion de cambio de centro de gravedad\n");
        break;

        case INT3:
            printf("Interrupcion por inactividad\n");

        break;

        case INT4:
            printf("Interrupcion por doble toque\n");
        break;
        default:
            printf("Ninguna interrupcion fue ejecutada\n");
        break;
      }
    }
  }
};