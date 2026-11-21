# Sistema de Controle de Estacionamento (em C)

Projeto prático desenvolvido para a disciplina de **Programação Procedimental** (FACOM / UFU), simulando o controle de vagas, cobrança por tempo de permanência e emissão de relatório diário de um estacionamento com capacidade para 10 veículos.

## Funcionalidades

- **Cadastro inicial de tarifas:** definição do valor por hora para Moto, Carro e Caminhonete.
- **Registro de entrada:** verificação de vaga livre, validação de placa (até 8 caracteres sem espaços), tipo de veículo e horário inteiro (`0` a `23`).
- **Registro de saída e cobrança:** busca pela placa, cálculo do tempo de permanência (com suporte à virada de meia-noite e cobrança de hora cheia para frações) e atualização do caixa.
- **Listagem de veículos:** exibe os veículos atualmente estacionados e suas respectivas vagas.
- **Relatório do dia:** apresenta o total arrecadado, o número de veículos atendidos e o tipo de veículo mais frequente.

## Como compilar e executar

No terminal (Linux/Windows com `gcc`):

```bash
gcc estacionamento.c -o estacionamento
./estacionamento
