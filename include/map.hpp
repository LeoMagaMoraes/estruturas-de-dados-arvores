#pragma once
#include "bst.hpp"

/**
 * @brief Classe que representa um Mapa Associativo (Map).
 *
 * Armazena pares chave-valor, onde cada chave é única. A ordenação e
 * busca são garantidas pelo uso de uma Árvore Binária.
 *
 * @tparam K Tipo da chave. Deve suportar o operadores de comparação '<'.
 * @tparam V Tipo do valor associado à chave.
 */
template <class K, class V>
class Map {
 private:
  /**
   * @brief Estrutura interna para armazenar o par chave-valor.
   * A Árvore Binária interna (`data`) armazenará objetos deste tipo.
   */
  struct Pair {
    K key;    ///< A chave única.
    V value;  ///< Ponteiro para o valor. O Map gerenciará a memória deste
              ///< valor.

    /**
     * @brief Construtor do Pair com uma chave.
     * @param k A chave.
     */
    explicit Pair(const K& k) : key(k), value() {}

    /**
     * @brief Operador de comparação 'menor que'.
     * Essencial para a ordenação dos Pares dentro da Árvore Binária.
     * **Importante:** Esta comparação DEVE ser baseada apenas na `key`
     * para que o mapa funcione corretamente.
     *
     * @param other O outro Pair para comparar.
     * @return `true` se este Pair for considerado menor que `other` (baseado na
     * chave), `false` caso contrário.
     */
    bool operator<(const Pair& other) const {
      // Implementação crucial: deve comparar APENAS as chaves.
      return key > other.key;
    }
  };

 public:
  /**
   * @brief Construtor padrão.
   * Cria um mapa vazio.
   */
  Map();

  /**
   * @brief Acessa o valor associado a uma chave.
   *
   * Se a chave `key` não existir no mapa, um novo par chave-valor é inserido.
   * O valor para a nova chave será inicializado usando o construtor padrão de
   * `V`.
   *
   * @param key A chave para buscar ou inserir.
   * @return Uma referência ao valor associado à chave.
   */
  V& operator[](const K& key);

  /**
   * @brief Acessa o valor associado a uma chave (versão constante).
   *
   * Se a chave não for encontrada deve lançar uma exceção `std::out_of_range`.
   *
   * @param key A chave para buscar.
   * @return Uma referência constante ao valor associado à chave.
   * @throw std::out_of_range se a chave não for encontrada.
   */
  const V& operator[](const K& key) const;

  /**
   * @brief Remove um par chave-valor do mapa.
   *
   * Se a chave existir, o par é removido.
   *
   * @param key A chave do elemento a ser removido.
   * @return `true` se o elemento foi encontrado e removido, `false` caso
   * contrário.
   */
  bool remove(const K& key);

 private:
  BST<Pair> data;  ///< A Árvore Binária que armazena os pares chave-valor.
};

template <class K, class V>
Map<K, V>::Map() {}

template <class K, class V>
V& Map<K, V>::operator[](const K& key) {}

template <class K, class V>
const V& Map<K, V>::operator[](const K& key) const {}

template <class K, class V>
bool Map<K, V>::remove(const K& key) {}