#pragma once
#include "bst.hpp"
#include <stdexcept>

/**
 * @brief Implementação de um mapa associativo (map/dicionário)
 *        usando uma árvore binária de busca (BST).
 *
 * Cada chave é única e associada a um valor.
 *
 * @tparam K Tipo da chave. Deve suportar operador <.
 * @tparam V Tipo do valor.
 */
template <class K, class V>
class Map {
private:
  struct Pair {
    K key;
    V value;

    explicit Pair(const K& k) : key(k), value() {}
    Pair(const K& k, const V& v) : key(k), value(v) {}

    bool operator<(const Pair& other) const { return key < other.key; }
    bool operator==(const Pair& other) const { return key == other.key; }
  };

public:
  Map() = default;

  // Acesso/modificação: insere valor default se chave não existir
  V& operator[](const K& key) {
    Pair p(key);
    auto node = data.find_node(p);
    if (!node) {
      data.insert(p);
      node = data.find_node(p);  // Buscar após inserção para pegar o nó atualizado
    }
    return node->data.value;
  }

  // Acesso constante: lança exceção se chave não existe
  const V& operator[](const K& key) const {
    Pair p(key);
    auto node = data.find_node(p);
    if (!node) {
      throw std::out_of_range("Key not found in Map");
    }
    return node->data.value;
  }

  // Remove par pela chave, retorna sucesso/falha
  bool remove(const K& key) {
    return data.remove(Pair(key));
  }

private:
  BST<Pair> data;
};
