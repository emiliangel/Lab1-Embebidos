#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX_LINEAR 5
//Def de spi
typedef enum spi {
    SDO = 0xE0,
    SDI,
    SC,   

}SPI;

//Definición de lectura y escritura
typedef enum {
  READ = 0x00, //Gravity_l read
  WRITE = 0x01, //Gravity_h write

}SPI_MODE;

// def de registros acelerómetro

typedef enum {
  DEVICE_DEFINITIONS_R=0XFF,
  GRAVITY_L_R = 0X10,
  INTERRUPT_CONFIGURE_RW = 0X20, 
  GRAVITY_H_R = 0x30,
}ACCEL_REGISTERS;

//Def de item
typedef struct {
  SPI_MODE mode;
  ACCEL_REGISTERS reg;
  void* data;
}SPI_ITEM;

//Def de cola lineal
typedef struct{
    int inicio;
    int final;
    SPI_ITEM vector [MAX_LINEAR];
}Cola_linear;

//Iniciar cola
void new_lq (Cola_linear *cola_linear){
    cola_linear->inicio = -1;
    cola_linear->final = -1;
}
//Esta vacia cola
bool isEmpty_lq(Cola_linear *cola_linear){
    if (cola_linear->final == -1) {
        return true;
    }else{
        return false;
    }
}
//Esta full la cola
bool isFull_lq (Cola_linear *cola_linear){
    if (cola_linear->final == (MAX_LINEAR -1)){
        return true;
    }else {
        return false;
    }
}
//Desplazar elementos en la cola
void move_lq (Cola_linear * cola_linear){
    for (int x=1; x<=cola_linear->final; x++){
        cola_linear->vector [x-1] = cola_linear->vector[x];
    }

}
//Encolar elementos
void enqueue_lq (Cola_linear *cola_linear, SPI_ITEM item) {
    if (!isFull_lq(cola_linear)) {
        if (isEmpty_lq(cola_linear)){
            cola_linear->inicio = 0;
        }
        cola_linear->final++;
        cola_linear->vector[cola_linear->final]= item;
        
    }else{
        printf ("La cola linear esta llena\n");
    }
}
//Obtener elemento en inicio de la cola
SPI_ITEM peek_lq (Cola_linear* cola_linear){
      if (!isEmpty_lq(cola_linear)){
         //si tiene un solo elemento
            return cola_linear->vector[0]; //retorna el item unico que esta en la pos cero
      }else {
        printf("La cola lineal está vacía\n");
        exit (1);
      }
}
//Desencolar elementos 
SPI_ITEM dequeue_lq (Cola_linear* cola_linear) {
    if (!isEmpty_lq(cola_linear)){
        if (cola_linear->final == 0){  //si tiene un solo elemento
            cola_linear->inicio = -1;
            cola_linear->final = -1;
            return cola_linear->vector[0]; //retorna el item unico que esta en la pos cero
        }else{
            SPI_ITEM aux;
            aux = cola_linear->vector[0];
            move_lq(cola_linear); //si tiene más de un elemento para mover la posicion de cada elemento de la cola_linear 
            cola_linear->final--;
            return aux;
        }   
    }else{
        printf ("la cola lineal esta vacia\n");
        exit (0);
    }

    
}

//Crear item

SPI_ITEM make (SPI_MODE mode, ACCEL_REGISTERS reg, void* data) {
  SPI_ITEM newitem;
  switch (mode){  //comprueba el modo si es de lectura o escritura 
    case READ: 
        //Se comprueba que resistro es??
      switch (reg){ 
        case DEVICE_DEFINITIONS_R:
          newitem.mode = mode;
          newitem.reg = reg;
          newitem.data = (void*) NULL;
          break;

        case GRAVITY_L_R:
          newitem.mode = mode;
          newitem.reg = reg;
          newitem.data = (void*) NULL;
          break;

        case INTERRUPT_CONFIGURE_RW:
          newitem.mode = mode;
          newitem.reg = reg;
          newitem.data = (void*) NULL;
          break;

        default:
          break;
      }
     
    case WRITE:
          newitem.mode = mode;
          newitem.reg = reg;
          newitem.data = (void*) data;
          break;

        default:    
          break;
  }

  return newitem;
};


//Manejar elementos en funcion del pin de entrada
void handler_lq (Cola_linear* cola_linear, SPI_ITEM spi_item, SPI spi) {
    //Se comprueba si es input o output
if (spi == SDI){
  enqueue_lq(cola_linear, spi_item);  //Ver
}
if (spi == SDO){
  enqueue_lq(cola_linear, spi_item);
}   
}
