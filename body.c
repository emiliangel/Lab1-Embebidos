#include <stdio.h>
#include <stdint.h>
#include "circularq.h"
#include "linearq.h"

//Bitfields

//Device
typedef union dev {
  uint8_t byte;
  struct  {
   // Grav bit0;
    uint8_t bit_0_1 : 2;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4;  
    };

}Dev;

//Grav_l
typedef struct grav_l{
    uint8_t byte;
    struct  {
      uint8_t : 2;
      uint8_t bit_2_7 : 6;
    };
   
}Grav_l;

//gravity h
typedef struct grav_h{
    uint8_t byte;
      struct  {
        uint8_t bit_0 : 1;
        uint8_t bit_1 : 1;
        uint8_t bit_2 : 1;
        uint8_t bit_3 : 1;
        uint8_t : 4;
      };
      
}Grav_h;

//pin de interrupcion

typedef union interrupt{
  uint8_t byte;
  struct {
    uint8_t bit_0 : 1;
    uint8_t bit_1 : 1;
    uint8_t bit_2 : 1;
    uint8_t bit_3 : 1;
    uint8_t : 4; 
  };
}Interrupt;


int main() {
// Elementos para prueba de cola lineal
SPI spi;
int a =10, b=11, c=12, d=13, e=14;
Cola_linear cola_linear;
SPI_ITEM spi_item1 = make(READ, GRAVITY_H_R,&a);
SPI_ITEM spi_item2 = make(READ, GRAVITY_H_R,&b);
SPI_ITEM spi_item3 = make(READ, GRAVITY_H_R,&c);
SPI_ITEM spi_item4 = make(READ, GRAVITY_H_R,&d);
SPI_ITEM spi_item5 = make(READ, GRAVITY_H_R,&e), spi_item6;

//Procesos en cola lineal
new_lq (&cola_linear); //Se inicia cola lineal
//Se agregan items con handler
handler_lq (&cola_linear, spi_item1, SDI);
handler_lq (&cola_linear, spi_item2, SDO);
handler_lq (&cola_linear, spi_item3, SDI);
handler_lq (&cola_linear, spi_item4, SDI);
handler_lq (&cola_linear, spi_item5, SDO);

/*------------------------------------------------------*/

/*------------------------------------------------------*/

//Elementos para prueba de cola circular

GPIO_ITEM get_cq, gpio_item[MAX_CIRCULAR]={INT1, INT2,INT3,INT4,INT1, INT2,INT3,INT4,INT1, INT2};
Cola_cirq cola_cirq;

//Procesos en cola circular
new_cq (&cola_cirq); //Se inicia cola circular

for (int i=0; i<MAX_CIRCULAR; i++) {
  enqueue_cq (&cola_cirq, gpio_item[i]); //Se encola vector
}
handler_cq(&cola_cirq);

}



