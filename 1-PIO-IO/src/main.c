/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

// Configuracoes do botao
#define BUT_3_PIO			PIOA
#define BUT_3_PIO_ID		ID_PIOA
#define BUT_3_PIO_IDX		19
#define BUT_3_PIO_IDX_MASK (1u << BUT_3_PIO_IDX) 

#define BUT_2_PIO			PIOC
#define BUT_2_PIO_ID		ID_PIOC
#define BUT_2_PIO_IDX		31
#define BUT_2_PIO_IDX_MASK (1u << BUT_2_PIO_IDX)

#define BUT_1_PIO			PIOD
#define BUT_1_PIO_ID		ID_PIOD
#define BUT_1_PIO_IDX		28
#define BUT_1_PIO_IDX_MASK (1u << BUT_1_PIO_IDX)

#define LED_3_PIO		PIOB
#define LED_3_PIO_ID	ID_PIOB
#define LED_3_PIO_IDX     2
#define LED_3_PIO_IDX_MASK  (1 << LED_3_PIO_IDX)

#define LED_2_PIO		PIOC
#define LED_2_PIO_ID	ID_PIOC
#define LED_2_PIO_IDX     30
#define LED_2_PIO_IDX_MASK  (1 << LED_2_PIO_IDX)

#define LED_1_PIO		PIOA
#define LED_1_PIO_ID	ID_PIOA
#define LED_1_PIO_IDX     0
#define LED_1_PIO_IDX_MASK  (1 << LED_1_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_3_PIO_ID);
	pmc_enable_periph_clk(LED_2_PIO_ID);
	pmc_enable_periph_clk(LED_1_PIO_ID);
	
	//Inicializa PC8 como saída
	pio_set_output(LED_3_PIO, LED_3_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED_2_PIO, LED_2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED_1_PIO, LED_1_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_3_PIO_ID);
	pmc_enable_periph_clk(BUT_2_PIO_ID);
	pmc_enable_periph_clk(BUT_1_PIO_ID);
	
	// configura pino ligado ao botão como entrada com um pull-up.
	pio_set_input(BUT_3_PIO, BUT_3_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT_2_PIO, BUT_2_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT_1_PIO, BUT_1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT_3_PIO, BUT_3_PIO_IDX_MASK, 1);
	pio_pull_up(BUT_2_PIO, BUT_2_PIO_IDX_MASK, 1);
	pio_pull_up(BUT_1_PIO, BUT_1_PIO_IDX_MASK, 1);
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	 // Verifica valor do pino que o botão está conectado
	 if(!pio_get(BUT_3_PIO, PIO_INPUT, BUT_3_PIO_IDX_MASK)) {
		 // Pisca LED
		 for (int i=0; i<10; i++) {
			 pio_clear(LED_3_PIO, LED_3_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
			 pio_set(LED_3_PIO, LED_3_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
		 }
		 } else  {
		 // Ativa o pino LED_IDX (par apagar)
		 pio_set(LED_3_PIO, LED_3_PIO_IDX_MASK);
	 }
	 
	 // Verifica valor do pino que o botão está conectado
	 if(!pio_get(BUT_2_PIO, PIO_INPUT, BUT_2_PIO_IDX_MASK)) {
		 // Pisca LED
		 for (int i=0; i<10; i++) {
			 pio_clear(LED_2_PIO, LED_2_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
			 pio_set(LED_2_PIO, LED_2_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
		 }
		 } else  {
		 // Ativa o pino LED_IDX (par apagar)
		 pio_set(LED_2_PIO, LED_2_PIO_IDX_MASK);
	 }
	 
	 if(!pio_get(BUT_1_PIO, PIO_INPUT, BUT_1_PIO_IDX_MASK)) {
		 // Pisca LED
		 for (int i=0; i<10; i++) {
			 pio_clear(LED_1_PIO, LED_1_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
			 pio_set(LED_1_PIO, LED_1_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
			 delay_ms(100);                         // delay
		 }
		 } else  {
		 // Ativa o pino LED_IDX (par apagar)
		 pio_set(LED_1_PIO, LED_1_PIO_IDX_MASK);
	 }
	 
	 
  }
  return 0;
}
