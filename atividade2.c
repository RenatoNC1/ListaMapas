#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Definições da Estrutura ---

// Tipo de dado a ser armazenado na pilha (simulando uma operação da calculadora)
typedef int TElemento; 
#define VALOR_ERRO -99999 // Valor de retorno para indicar erro (ex: pop em pilha vazia)

// 1. Estrutura do Nó (Cada elemento da Pilha)
typedef struct No {
    TElemento dado;
    struct No *anterior; // Ponteiro para o nó abaixo (anterior)
} No;

// 2. Estrutura da Pilha (Contém apenas o ponteiro para o topo)
typedef struct {
    No *topo;
} Pilha;

// --- Funções Auxiliares ---

/**
 * @brief Inicializa a pilha.
 * @param p Ponteiro para a estrutura Pilha.
 */
void inicializar_pilha(Pilha *p) {
    p->topo = NULL; // NULL indica que a pilha está vazia
}

/**
 * @brief Verifica se a pilha está vazia.
 * @param p A estrutura Pilha.
 * @return true se a pilha estiver vazia (topo é NULL), false caso contrário.
 */
bool is_empty(Pilha p) {
    // A pilha está vazia se o ponteiro do topo for NULL
    return p.topo == NULL;
}

// --- Funções da Pilha (PUSH e POP) ---

/**
 * @brief Insere um novo elemento no topo da pilha (operação PUSH).
 *
 * @param p Ponteiro para a estrutura Pilha.
 * @param valor O valor a ser inserido.
 * @return true se a inserção foi bem-sucedida, false em caso de erro de alocação de memória.
 */
bool push(Pilha *p, TElemento valor) {
    // 1. Aloca memória para o novo nó
    No *novoNo = (No *)malloc(sizeof(No));

    if (novoNo == NULL) {
        // Erro: falha na alocação de memória (Pilha cheia do sistema)
        printf("ERRO: Falha na alocacao de memoria. O push nao foi realizado.\n");
        return false;
    }

    // 2. Atribui os dados ao novo nó
    novoNo->dado = valor;
    
    // 3. O ponteiro 'anterior' do novo nó aponta para o que era o 'topo'
    novoNo->anterior = p->topo; 
    
    // 4. Atualiza o 'topo' da pilha para ser o novo nó
    p->topo = novoNo;
    
    return true;
}

/**
 * @brief Remove o elemento do topo da pilha (operação POP).
 *
 * @param p Ponteiro para a estrutura Pilha.
 * @return O valor do elemento removido. Retorna VALOR_ERRO se a pilha estiver vazia.
 */
TElemento pop(Pilha *p) {
    if (is_empty(*p)) {
        printf("ERRO: Pilha vazia. Nao ha elementos para remover.\n");
        return VALOR_ERRO;
    }

    // 1. Guarda uma referência para o nó que está no topo
    No *no_removido = p->topo;

    // 2. Guarda o valor a ser retornado
    TElemento valor_removido = no_removido->dado;

    // 3. Atualiza o topo: o novo topo é o nó 'anterior' ao atual (LIFO)
    p->topo = no_removido->anterior;

    // 4. Libera a memória alocada para o nó removido
    free(no_removido);

    return valor_removido;
}


/**
 * @brief Função principal para demonstração.
 */
int main() {
    Pilha historico_operacoes;
    inicializar_pilha(&historico_operacoes);
    TElemento resultado_pop;

    printf("--- Simulacao do Historico de Operacoes da Calculadora ---\n");
    printf("A pilha esta vazia? %s\n", is_empty(historico_operacoes) ? "Sim" : "Nao"); // Deve ser Sim

    // 1. Inserir operações (PUSH)
    printf("\n--- Inserindo operacoes (PUSH) ---\n");
    
    // Operação: Soma (1)
    if (push(&historico_operacoes, 1)) {
        printf("  -> Inserido no historico: Soma\n"); 
    }
    
    // Operação: Subtração (2)
    if (push(&historico_operacoes, 2)) {
        printf("  -> Inserido no historico: Subtracao\n"); 
    }
    
    // Operação: Multiplicação (3 - TOPO)
    if (push(&historico_operacoes, 3)) {
        printf("  -> Inserido no historico: Multiplicacao\n"); 
    }
    
    printf("\nA pilha esta vazia agora? %s\n", is_empty(historico_operacoes) ? "Sim" : "Nao"); // Deve ser Não

    // 2. Remover operações (POP - Simulação do 'Desfazer')
    printf("\n--- Desfazendo operacoes (POP - LIFO) ---\n");

    // Desfaz a última operação (Multiplicação)
    resultado_pop = pop(&historico_operacoes);
    if (resultado_pop != VALOR_ERRO) {
        printf("  -> Operacao desfeita (removida): Codigo %d\n", resultado_pop); 
    }
    
    // Desfaz a penúltima operação (Subtração)
    resultado_pop = pop(&historico_operacoes);
    if (resultado_pop != VALOR_ERRO) {
        printf("  -> Operacao desfeita (removida): Codigo %d\n", resultado_pop);
    }
    
    // 3. Inserir uma nova operação
    if (push(&historico_operacoes, 4)) {
        printf("\n  -> Inserido no historico: Divisao\n"); // (Novo TOPO)
    }

    // 4. Remover as operações restantes
    printf("\n--- Removendo as operacoes restantes ---\n");
    while (!is_empty(historico_operacoes)) {
        resultado_pop = pop(&historico_operacoes);
        printf("  -> Operacao desfeita (removida): Codigo %d\n", resultado_pop);
    }

    // 5. Testar POP em pilha vazia
    printf("\n--- Tentando desempilhar com a pilha vazia (Teste de Erro) ---\n");
    pop(&historico_operacoes); 
    
    printf("\nA pilha esta vazia apos tudo? %s\n", is_empty(historico_operacoes) ? "Sim" : "Nao"); // Deve ser Sim

    return 0;
}