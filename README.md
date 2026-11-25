# Vetores 3D em C com Plotagem no Gnuplot

Aplicação desenvolvida em linguagem **C** que realiza operações vetoriais básicas (soma e subtração) entre dois pontos no espaço tridimensional $(x, y, z)$ e gera automaticamente uma visualização gráfica interativa em 3D utilizando o **Gnuplot** via pipe (`popen`).

## Funcionalidades

- **Entrada de coordenadas 3D:** Leitura dos pontos $P_1(x, y, z)$ e $P_2(x, y, z)$ via terminal.
- **Operações vetoriais:** Cálculo da soma ($P_1 + P_2$) e da subtração ($P_1 - P_2$) utilizando estruturas (`struct`).
- **Visualização gráfica 3D:**
  - Desenho dos vetores saindo da origem $(0, 0, 0)$ até cada ponto.
  - Linhas tracejadas ilustrando a regra do paralelogramo para a soma vetorial.
  - Rótulos identificando $P_1$, $P_2$, `Soma` e `Sub`.
  - Janela interativa que permite rotacionar e aplicar zoom nos eixos.

## Pré-requisitos

Para compilar e executar o projeto, você precisa ter instalado em seu sistema:

- **Compilador C** (ex: `gcc`)
- **Gnuplot** (com suporte a interface gráfica, como `gnuplot-x11` ou `gnuplot-qt` no Linux)

### Instalação no Linux (Ubuntu / Debian / Linux Mint)

```bash
sudo apt update
sudo apt install gcc gnuplot
