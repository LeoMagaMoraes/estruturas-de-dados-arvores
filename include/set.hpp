#pragma once
#include "avl.hpp"

/**
 * @brief Classe Set que representa um conjunto de elementos únicos usando uma Árvore AVL.
 * 
 * Permite inserção, remoção e busca de elementos com complexidade O(log n).
 * Elementos duplicados não são inseridos.
 * 
 * @tparam T Tipo dos elementos armazenados no conjunto. Deve suportar operador '<'.
 */
template <class T>
class Set {
public:
  Set() = default;

  // Insere um elemento no conjunto. Retorna true se inserido, false se já existe.
  bool insert(const T& value) {
    if (data.contain(value))
      return false;
    return data.insert(value);
  }

  // Remove um elemento do conjunto. Retorna true se removido, false se não existe.
  bool remove(const T& value) {
    if (!data.contain(value))
      return false;
    return data.remove(value);
  }

  // Verifica se o conjunto contém o elemento.
  bool search(const T& value) const {
    return data.contain(value);
  }

private:
  AVL<T> data;  // Árvore AVL que armazena os elementos
};
