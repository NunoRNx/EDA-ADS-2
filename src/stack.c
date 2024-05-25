#include "header.h"

#pragma once
/**
 * @brief Verifica existência de vértice na stack
 * 
 * @param v 
 * @param stack 
 * @return true 
 * @return false 
 */
bool checkStack(int v, stacks* stack) {
    stacks* aux = stack;
    while (aux != NULL) {
        if (aux->id == v) {
            return true;
        }
        aux = aux->next;
    }
    return false;
}

/**
 * @brief Print caminho recursivo
 * Como o inicio da stack representa o final do caminho, esta função de escrita de forma recursiva faz print do caminho na ordem correta
 * @param stack inicio da stack
 */
void printPath(stacks* stack) {
    if (stack == NULL) {
        return;
    }
    printPath(stack->next);
    if (stack->next != NULL) {
        printf("->%d", stack->id);
    } else {
        printf("\n%d", stack->id);
    }
}

/**
 * @brief Adicionar vértice atual na stack
 * 
 * @param stack lista que contem os IDs dos vértices do caminho atual
 * @param id ID do vértice
 * @return retorna o nó atual da stack com o novo ID adicionado
 */
stacks* push(stacks* stack, int id) {
    stacks* aux = (stacks*)malloc(sizeof(stacks));
    if (aux == NULL) {
        return NULL;
    }
    aux->id = id;
    aux->next = stack;
    return aux;
}

/**
 * @brief Remover vértice da stack
 * 
 * @param stack lista que contem os IDs dos vértices do caminho atual
 * @return retorna o nó atual da stack com o ID do vértice anterior ao removido
 */
stacks* pop(stacks* stack) {
    if (stack == NULL) {
        return NULL;
    }
    stacks* temp = stack;
    stack = stack->next;
    free(temp);
    return stack;
}

/**
 * @brief Cópia do caminho(stack)
 * 
 * @param ori original, o caminho atual que foi percorrido é copiado para uma nova lista stack que vai ser o caminho de maior custo
 * @param copy inicio da lista da cópia do maior caminho
 * @param cur nó atual a precorrer o caminho original
 * @return copy
 */
stacks* copyPath(stacks* ori) {
    if (ori == NULL) {
        return NULL;
    }
    stacks* copy = NULL;
    stacks* cur = NULL;
    while (ori != NULL) {
        stacks* aux = (stacks*)malloc(sizeof(stacks));
        if (aux == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        aux->id = ori->id;
        aux->next = NULL;
        if (copy == NULL) {
            copy = aux;
            cur = copy;
        } else {
            cur->next = aux;
            cur = cur->next;
        }
        ori = ori->next;
    }
    return copy;
}

/**
 * @brief Apaga um caminho inteiro
 * Utilizada para repor/substituir o caminho de maior valor
 * @param stack inicio da stack a ser apagada
 */
void clearPath(stacks* stack) {
    stacks* aux = stack;
    while (aux != NULL) {
        stacks* temp = aux;
        aux = aux->next;
        free(temp);
    }
}