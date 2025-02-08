# Projeto Embarcatech - Unidade 4 Capítulo 6: Interfaces de Comunicação Serial

Este repositório contém o código-fonte e a documentação para o projeto do Capítulo 6 do curso Embarcatech, focado em interfaces de comunicação serial utilizando o Raspberry Pi Pico. O projeto demonstra a utilização de interfaces I2C, UART, e controle de LEDs RGB endereçáveis, além de interação com botões e um display OLED.

## Descrição do Projeto

O projeto tem como objetivo principal a implementação de um sistema de monitoramento e controle de LEDs utilizando diferentes interfaces de comunicação serial. O sistema inclui:

- **Display OLED**: Utilizado para exibir informações sobre o estado dos LEDs e interações do usuário.
- **LEDs RGB Endereçáveis**: Controlados via matriz de LEDs, permitindo a exibição de diferentes padrões e sprites.
- **Botões**: Utilizados para alternar o estado dos LEDs verde e azul.
- **UART**: Utilizada para comunicação serial com um terminal, permitindo a interação do usuário via teclado.

## Configuração do Hardware

### Pinagem

- **I2C**:
  - SDA: GPIO 14
  - SCL: GPIO 15
- **UART**:
  - TX: GPIO 0
  - RX: GPIO 1
- **LEDs**:
  - Verde: GPIO 11
  - Azul: GPIO 12
- **Botões**:
  - BTN_A: GPIO 5
  - BTN_B: GPIO 6
- **Matriz de LEDs**:
  - Pino de comunicação: GPIO 7

## Funcionalidades

### Inicialização

O código inicializa todas as interfaces de comunicação e periféricos necessários, incluindo:

- **I2C**: Para comunicação com o display OLED.
- **UART**: Para comunicação serial com o terminal.
- **LEDs**: Configuração dos LEDs verde e azul.
- **Botões**: Configuração dos botões A e B com tratamento de debounce.
- **Matriz de LEDs**: Inicialização da matriz de LEDs RGB endereçáveis.

### Interação com o Usuário

- **Botões**: Os botões A e B alternam o estado dos LEDs verde e azul, respectivamente. O estado dos LEDs é exibido no display OLED.
- **UART**: O usuário pode enviar comandos via terminal para exibir sprites na matriz de LEDs. Comandos numéricos de 0 a 9 exibem sprites correspondentes, enquanto outros caracteres limpam a matriz.

### Display OLED

O display OLED exibe informações sobre o estado dos LEDs e a última tecla pressionada pelo usuário. O conteúdo é atualizado continuamente com base nas interações do usuário.

## Estrutura do Código

O código está organizado em várias funções principais:

- **i2c_setup()**: Configura a interface I2C.
- **uart_setup()**: Configura a interface UART.
- **oled_setup()**: Inicializa e configura o display OLED.
- **leds_setup()**: Configura os LEDs verde e azul.
- **btns_setup()**: Configura os botões A e B.
- **insert_sprite()**: Exibe um sprite na matriz de LEDs com base no índice fornecido.
- **gpio_irq_handler()**: Manipula as interrupções geradas pelos botões.
- **main()**: Função principal que inicializa o sistema e entra em um loop infinito para monitorar e atualizar o estado do sistema.

## Compilação e Upload
1. Clone o repositório utilizando o comando abaixo.
```
git clone https://github.com/GabrielShiva/serial_communication_embarcatech.git
```
2. No VsCode, clique na extensão `Raspberry Pi Pico W`, depois em *Importar Projeto*, selecione a pasta do projeto, escolha a versão do SDK (2.1.0) e, por fim, em *Importar*.

## Vídeo de Apresentação

Assita ao vídeo com a apresentação do projeto (clicando aqui)[https://youtu.be/0n7IPdrnEfA].