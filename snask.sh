#!/bin/bash

# Executa o script main.py, passando todos os argumentos para o Python
python3 "$(dirname "$0")/main.py" "$@"

# Espera uma tecla ser pressionada antes de fechar o terminal (similar ao 'pause' no Windows)
read -p "Pressione qualquer tecla para continuar..." -n1 -s
echo
