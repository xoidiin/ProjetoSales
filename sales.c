#include <avr/io.h>
#include <util/delay.h>

// Definições dos pinos
#define LCD_RS   13
#define LCD_EN   12
#define LCD_D4   6
#define LCD_D5   5
#define LCD_D6   3
#define LCD_D7   2
#define LED_PIN  7
#define PIR_PIN  4
#define BUZZER_PIN 8

// Protótipos de função
void lcd_command(uint8_t command);
void lcd_write(uint8_t data);
void lcd_init(void);
void lcd_print(const char *str);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_clear(void);

int main(void) {
    // Configuração dos pinos
    DDRD |= (1 << LED_PIN) | (1 << BUZZER_PIN); // LED e Buzzer como saída
    DDRD &= ~(1 << PIR_PIN); // PIR como entrada
    
    // Inicializa o LCD
    lcd_init();
    
    while(1) {
        uint8_t pir_status = PIND & (1 << PIR_PIN);
        
        if (pir_status) {
            lcd_clear();
            PORTD |= (1 << LED_PIN); // Liga LED
            PORTD |= (1 << BUZZER_PIN); // Liga Buzzer
            
            // Simula o tone() - versão simplificada
            for (int i = 0; i < 30; i++) {
                PORTD ^= (1 << BUZZER_PIN);
                _delay_ms(1);
            }
            
            lcd_set_cursor(0, 1);
            lcd_print("ALERTA MOVIMENTO");
            _delay_ms(3000);
            lcd_clear();
        } else {
            lcd_set_cursor(0, 0);
            lcd_print("NADA DETECTADO");
            PORTD &= ~((1 << LED_PIN) | (1 << BUZZER_PIN)); // Desliga LED e Buzzer
        }
        _delay_ms(1000);
    }
    return 0;
}

// Implementações das funções do LCD (simplificadas)
void lcd_command(uint8_t command) {
    // Implementação do envio de comando para o LCD
    // (código específico para controlar o LCD via GPIO)
}

void lcd_write(uint8_t data) {
    // Implementação do envio de dados para o LCD
}

void lcd_init(void) {
    // Inicialização do LCD
    _delay_ms(50);
    // Sequência de inicialização específica para o LCD
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_write(*str++);
    }
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? 0x80 : 0xC0;
    address += col;
    lcd_command(address);
}

void lcd_clear(void) {
    lcd_command(0x01);
    _delay_ms(2);
}