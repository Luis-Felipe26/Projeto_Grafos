#!/bin/bash

# Caminho para o executável
bellmanford=./bellmanford.bin

# Diretório com os testes
test_dir="./Testes"

# Cria diretório para as saídas se não existir
mkdir -p saidas

# Loop sobre os arquivos de entrada da pasta Testes
for test_input in "$test_dir"/*.mtx; do
    if [ -f "$test_input" ]; then
        test_name=$(basename "$test_input" .mtx)
        output_file="saidas/${test_name}_saida.txt"

        echo "Executando teste $test_name..."
        "$bellmanford" -f "$test_input" -o "$output_file" -i 1
    fi
done

echo "Todos os testes foram executados."