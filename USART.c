
#include "Req.h"

void usart2_send_char(char c){
	//check status of TX is ready (TDR is empty?)
	while(!(USART2->SR & USART_SR_TXE)); //(0x1 << 7)
	USART2->DR = c;
}

char usart2_read_char(void){
	//check status of RX is ready ()
	while(!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}

void usart2_read_string(char *buffer, uint16_t max_len){
	uint16_t i =0;
	char c;
	
	while(i < (max_len - 1)){ //Except null
		c = usart2_read_char();
		
		if(c == '\n' || c == '\r'){
				break;
		}
		
		buffer[i++] = c;
	
	}
	
	buffer[i] = '\0'; //End of the string

}


void usart2_send_string(const char *str){
	while(*str){
		usart2_send_char(*str++);
	}
}