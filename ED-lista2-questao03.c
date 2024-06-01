/*
** Função : Desenvolver um sistema de registro de estudantes em C, utilizando TADs, Listas, Pilhas, Filas e Deques para gerenciar informações dos estudantes.
** Autor : Marlon Rufino do nascimento 2º período turma A 2024.1
** Data : 28/05/2024
** Observações: Estou utilizando a função 'setlocale' da biblioteca 'locale.h' para a representação de acentuação padrão da lingua portuguesa, tais como ´, ^, `, ª ...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct Estudante {
    char nome[100];
    int matricula;
    char disciplinas[10][100];
    int numDisciplinas;
    float notas[3]; // Supondo que o número de notas do estudante seja 3
} Estudante;

typedef struct ListaEstudante {
    Estudante estudante;
    struct ListaEstudante* proximo;
} ListaEstudante;

typedef struct PilhaHistoricoNotas {
    char disciplina[100];
    float notas[3];
    struct PilhaHistoricoNotas* proximo;
} PilhaHistoricoNotas;

typedef struct FilaDeMatricula {
    Estudante estudante;
    struct FilaDeMatricula* proximo;
} FilaDeMatricula;

typedef struct FilaDeDisciplina{
    char nome[100];
    FilaDeMatricula* primeiro;
    FilaDeMatricula* ultimo;
    int quantidade; // Quantidade de estudantes na fila
    int limite;
} FilaDeDisciplina;

typedef struct DequeEsperaAtendimento {
    Estudante estudante;
    struct DequeEsperaAtendimento* final;
    struct DequeEsperaAtendimento* comeco;
} DequeEsperaAtendimento;

void adicionarEstudante(ListaEstudante** inicio, char nome[100], int matricula) {
    // Cria um novo nodo para o estudante
    ListaEstudante* novoNodo = (ListaEstudante*)malloc(sizeof(ListaEstudante));
    if (novoNodo == NULL) {
        printf("Erro: falha ao alocar memória para o novo estudante.\n");
        return;
    }
    
    // Inicializa um novo estudante com número de disciplinas igual a 0
    Estudante novoEstudante;
    strcpy(novoEstudante.nome, nome);
    novoEstudante.matricula = matricula;
    novoEstudante.numDisciplinas = 0; // Número de disciplinas igual a 0
    for (int i = 0; i < 10; i++) {
        novoEstudante.disciplinas[i][0] = '\0'; // Inicializa todas as disciplinas como vazias
    }
    
    // Define o estudante e aponta para o próximo nodo
    novoNodo->estudante = novoEstudante;
    novoNodo->proximo = *inicio;
    
    // Atualiza o início da lista
    *inicio = novoNodo;
    
    printf("Estudante adicionado com sucesso!\n");
}

void removerEstudante(ListaEstudante** inicio, int matricula) {
    ListaEstudante* temp = *inicio, *prev = NULL;

    if (temp != NULL && temp->estudante.matricula == matricula) {
        *inicio = temp->proximo;
        free(temp);
        printf("\nRemoção sucedida!\n");
        return;
    }

    while (temp != NULL && temp->estudante.matricula != matricula) {
        prev = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Estudante não encontrado!\n");
        return;
    }

    prev->proximo = temp->proximo;
    free(temp);
    printf("\nRemoção sucedida!\n");
}

int verifica_lista_estudante_vazia(ListaEstudante* inicio) {
    return (inicio != NULL);
}

Estudante* buscarEstudante(ListaEstudante* inicio, int matricula) {
    ListaEstudante* atual = inicio;
    while (atual != NULL) {
        if (atual->estudante.matricula == matricula) {
            printf("\nEstudante encontrado!\n");
            return &(atual->estudante);
        }
        atual = atual->proximo;
    }
    printf("\nEstudante não encontrado!\n");
    return NULL;
}


int verifica_aluno_matriculado(Estudante *estudante) {
    return estudante->numDisciplinas > 0;
}

void empilharNotas(PilhaHistoricoNotas** topo, Estudante* estudante) {
    // Verifica se o estudante tem disciplinas cadastradas
    if (!verifica_aluno_matriculado(estudante)) {
        printf("\nO aluno não tem disciplinas cadastradas!\n");
        return;
    }

    // Solicita o nome da disciplina a ser atualizada
    char nomeDisciplina[100];
    printf("\nDigite o nome da disciplina para atualizar as notas: ");
    scanf(" %[^\n]", nomeDisciplina);

    // Verifica se a disciplina está cadastrada para o estudante
    int disciplinaEncontrada = 0;
    for (int i = 0; i < estudante->numDisciplinas; i++) {
        if (strcmp(estudante->disciplinas[i], nomeDisciplina) == 0) {
            disciplinaEncontrada = 1;
            break;
        }
    }

    if (!disciplinaEncontrada) {
        printf("\nA disciplina %s não está cadastrada para o estudante.\n", nomeDisciplina);
        return;
    }

    // Cria um novo nodo para armazenar as notas
    PilhaHistoricoNotas* novoNodo = (PilhaHistoricoNotas*)malloc(sizeof(PilhaHistoricoNotas));
    if (novoNodo == NULL) {
        printf("\nErro ao alocar memória para o histórico de notas.\n");
        return;
    }

    // Solicita as notas da disciplina ao usuário
    printf("\nDigite as notas da disciplina %s:\n", nomeDisciplina);
    for (int i = 0; i < 3; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &novoNodo->notas[i]);
    }

    // Copia o nome da disciplina para o nodo
    strcpy(novoNodo->disciplina, nomeDisciplina);

    // Empilha o nodo no topo da pilha
    novoNodo->proximo = *topo;
    *topo = novoNodo;

    printf("\nNotas da disciplina %s atualizadas com sucesso!\n", nomeDisciplina);
}

void exibirNotasEstudante(PilhaHistoricoNotas** topo, Estudante* estudante) {
    if (*topo == NULL) {
        printf("\nNão há notas registradas para este estudante.\n");
        return;
    }

    PilhaHistoricoNotas* atual = *topo;
    int encontrouNota = 0;

    while (atual != NULL) {
        for (int i = 0; i < estudante->numDisciplinas; i++) {
            if (strcasecmp(atual->disciplina, estudante->disciplinas[i]) == 0) {
                printf("\nDisciplina: %s\n", atual->disciplina);
                printf("Notas: %.1f, %.1f, %.1f\n", atual->notas[0], atual->notas[1], atual->notas[2]);
                float media = (atual->notas[0] + atual->notas[1] + atual->notas[2]) / 3;
                printf("Média: %.1f\n", media);
                encontrouNota = 1;
            }
        }
        atual = atual->proximo;
    }

    if (!encontrouNota) {
        printf("\nNenhuma nota encontrada para as disciplinas do estudante.\n");
    }
}

void inicializarFila(FilaDeDisciplina* fila, char *nome_da_disciplina, int limite_da_fila) {
    strcpy(fila->nome, nome_da_disciplina); 
    fila->primeiro = fila->ultimo = NULL;
    fila->limite = limite_da_fila;
    fila->quantidade = 0; 
}

FilaDeDisciplina* buscarFila(FilaDeDisciplina filas[], int numFilas, char *nome_da_disciplina) {
    for (int i = 0; i < numFilas; i++) {
        if (strcmp(filas[i].nome, nome_da_disciplina) == 0) {
            // Retorna um ponteiro para a fila de disciplina encontrada
            return &filas[i];
        }
    }
    // Retorna NULL se a fila de disciplina não for encontrada
    return NULL;
}

int verificaFilaVazia(FilaDeDisciplina fila) {
    return (fila.quantidade == 0);
}

void adicionar_estudante_a_fila(FilaDeDisciplina* fila, Estudante estudante) {
    if (fila->quantidade >= fila->limite) {
        printf("A fila de matrícula para a disciplina %s já atingiu seu limite.\n", fila->nome);
        return;
    }

    // Verificar se o estudante já está na fila
    FilaDeMatricula* atual = fila->primeiro;
    while (atual != NULL) {
        if (atual->estudante.matricula == estudante.matricula) {
            printf("O estudante já está matriculado na disciplina %s.\n", fila->nome);
            return;
        }
        atual = atual->proximo;
    }

    // Se o estudante não estiver na fila, adicioná-lo
    FilaDeMatricula* novoNodo = (FilaDeMatricula*)malloc(sizeof(FilaDeMatricula));
    if (novoNodo == NULL) {
        printf("Erro ao alocar memória para o novo estudante.\n");
        return;
    }

    novoNodo->estudante = estudante;
    novoNodo->proximo = NULL;

    if (fila->ultimo == NULL) {
        fila->primeiro = fila->ultimo = novoNodo;
    } else {
        fila->ultimo->proximo = novoNodo;
        fila->ultimo = novoNodo;
    }
    printf("Estudante '%s' adicionado à fila da disciplina '%s' com sucesso.\n",estudante.nome, fila->nome);
    fila->quantidade++;
}


Estudante* matricular_estudante(FilaDeDisciplina* fila, ListaEstudante *estudantes) {
    if (fila->primeiro == NULL) {
        return NULL;
    }
    
    FilaDeMatricula* temp = fila->primeiro;
    fila->primeiro = fila->primeiro->proximo;
    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    Estudante* estudanteTemp = &(temp->estudante);
    
    // Verifica se o estudante existe na lista de estudantes
    Estudante *estudante = buscarEstudante(estudantes, estudanteTemp->matricula);
    
    if (estudante != NULL) {
        // Adiciona a disciplina ao array de disciplinas do estudante
        int i;
        for (i = 0; i < 10; i++) {
            if (strlen(estudante->disciplinas[i]) == 0) {
                strcpy(estudante->disciplinas[i], fila->nome);
                estudante->numDisciplinas++;
                break;
            }
        }
    }

    free(temp);
    fila->quantidade--;

    return estudante;
}

void inicializarDeque(DequeEsperaAtendimento** primeiro, DequeEsperaAtendimento** ultimo) {
    *primeiro = *ultimo = NULL;
}

int estudanteEstaNoDeque(DequeEsperaAtendimento* primeiro, const Estudante* estudante) {
    DequeEsperaAtendimento* atual = primeiro;
    while (atual != NULL) {
        if (strcmp(atual->estudante.nome, estudante->nome) == 0 && atual->estudante.matricula == estudante->matricula) {
            return 1; // Estudante encontrado no deque
        }
        atual = atual->final;
    }
    return 0; // Estudante não encontrado no deque
}

void adicionarInicioDeque(DequeEsperaAtendimento** primeiro, DequeEsperaAtendimento** ultimo, Estudante estudante) {
    if (estudanteEstaNoDeque(*primeiro, &estudante)) {
        printf("\nEstudante já está presente no deque.\n");
        return;
    }

    DequeEsperaAtendimento* novoNodo = (DequeEsperaAtendimento*)malloc(sizeof(DequeEsperaAtendimento));
    novoNodo->estudante = estudante;
    novoNodo->final = *primeiro;
    novoNodo->comeco = NULL;
    if (*primeiro == NULL) {
        *primeiro = *ultimo = novoNodo;
    } else {
        (*primeiro)->comeco = novoNodo;
        *primeiro = novoNodo;
    }
    printf("\nEstudante '%s' adicionado no início do deque.\n", estudante.nome);
}

void adicionarFimDeque(DequeEsperaAtendimento** primeiro, DequeEsperaAtendimento** ultimo, Estudante estudante) {
    if (estudanteEstaNoDeque(*primeiro, &estudante)) {
        printf("\nEstudante já está presente no deque.\n");
        return;
    }

    DequeEsperaAtendimento* novoNodo = (DequeEsperaAtendimento*)malloc(sizeof(DequeEsperaAtendimento));
    novoNodo->estudante = estudante;
    novoNodo->final = NULL;
    novoNodo->comeco = *ultimo;
    if (*ultimo == NULL) {
        *primeiro = *ultimo = novoNodo;
    } else {
        (*ultimo)->final = novoNodo;
        *ultimo = novoNodo;
    }
       printf("\nEstudante '%s' adicionado ao fim do deque.\n", estudante.nome);
}

Estudante* removerInicioDeque(DequeEsperaAtendimento** primeiro, DequeEsperaAtendimento** ultimo) {
    if (*primeiro == NULL) {
        return NULL;
    }
    DequeEsperaAtendimento* temp = *primeiro;
    *primeiro = (*primeiro)->final;
    if (*primeiro == NULL) {
        *ultimo = NULL;
    } else {
        (*primeiro)->comeco = NULL;
    }
    Estudante* estudante = (Estudante*)malloc(sizeof(Estudante));
    if (estudante == NULL) {
        // Tratar falha na alocação de memória
        return NULL;
    }
    *estudante = temp->estudante;
    free(temp);
    return estudante;
}

Estudante* removerFimDeque(DequeEsperaAtendimento** primeiro, DequeEsperaAtendimento** ultimo) {
    if (*ultimo == NULL) {
        return NULL;
    }
    DequeEsperaAtendimento* temp = *ultimo;
    *ultimo = (*ultimo)->comeco;
    if (*ultimo == NULL) {
        *primeiro = NULL;
    } else {
        (*ultimo)->final= NULL;
    }
    Estudante* estudante = (Estudante*)malloc(sizeof(Estudante));
    if (estudante == NULL) {
        // Tratar falha na alocação de memória
        return NULL;
    }
    *estudante = temp->estudante;
    free(temp);
    return estudante;
}

float calcularMedia(float notas[3]) {
    return (notas[0] + notas[1] + notas[2]) / 3;
}

void exibirEstudantes(ListaEstudante* inicio) {
    ListaEstudante* atual = inicio;
    while (atual != NULL) {
        printf("\nNome: %s \nMatrícula: %d\n",
            atual->estudante.nome, atual->estudante.matricula);
        atual = atual->proximo;
    }
}

void exibirFilaMatricula(FilaDeDisciplina* fila) {
    if (fila->quantidade == 0) {
        printf("\nNão há estudantes na fila de matrícula.\n");
        return;
    }
    printf("\nEstudantes na fila de matrícula da disciplina %s:\n", fila->nome);
    FilaDeMatricula* atual = fila->primeiro;
    while (atual != NULL) {
        printf("\nNome: %s, Matrícula: %d\n", atual->estudante.nome, atual->estudante.matricula);
        atual = atual->proximo;
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");

    ListaEstudante* listaEstudantes = NULL;
    PilhaHistoricoNotas* historicoNotas = NULL;
    DequeEsperaAtendimento *dequeprimeiro, *dequeultimo;
    FilaDeDisciplina filas[10];
    int numFilas = 0; 
    inicializarDeque(&dequeprimeiro, &dequeultimo);

    int opcao;
    int matricula;
    Estudante estudante;
    Estudante *estudanteDoDeque;
    char nomeDisciplina[100];
    int capacidadeDisciplina;

    
     int verifica_cadastro_disciplina;
    
    do {
        printf("\n----- Menu Principal -----\n");
        printf("1. Gerenciar Lista de Estudantes\n");
        printf("2. Gerenciar Pilha de Histórico de Notas\n");
        printf("3. Gerenciar Fila de Matrícula em Disciplinas\n");
        printf("4. Gerenciar Deque de Espera para Atendimento\n");
        printf("5. Salvar tudo em um arquivo.txt\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    printf("\n----- Lista de Estudantes -----\n");
                    printf("1. Adicionar Estudante\n");
                    printf("2. Remover Estudante\n");
                    printf("3. Buscar Estudante\n");
                    printf("4. Exibir Todos os Estudantes\n");
                    printf("0. Voltar ao Menu Principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            printf("\nNome do Estudante: ");
                            scanf(" %[^\n]s", estudante.nome);

                            int numero = rand() % 90000 + 10000; // Números de 10000 a 99999
                            estudante.matricula = numero;   

                            adicionarEstudante(&listaEstudantes, estudante.nome,estudante.matricula);
                            break
;

                        case 2:
                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                printf("\nNenhum estudante cadastrado!\n");
                                break;
                              }   
                            printf("Matrícula do Estudante a remover: ");
                            scanf("%d", &matricula);
                            removerEstudante(&listaEstudantes, matricula);
                            break;

                         case 3:
                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                printf("\nNenhum estudante cadastrado!\n");
                                break;
                              }  

                            printf("Matrícula do Estudante a buscar: ");
                            scanf("%d", &matricula);
                            Estudante *estudante = buscarEstudante(listaEstudantes, matricula);
                            if (estudante != NULL) {
                                printf("\nNome: %s, Matrícula: %d\n", estudante->nome, estudante->matricula);
                            }
                            break;

                        case 4:
                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                printf("\nNenhum estudante cadastrado!\n");
                                break;
                              }  
                            printf("\n------------- LISTA DE ESTUDANTES: ---------------\n");
                            exibirEstudantes(listaEstudantes);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Opção inválida! Tente novamente.\n");
                            break;
                    }
                } while (opcao != 0);
                opcao = -1;  
                break;

         case 2:
    do {
        printf("\n----- Pilha de Histórico de Notas -----\n");
        printf("1. Atualizar Notas do Estudante\n");
        printf("2. Exibir notas do Estudante\n"); 
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                    if(!verifica_lista_estudante_vazia(listaEstudantes)){
                    printf("\nNenhum estudante cadastrado!\n");
                    break;
                }
                printf("Matrícula do Estudante para atualizar notas: ");
                scanf("%d", &matricula);
                Estudante* estudanteAtualizado = buscarEstudante(listaEstudantes, matricula);
                if (estudanteAtualizado != NULL) {
                    empilharNotas(&historicoNotas, estudanteAtualizado);
                } else {
                    printf("Estudante não encontrado.\n");
                }
                break;
            case 2:
                    if(!verifica_lista_estudante_vazia(listaEstudantes)){
                        printf("\nNenhum estudante cadastrado!\n");
                    break;
                    }
                printf("Matrícula do Estudante para exibir as notas: ");
                scanf("%d", &matricula);
                Estudante* estudanteAtual = buscarEstudante(listaEstudantes, matricula);
                if (estudanteAtual != NULL) {
                    printf("Notas do Estudante %s (Matrícula: %d):\n", estudanteAtual->nome, estudanteAtual->matricula);
                    exibirNotasEstudante(&historicoNotas, estudanteAtual);
                            } else {
                                printf("Estudante não encontrado.\n");
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                            break;
                    }
                } while (opcao != 0);
                opcao = -1;
                break;
            case 3:
                do {
                    printf("\n----- Fila de Matrícula em Disciplinas -----\n");
                    printf("1. Definir Disciplina e Capacidade\n");
                    printf("2. Adicionar Estudante na Fila de Matrícula\n");
                    printf("3. Matricular Estudante da Fila\n");
                    printf("4. Exibir Fila de Matrícula\n");
                    printf("0. Voltar ao Menu Principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            if (numFilas < 10) {
                                    printf("\nNome da Disciplina: ");
                                    scanf(" %[^\n]s", nomeDisciplina);
                                    printf("Capacidade da Disciplina: ");
                                    scanf("%d", &capacidadeDisciplina);

                                    // Aloca memória dinamicamente para uma nova fila de disciplina
                                    FilaDeDisciplina *novaFila = (FilaDeDisciplina *)malloc(sizeof(FilaDeDisciplina));
                                    if (novaFila == NULL) {
                                        printf("\nErro: não foi possível alocar memória para a nova fila de disciplina.\n");
                                        break;
                                    }

                                    // Inicializa a nova fila de disciplina
                                    inicializarFila(novaFila, nomeDisciplina, capacidadeDisciplina);

                                    // Adiciona a nova fila ao array de filas de disciplina
                                    filas[numFilas++] = *novaFila;
                                    verifica_cadastro_disciplina = 1;
                                    printf("\nDisciplina '%s' adicionada com sucesso!\n", nomeDisciplina);
                                } else {
                                    printf("\nNúmero máximo de filas de disciplina atingido!\n");
                                }
                                break;
                         case 2:    


                                // Se todas as filas estiverem vazias, exibe a mensagem e interrompe a execução
                                if (verifica_cadastro_disciplina != 1) {
                                    printf("\nNenhuma Disciplina cadastrada!\n");
                                    break;
                                }
                                if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                printf("\nNenhum estudante cadastrado!\n");
                                break;
                              }  

                                    printf("Digite a matrícula do Estudante que quer adicionar: ");
                                    scanf("%d", &matricula);
                                    Estudante *estudante = buscarEstudante(listaEstudantes, matricula);
                                    if(estudante != NULL) {
                                       printf("\nNome: %s, Matrícula: %d\n", estudante->nome, estudante->matricula);

                                        printf("Digite o nome da disciplina que deseja ingressar na fila: ");
                                        scanf(" %[^\n]s", nomeDisciplina);

                                        printf("\n");
                                        FilaDeDisciplina *fila = buscarFila(filas, numFilas, nomeDisciplina);
                                        if (fila != NULL) {
                                            adicionar_estudante_a_fila(fila, *estudante);
                                        } else {
                                            printf("\nA disciplina não foi encontrada.\n");
                                        }
                                    } else {
                                        printf("\nEstudante com matrícula %d não encontrado.\n", matricula);
                                    }
                                    break;
                           case 3:
                                // Verifica se há disciplinas cadastradas
                                if (numFilas == 0) {
                                    printf("\nNenhuma disciplina cadastrada!\n");
                                    break;
                                }

                                printf("Digite o nome da disciplina para matricular um estudante: ");
                                scanf(" %[^\n]s", nomeDisciplina);

                                // Busca a fila da disciplina desejada
                                FilaDeDisciplina *fila = buscarFila(filas, numFilas, nomeDisciplina);

                                if (fila != NULL) {
                                    // Matricula o próximo estudante na fila específica
                                    Estudante* estudante = matricular_estudante(fila, listaEstudantes);

                                    if (estudante != NULL && strcmp(estudante->nome, "") != 0) {
                                        // Exibe o nome do estudante matriculado na disciplina
                                        printf("\n%s matriculado na disciplina %s.\n", estudante->nome, nomeDisciplina);
                                    } else {
                                        printf("\nNão foi possível matricular um estudante na disciplina %s. Fila vazia.\n", nomeDisciplina);
                                    }
                                } else {
                                    printf("\nA disciplina %s não foi encontrada.\n", nomeDisciplina);
                                }
                                break;
                     case 4:
                        if (verifica_cadastro_disciplina != 1) {
                            printf("\nNenhuma Disciplina cadastrada!\n");
                            break;
                        }

                        printf("Digite o nome da disciplina para exibir a fila de matrícula: ");
                        scanf(" %[^\n]s", nomeDisciplina);
                        FilaDeDisciplina *fila_buscada = buscarFila(filas, numFilas, nomeDisciplina);
                        if (fila_buscada != NULL) {
                            exibirFilaMatricula(fila_buscada);
                        } else {
                            printf("\nA disciplina não foi encontrada.\n");
                        }
                        break;
                        case 0:
                            break;

                        default:
                            printf("\nOpção inválida! Tente novamente.\n");
                            break;
                    }
                } while (opcao != 0);
                opcao = -1;  
                break;
                    case 4:
                                do {
                                    printf("\n----- Deque de Espera para Atendimento -----\n");
                                    printf("1. Adicionar Estudante no Início do Deque\n");
                                    printf("2. Adicionar Estudante no Fim do Deque\n");
                                    printf("3. Remover Estudante do Início do Deque\n");
                                    printf("4. Remover Estudante do Fim do Deque\n");
                                    printf("5. Exibir Deque de Espera\n");
                                    printf("6. Buscar Estudante no Deque\n");
                                    printf("0. Voltar ao Menu Principal\n");
                                    printf("Escolha uma opção: ");
                                    scanf("%d", &opcao);

                                    switch (opcao) {
                                        case 1:
                                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                printf("\nNenhum estudante cadastrado!\n");
                                                break;
                                            }
                                            printf("Digite a matrícula do Estudante: ");
                                            scanf("%d", &matricula);
                                            Estudante* estudanteInicio = buscarEstudante(listaEstudantes, matricula);
                                            if (estudanteInicio != NULL) {
                                                adicionarInicioDeque(&dequeprimeiro, &dequeultimo, *estudanteInicio);
                                            }
                                            break;

                                        case 2:
                                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                printf("\nNenhum estudante cadastrado!\n");
                                                break;
                                            }
                                            printf("Digite a matrícula do Estudante: ");
                                            scanf("%d", &matricula);
                                            Estudante* estudanteFim = buscarEstudante(listaEstudantes, matricula);
                                            if (estudanteFim != NULL) {
                                                adicionarFimDeque(&dequeprimeiro, &dequeultimo, *estudanteFim);
                                            }
                                            break;

                                        case 3:
                                            if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                printf("\nNenhum estudante cadastrado!\n");
                                                break;
                                            }
                                            estudanteDoDeque = removerInicioDeque(&dequeprimeiro, &dequeultimo);
                                            if (estudanteDoDeque->matricula != 0) {
                                                printf("\nEstudante removido do início do deque: %s\n", estudanteDoDeque->nome);
                                            } else {
                                                printf("\nDeque de atendimento vazio.\n");
                                            }
                                            break;

                                        case 4:
                                             if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                printf("\nNenhum estudante cadastrado!\n");
                                                break;
                                            }
                                            estudanteDoDeque = removerFimDeque(&dequeprimeiro, &dequeultimo);
                                            if (estudanteDoDeque->matricula != 0) {
                                                printf("\nEstudante removido do fim do deque: %s\n", estudanteDoDeque->nome);
                                            } else {
                                                printf("\nDeque de atendimento vazio.\n");
                                            }
                                           break;
                                        case 5:
                                             if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                printf("\nNenhum estudante cadastrado!\n");
                                                break;
                                            }
                                            if (dequeprimeiro == NULL) {
                                                printf("\nDeque de atendimento vazio.\n");
                                            } else {
                                                printf("\n----- Deque de Espera -----\n");
                                                DequeEsperaAtendimento *atual = dequeprimeiro;
                                                int i = 0;
                                                while (atual != NULL) {
                                                    printf("%d. Nome: %s, Matrícula: %d\n",i + 1, atual->estudante.nome, atual->estudante.matricula);
                                                    atual = atual->final;
                                                    i++;
                                                }
                                            }
                                            break;
                                        case 6:
                                                if (!verifica_lista_estudante_vazia(listaEstudantes)) {
                                                    printf("\nNenhum estudante cadastrado!\n");
                                                    break;
                                                }
                                                printf("Digite a matrícula do Estudante que deseja buscar: ");
                                                scanf("%d", &matricula);
                                                DequeEsperaAtendimento* atual = dequeprimeiro;
                                                int encontrou = 0;
                                            int posicao = 0;
                                            while (atual != NULL) {
                                                if (atual->estudante.matricula == matricula) {
                                                    printf("\nEstudante encontrado no deque:\n");
                                                    printf("Posição: %d\n", posicao + 1);
                                                    printf("Nome: %s, Matrícula: %d\n", atual->estudante.nome, atual->estudante.matricula);
                                                    encontrou = 1;
                                                    break;
                                                }
                                                atual = atual->final;
                                                posicao++;
                                            }
                                                if (!encontrou) {
                                                    printf("\nEstudante com matrícula %d não encontrado no deque.\n", matricula);
                                                }
                                                break;
                                        case 0:
                                            break;

                                        default:
                                            printf("Opção inválida! Tente novamente.\n");
                                            break;
                                        }
                                    } while (opcao != 0);
                                    opcao = -1;
                                    break;
                        case 5: {
                                    // Abre o arquivo para escrita
                                    FILE* arquivo = fopen("ED-lista2-questao03.txt", "w");
                                    if (arquivo == NULL) {
                                        printf("Erro ao abrir o arquivo.\n");
                                        return 1;
                                    }

                                    // Escreve os dados da lista de estudantes no arquivo
                                    fprintf(arquivo, "=== Lista de Estudantes ===\n");
                                    ListaEstudante* estudanteAtual = listaEstudantes;
                                    while (estudanteAtual != NULL) {
                                        fprintf(arquivo, "Nome: %s, Matrícula: %d\n", estudanteAtual->estudante.nome, estudanteAtual->estudante.matricula);
                                        estudanteAtual = estudanteAtual->proximo;
                                    }
                                    fprintf(arquivo, "\n");

                                    // Escreve os dados de todas as filas de matrícula no arquivo
                                    fprintf(arquivo, "\n === Fila de Matrícula === \n");
                                    for (int i = 0; i < numFilas; i++) {
                                        FilaDeMatricula* atual = filas[i].primeiro;
                                        fprintf(arquivo, "Disciplina: %s\n", filas[i].nome);
                                        int j = 0;
                                        while (atual != NULL) {
                                            fprintf(arquivo, "%d. Nome: %s, Matrícula: %d\n", j + 1, atual->estudante.nome, atual->estudante.matricula);
                                            atual = atual->proximo;
                                            j++;
                                        }
                                        fprintf(arquivo, "\n");
                                    }
                                    fprintf(arquivo, "\n");

                          // Escreve os dados do histórico de notas no arquivo
                                    fprintf(arquivo, "\n=== Histórico de Notas ===\n");
                                    ListaEstudante* estudanteAtualNotas = listaEstudantes;
                                    while (estudanteAtualNotas != NULL) {
                                        if(verifica_aluno_matriculado(estudanteAtualNotas)){
                                        fprintf(arquivo, "Aluno: %s, Matrícula: %d\n", estudanteAtualNotas->estudante.nome, estudanteAtualNotas->estudante.matricula);
                                        for (int i = 0; i < estudanteAtualNotas->estudante.numDisciplinas; i++) {
                                            PilhaHistoricoNotas* atualHistorico = historicoNotas;
                                            while (atualHistorico != NULL) {
                                                if (strcasecmp(atualHistorico->disciplina, estudanteAtualNotas->estudante.disciplinas[i]) == 0) {
                                                    fprintf(arquivo, "Disciplina: %s, Notas: %.1f, %.1f, %.1f, Média: %.1f\n",
                                                            atualHistorico->disciplina,
                                                            atualHistorico->notas[0],
                                                            atualHistorico->notas[1],
                                                            atualHistorico->notas[2],
                                                            (atualHistorico->notas[0] + atualHistorico->notas[1] + atualHistorico->notas[2]) / 3.0);
                                                    break;
                                                }
                                                atualHistorico = atualHistorico->proximo;
                                            }
                                        }
                                        }
                                        fprintf(arquivo, "\n");
                                        estudanteAtualNotas = estudanteAtualNotas->proximo;
                                    }

                                   // Escreve os dados do deque de espera de atendimento no arquivo
                                    fprintf(arquivo, "\n=== Deque de Espera de Atendimento ===\n");
                                    DequeEsperaAtendimento* temp = dequeprimeiro;
                                    int n = 0;
                                    while (temp != NULL) {
                                        fprintf(arquivo, "%d. Nome: %s, Matrícula: %d\n", n + 1, temp->estudante.nome, temp->estudante.matricula);
                                        temp = temp->final; // Percorre até o final
                                        n++;
                                    }

                                    fclose(arquivo); // Fecha o arquivo
                                    printf("\nDados salvos em arquivo com sucesso!\n");
                                    break;
                                }
                        case 0:
                            printf("Saindo...\n");
                            break;

                        default:
                            printf("Opção inválida! Tente novamente.\n");
                            break;
                    }
                } while (opcao != 0);

                return 0;
            }   