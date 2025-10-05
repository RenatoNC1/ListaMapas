#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

#define MAX_DESCRICAO 256

// ---------------------------------------------
// 1. ESTRUTURA DO NÓ (TAREFA)
// ---------------------------------------------

typedef struct No {
    int id;                       
    char descricao[MAX_DESCRICAO]; 
    struct No* proximo;           
} No;

// Ponteiro global que aponta para o primeiro nó da lista.
No* cabeca = NULL;

// ---------------------------------------------
// 2. ADICIONAR TAREFA (Inserção no Início)
// ---------------------------------------------

void adicionarTarefa(int novoId, const char *descricao) {
    // 1. Aloca memória no heap para o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    
    // 2. Verifica se a alocação foi bem-sucedida
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória para a nova tarefa.\n");
        return;
    }

    // 3. Atribui os dados: ID e descrição
    novoNo->id = novoId;
    
    // Copia a string de descrição com limite de tamanho (segurança)
    strncpy(novoNo->descricao, descricao, MAX_DESCRICAO - 1);
    // Garante que a string está terminada em nulo, mesmo se truncada
    novoNo->descricao[MAX_DESCRICAO - 1] = '\0'; 

    // 4. Conecta o novo nó à lista:
    novoNo->proximo = cabeca;
    
    // 5. Atualiza a 'cabeca':
    cabeca = novoNo;
    
    printf("[ADD] Adicionada: ID %d - %s\n", novoId, novoNo->descricao);
}

// ---------------------------------------------
// 3. LISTAR TAREFAS (Percurso)
// ---------------------------------------------

void listarTarefas() {
    // Ponteiro auxiliar que começa na cabeça para percorrer a lista
    No* atual = cabeca;
    
    printf("\n--- LISTA DE TAREFAS ---\n");
    
    // Verifica se a lista está vazia
    if (atual == NULL) {
        printf("A lista de tarefas está vazia.\n");
        return;
    }

    // O loop continua enquanto 'atual' não for NULL (o que marca o fim da lista)
    while (atual != NULL) {
        // Imprime os dados do nó atual
        printf("ID: %d | Descrição: %s\n", atual->id, atual->descricao);
        
        // Move o ponteiro 'atual' para o próximo nó
        atual = atual->proximo;
    }
    printf("------------------------\n");
}

// ---------------------------------------------
// 4. EXCLUIR TAREFA (Busca e Remoção)
// ---------------------------------------------

void excluirTarefa(int id) {
    // Ponteiro para o nó que estamos verificando
    No* atual = cabeca;
    // Ponteiro para o nó ANTERIOR ao que estamos verificando (essencial para a exclusão)
    No* anterior = NULL;

    // 1. Busca pelo nó a ser excluído (o loop para quando encontra o ID ou chega ao fim)
    while (atual != NULL && atual->id != id) {
        anterior = atual;         // Guarda o nó atual como o 'anterior'
        atual = atual->proximo;   // Move para o próximo nó
    }

    // 2. Caso 1: Nó não encontrado
    if (atual == NULL) {
        printf("[DEL] Tarefa com ID %d não encontrada.\n", id);
        return;
    }

    // 3. Caso 2: Nó encontrado e é a CABEÇA (primeiro elemento)
    if (anterior == NULL) {
        // A cabeça deve pular para o próximo nó
        cabeca = atual->proximo;
    } 
    // 4. Caso 3: Nó encontrado no meio ou no fim
    else {
        // O nó anterior deve "pular" o nó atual, ligando-se diretamente ao próximo nó
        anterior->proximo = atual->proximo;
    }

    // 5. Liberação da memória
    printf("[DEL] Tarefa com ID %d (\"%s\") excluída com sucesso.\n", id, atual->descricao);
    free(atual); // Libera a memória alocada para o nó excluído
}

// ---------------------------------------------
// 5. LIBERAR MEMÓRIA (Prevenção de Memory Leak)
// ---------------------------------------------

void liberarLista() {
    No* atual = cabeca;
    No* proximoNo; // Variável temporária para guardar o próximo endereço

    // O loop percorre a lista até o fim
    while (atual != NULL) {
        // Guarda o ponteiro do PRÓXIMO nó, pois o nó 'atual' será liberado
        proximoNo = atual->proximo; 
        
        free(atual); // Libera a memória do nó 'atual'
        
        atual = proximoNo; // Move 'atual' para o próximo nó
    }
    cabeca = NULL; // Define a cabeça como NULL para indicar que a lista está vazia
    printf("\n[MEM] Memória da lista liberada com sucesso.\n");
}


// ---------------------------------------------
// 6. FUNÇÃO PRINCIPAL (MAIN)
// ---------------------------------------------

int main() {
    printf("INÍCIO DO PROGRAMA DE GERENCIAMENTO DE TAREFAS\n");

    // Testes de Adição:
    // A ordem na lista será (3 -> 2 -> 1) pois a inserção é no início (HEAD)
    adicionarTarefa(1, "Estudar para a prova de C");
    adicionarTarefa(2, "Fazer compras de mercado");
    adicionarTarefa(3, "Enviar email importante");
    
    // Lista as tarefas
    listarTarefas();

    // Testes de Exclusão:
    excluirTarefa(2); // Excluir no meio
    excluirTarefa(3); // Excluir a cabeça
    excluirTarefa(99); // Excluir tarefa que não existe

    // Lista novamente para ver o resultado da exclusão
    listarTarefas();

    // Adiciona uma nova tarefa
    adicionarTarefa(4, "Revisar o código final");
    listarTarefas();

    // LIMPEZA: Libera toda a memória antes de encerrar
    liberarLista(); 

    return 0; // Termina o programa com sucesso
}