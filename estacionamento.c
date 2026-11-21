#include <stdio.h>
#include <string.h>

#define VAGAS 10

// Variaveis globais para controle das vagas, dados dos veiculos e estatisticas do dia
char placas[VAGAS][9];
int tipos[VAGAS];
int horasEntrada[VAGAS];
int ocupadas[VAGAS];
float totalArrecadado = 0.0;
int totalVeiculos = 0, contMoto = 0, contCarro = 0, contCaminhonete = 0;
float tarifamoto, tarifacarro, tarifacaminhonete;

// Exibe o relatorio consolidado do dia: faturamento, total de atendimentos e tipo mais frequente
void exibirRelatorio() {
    printf("\n--- RELATORIO DO DIA ---\n");
    printf("Total arrecadado: %.2f reais\n", totalArrecadado);
    printf("Numero de veiculos atendidos: %d\n", totalVeiculos);

    if (contMoto >= contCarro && contMoto >= contCaminhonete)
        printf("Veiculo mais frequente: moto\n\n");
    else if (contCarro >= contMoto && contCarro >= contCaminhonete)
        printf("Veiculo mais frequente: carro\n\n");
    else if (contCaminhonete >= contCarro && contCaminhonete >= contMoto)
        printf("Veiculo mais frequente: caminhonete\n\n");
}

// Apresenta as opcoes do menu interativo no terminal
void exibirMenu() {
    printf("\n===== ESTACIONAMENTO =====\n");
    printf("1 - Registrar entrada\n");
    printf("2 - Registrar saida\n");
    printf("3 - Listar veiculos\n");
    printf("4 - Relatorio do dia\n");
    printf("5 - Sair\n\n");
    printf("Opcao: ");
}

// Percorre o vetor de vagas e retorna o indice da primeira vaga livre (ou -1 se estiver lotado)
int buscarVagaLivre() {
    for (int i = 0; i < VAGAS; i++) {
        if (ocupadas[i] == 0)
            return i;
    }
    return -1;
}

// Procura uma placa ativa nas vagas ocupadas e retorna seu indice (ou -1 caso nao encontre)
int buscarPlaca(char placa[9]) {
    for (int i = 0; i < VAGAS; i++) {
        if (strcmp(placa, placas[i]) == 0 && ocupadas[i] == 1) {
            return i;
        }
    }
    return -1;
}

// Verifica disponibilidade de vaga, le e valida placa, tipo e hora de entrada, e registra o veiculo
void registrarEntrada() {
    int vaga = buscarVagaLivre();
    if (vaga == -1) {
        printf("\nNao ha mais vagas disponiveis.\n\n");
        return;
    }

    printf("\n--- REGISTRAR ENTRADA ---\n");
    do {
        printf("Digite a placa do veiculo (ate 8 caracteres sem espaco): ");
        scanf("%s", placas[vaga]);
        if (strlen(placas[vaga]) > 8)
            printf("Placa invalida, tente novamente.\n");
    } while (strlen(placas[vaga]) > 8);

    int tipo;
    do {
        printf("Tipo do veiculo (1-moto, 2-carro e 3-caminhonete): ");
        scanf("%d", &tipo);
        if (tipo != 3 && tipo != 2 && tipo != 1)
            printf("Tipo invalido, tente novamente.\n");
    } while (tipo != 3 && tipo != 2 && tipo != 1);

    if (tipo == 1)
        contMoto++;
    else if (tipo == 2)
        contCarro++;
    else if (tipo == 3)
        contCaminhonete++;

    tipos[vaga] = tipo;

    int hora;
    do {
        printf("Digite horario de entrada (0-23): ");
        scanf("%d", &hora);

        if (hora > 23 || hora < 0)
            printf("Hora invalida, tente novamente.\n");

        horasEntrada[vaga] = hora;
    } while (hora > 23 || hora < 0);

    ocupadas[vaga] = 1;
    totalVeiculos++;
    printf("Veiculo registrado na vaga %d.\n\n", vaga + 1);
}

// Calcula o valor total a pagar multiplicando a tarifa do tipo do veiculo pelas horas estacionadas
float calcularValor(int tipo, int horas) {
    switch (tipo) {
        case 1:
            return tarifamoto * horas;
        case 2:
            return tarifacarro * horas;
        case 3:
            return tarifacaminhonete * horas;
        default:
            return 0;
    }
}

// Lista todos os veiculos atualmente estacionados com seu tipo, placa e numero da vaga
void listarVeiculos() {
    printf("\n--- LISTA DE VEICULOS ---\n");
    int vazio = 1;

    for (int i = 0; i < VAGAS; i++) {
        if (ocupadas[i] == 1 && tipos[i] == 1) {
            vazio = 0;
            printf("Moto com placa %s na vaga %d.\n", placas[i], i + 1);
        } else if (ocupadas[i] == 1 && tipos[i] == 2) {
            vazio = 0;
            printf("Carro com placa %s na vaga %d.\n", placas[i], i + 1);
        } else if (ocupadas[i] == 1 && tipos[i] == 3) {
            vazio = 0;
            printf("Caminhonete com placa %s na vaga %d.\n", placas[i], i + 1);
        }
    }

    if (vazio == 1)
        printf("Nao ha veiculos no estacionamento.\n");

    printf("\n");
}

// Localiza o veiculo pela placa, calcula o tempo (incluindo virada de meia-noite), cobra e libera a vaga
void registrarSaida() {
    char placa[9];
    printf("\n--- SAIDA DE VEICULO ---\n");

    do {
        printf("Digite a placa do veiculo para registrar saida (ate 8 caracteres sem espaco): ");
        scanf("%s", placa);
        if (strlen(placa) > 8)
            printf("Placa invalida, tente novamente.\n");
    } while (strlen(placa) > 8);

    if (buscarPlaca(placa) >= 0) {
        int horariosaida, totalhoras;
        int vaga = buscarPlaca(placa);

        do {
            printf("Digite o horario de saida (0-23): ");
            scanf("%d", &horariosaida);
            if (horariosaida > 23 || horariosaida < 0)
                printf("Horario invalido, tente novamente.\n");
        } while (horariosaida > 23 || horariosaida < 0);

        if (horariosaida < horasEntrada[vaga]) {
            totalhoras = (horariosaida + 24) - horasEntrada[vaga];
        } else if (horariosaida > horasEntrada[vaga]) {
            totalhoras = horariosaida - horasEntrada[vaga];
        } else {
            totalhoras = 1;
        }

        ocupadas[vaga] = 0;
        float valor = calcularValor(tipos[vaga], totalhoras);
        totalArrecadado += valor;

        printf("Tempo total: %d hora(s)\n", totalhoras);
        printf("Valor a pagar: %.2f\n\n", valor);
    } else {
        printf("Veiculo nao encontrado.\n\n");
    }
}

// Funcao principal: configura as tarifas iniciais e controla o laco de execucao do menu
int main() {
    printf("Digite o valor por hora do tipo moto: ");
    scanf("%f", &tarifamoto);
    printf("Digite o valor por hora do tipo carro: ");
    scanf("%f", &tarifacarro);
    printf("Digite o valor por hora do tipo caminhonete: ");
    scanf("%f", &tarifacaminhonete);

    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarEntrada();
                break;
            case 2:
                registrarSaida();
                break;
            case 3:
                listarVeiculos();
                break;
            case 4:
                exibirRelatorio();
                break;
            case 5:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
