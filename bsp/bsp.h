#ifndef _BSP_H
#define _BSP_H

/**
 * @brief Prende un led
 *
 * @param led Led a prender
 */
void led_on(uint8_t led);

/**
 * @brief Apaga un led
 *
 * @param led Led a apagar
 */
void led_off(uint8_t led);

/**
 * @brief Conmuta un led
 *
 * @param led Led a apagar
 */
void led_toggle(uint8_t led);

/**
 * @brief PWM
 *
 * @param led
 * @param value Ciclo de trabajo
 */
void led_set_bright (uint8_t led, uint8_t value);

/**
 * @brief Delay de x ms
 *
 * @param x cantidad de ms
 */
void bsp_delay_ms(uint16_t x);

/**
 * @brief Enviar por uart
 *
 * @param Dato
 *
 * @retval Si fue enviado o recibido
 */
void uart_tx (char* data);

/**
 * @brief Recibir por uart
 *
 * @retval Dato recibido
 */
char uart_rx (void);

/**
 * @brief Lectura del switch
 *
 * @retval Estado del switch
 */
uint8_t sw_getState(uint16_t sw);

/**
 * @brief Lectura ADC
 */
uint16_t read_adc();

/**
 * @brief Valor potenciometro a leds
 *
 * @retval Cantidad de leds a prender
 */
uint16_t vumetro();

/**
 * @brief Nivel potenciometro a porcentaje
 *
 * @retval Porcentaje
 */
uint16_t nivel_pote (void);

/**
 * @brief Inicializacion de los servicios de BSP
 */
void bsp_init();

#endif
