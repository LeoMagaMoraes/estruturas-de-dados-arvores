#pragma once
#include "avl.hpp"

/**
 * @brief Classe que representa um Conjunto (Set) baseado em uma Árvore AVL.
 *
 * Armazena elementos únicos de um tipo T, permitindo operações eficientes de
 * inserção, remoção e busca. A unicidade dos elementos é garantida pela
 * estrutura da Árvore AVL subjacente.
 *
 * @tparam T Tipo dos elementos a serem armazenados no conjunto.
 * O tipo T deve suportar o operadores de '<'.
 */
template <class T>
class Set {
 public:
  /**
   * @brief Construtor padrão.
   * * Cria um conjunto vazio.
   */
  Set();

  /**
   * @brief Insere um elemento no conjunto.
   *
   * Se o elemento já existir no conjunto, a inserção falha e o conjunto
   * não é modificado.
   *
   * @param value O valor a ser inserido.
   * @return `true` se o elemento foi inserido com sucesso (não existia antes),
   * `false` se o elemento já existe no conjunto.
   */
  bool insert(const T& value);

  /**
   * @brief Remove um elemento do conjunto.
   *
   * Se o elemento não for encontrado no conjunto, a remoção falha e o conjunto
   * não é modificado.
   *
   * @param value O valor a ser removido.
   * @return `true` se o elemento foi removido com sucesso,
   * `false` se o elemento não foi encontrado no conjunto.
   */
  bool remove(const T& value);

  /**
   * @brief Verifica se um elemento está contido no conjunto.
   *
   * @param value O valor a ser buscado.
   * @return `true` se o elemento estiver presente no conjunto,
   * `false` caso contrário.
   */
  bool search(const T& value) const;

 private:
  /**
   * @brief A Árvore AVL utilizada para armazenar os dados do conjunto.
   * * A AVL garante a ordenação e o balanceamento, resultando em operações
   * eficientes.
   */
  AVL<T> data;
};

template <class T>
Set<T>::Set() {}

template <class T>
bool Set<T>::insert(const T& value) {}

template <class T>
bool Set<T>::remove(const T& value) {}

template <class T>
bool Set<T>::search(const T& value) const {}