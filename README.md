# Projeto de Depuração – Raspberry Pi Pico

## Objetivo

Este repositório é dedicado à depuração de um exemplo simples em C rodando no Raspberry Pi Pico (RP2040), focado em validar PWM para controle de um servo no `GPIO 28` e a saída de logs pela UART de debug (`uart0` nos GPIOs 16 e 17).

O programa alterna o pulso do servo entre ~500 µs (aprox. 0°) e ~2400 µs (aprox. 180°) a cada segundo, imprimindo mensagens via UART para acompanhar o estado.

## Stack e Ferramentas

- C (Pico SDK)
- CMake
- VS Code + extensão Raspberry Pi Pico
- Windows 11

## Arquivos Importantes

- `Depuracao.c`: Código principal com inicialização da UART, configuração de PWM e pulsos para servo no `GPIO 28`.
- `CMakeLists.txt`: Configuração do build via Pico SDK.
- `build/Depuracao.uf2`: Artefato gerado após compilação para gravação via BOOTSEL.

## Como Compilar

Há uma task configurada chamada "Compile Project" que usa `ninja` no diretório `build`.

### Pelo VS Code
- Pressione `Ctrl+Shift+P` e execute: `Raspberry Pi Pico: Compile Project`.
   - Alternativamente, use a task "Compile Project".

### Pelo terminal (PowerShell)
Se já houver o diretório `build` configurado:

```powershell
"$env:USERPROFILE/.pico-sdk/ninja/v1.12.1/ninja.exe" -C "${PWD}/build"
```

## Como Gravar no Pico

Você pode utilizar uma das tasks já configuradas:

- "Run Project" (via `picotool`): carrega o binário no dispositivo.
- "Flash" (via `openocd`): programa, verifica e reseta via CMSIS-DAP.

Alternativamente, use o modo BOOTSEL:

1. Conecte o Pico com o botão BOOTSEL pressionado.
2. Arraste e solte o arquivo `build/Depuracao.uf2` na unidade montada do Pico.

## Observação sobre UART

- UART de debug configurada: `uart0`, `BAUD_RATE = 115200`, `TX = GPIO 16`, `RX = GPIO 17`.
- Abra um terminal serial a 115200 baud para ver mensagens como:
   - "Garra fechando (0 graus)..."
   - "Garra abrindo (180 graus)..."

## Estrutura do Projeto

```
├── Depuracao.c
├── CMakeLists.txt
├── pico_sdk_import.cmake
├── README.md
└── build/
      └── Depuracao.uf2
```

## Escopo da Depuração

- Validação de PWM a 50 Hz com `wrap = 20000` e `clkdiv = 125`.
- Verificação de níveis de pulso do servo entre 500 µs e 2400 µs.
- Confirmação de logs pela UART no baud rate configurado.

