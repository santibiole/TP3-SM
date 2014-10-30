#include <stdint.h>
#include "bsp/bsp.h"
#include <stdio.h>
#include <string.h>

#define BT_ARRIBA 1
#define BT_DERECHA 2
#define BT_ABAJO 3
#define BT_IZQUIERDA 4

/* Variables utilizadas en recepcion de datos a traves de la UART */
#define TAM_RX_BUFFER 1
#define ASCII_A_DECIMAL 48

char rx_buffer[TAM_RX_BUFFER];

static uint8_t rx_dato_disponible = 0;

/**
 * @brief Se encarga de prender un led y apagarlo luego de un tiempo
 *
 * @param led    Numero de led a pulsar
 * @param tiempo Numero de ciclos del delay entre prendido y apagado
 */
void pulsoLed(uint8_t led, uint32_t tiempo);

/**
 * @brief Analiza la trama recibida por la UART
 *
 */
int analizar_dato (int estado_anterior);

/**
 * @brief Aplicacion principal
 */
int main(void) {


	typedef enum {
		mostrar_menu=0,
		procesar_estado=1,
		test_adc=2,
		test_leds=3,
		test_switch=4,
		adc_binario=5,
		adc_voltios=6,
		ledn_on=7,
		push_switch=8
	} estados_e;
	estados_e estado = mostrar_menu;

	int estado_anterior;
	int pote;
	char buffer[50];
	// Inicializo hardware
	bsp_init();

	while (1) {
		switch (estado) {
		case mostrar_menu:
			// Se muestra el menú
			uart_tx("\nMenú:\n1) Test ADC\n2) Test LEDS\n3) Test SWITCHES\n");
			estado_anterior = estado;
			estado = procesar_estado;
			break;
		case procesar_estado:
			// Se procesa el estado
			if(rx_dato_disponible==1){
					estado = analizar_dato(estado_anterior);
			}
			break;
		case test_adc:
			// Se muestra el menú Test ADC
			uart_tx("\nTest ADC:\n1) BINARIO\n2) VOLTIOS\n3) VOLVER");
			estado_anterior = estado;
			estado = procesar_estado;
			break;
		case test_leds:
			// Se muestra el menú Test LEDS
			uart_tx("\nTest LEDS:\n1) LED 1\n2) LED 2\n3) LED 3\n4) LED 4\n5) LED 5\n6) LED 6\n7) LED 7\n8) LED 8\n9) VOLVER");
			estado_anterior = estado;
			estado = procesar_estado;
			break;
		case test_switch:
			// Se muestra el menú Test SWITCHES
			uart_tx("\nTest SWITCHES: Presione el switch que desea testear\n1) VOLVER");
			estado_anterior = estado;
			estado = push_switch;
			break;
		case adc_binario:
			// Se muestra el menú Test SWITCHES
			pote=read_adc();
			sprintf(buffer,"\nTest ADC BINARIO: %d\n1) VOLVER", (int)pote);
			uart_tx(buffer);
			estado_anterior = estado;
			estado = procesar_estado;
			break;
		case adc_voltios:
			break;
		case ledn_on:
			// Se muestra el menú Test SWITCHES
			if(rx_buffer[0]=='1')
				pulsoLed(0,100);
			if(rx_buffer[0]=='2')
				pulsoLed(1,100);
			if(rx_buffer[0]=='3')
				pulsoLed(2,100);
			if(rx_buffer[0]=='4')
				pulsoLed(3,100);
			if(rx_buffer[0]=='5')
				pulsoLed(4,100);
			if(rx_buffer[0]=='6')
				pulsoLed(5,100);
			if(rx_buffer[0]=='7')
				pulsoLed(6,100);
			if(rx_buffer[0]=='8')
				pulsoLed(7,100);
			estado_anterior = test_leds;
			estado = procesar_estado;
			break;
		case push_switch:
			if(sw_getState(GPIO_Pin_4))
				led_toggle(0);
			if(sw_getState(GPIO_Pin_5))
				led_toggle(1);
			if(sw_getState(GPIO_Pin_6))
				led_toggle(2);
			if(sw_getState(GPIO_Pin_2))
				led_toggle(3);
			estado_anterior = estado;
			estado = procesar_estado;
			break;
		}
	}
}

void pulsoLed(uint8_t led, uint32_t tiempo){
	led_on(led);
	bsp_delay_ms(tiempo);
	led_off(led);
}

void APP_ISR_uartrx (void){
	/*Levanto bandera de dato disponible en UART RX*/
	rx_dato_disponible = 1;
	/*Cargo dato disponible en "data"*/
	rx_buffer[0] = uart_rx();
}

int analizar_dato (int estado_anterior) {
	int estado;
	rx_dato_disponible=0;
	if(estado_anterior==0){
		if (rx_buffer[0] == '1')
			estado=2;
		if (rx_buffer[0] == '2')
			estado=3;
		if (rx_buffer[0] == '3')
			estado=4;
	}
	if(estado_anterior==2){
		if (rx_buffer[0] == '1')
			estado=5;
		if (rx_buffer[0] == '2')
			estado=3;
		if (rx_buffer[0] == '3')
			estado=0;
	}
	if(estado_anterior==3){
		if (rx_buffer[0] == '9')
			estado=0;
		else
			estado=7;
	}
	if(estado_anterior==4){
		if (rx_buffer[0] == '1')
			estado=2;
		if (rx_buffer[0] == '2')
			estado=3;
		if (rx_buffer[0] == '3')
			estado=4;
	}
	if(estado_anterior==5){
		if (rx_buffer[0] == '1')
			estado=2;
	}
	if(estado_anterior==8){
		if (rx_buffer[0] == '1')
			estado=0;
		else
			estado=8;
	}
	return estado;
}

void APP_ISR_sw(void) {
}

void APP_ISR_1ms(void) {
}
