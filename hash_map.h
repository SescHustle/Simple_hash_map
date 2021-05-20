#ifndef INC_3_2_HASH_MAP_HASH_MAP_H
#define INC_3_2_HASH_MAP_HASH_MAP_H
#include "list.h"

template <typename K, typename T>
class hash_map {
private:
    int step = 10;
    int mapsize;
    int count;
    const int maxlistsize = 5;
    list<K, T> *lists;
public:
    class iterator
    {
        list<K, T>* lists;
        typename list<K, T>::node* node;
        int last_index;
        int index;
    public:
        iterator(list<K, T>* lists, typename list<K, T>::node* node, int index, int last_index);
        iterator & operator++();
        bool check_final_item(int ind);
        bool operator!=(iterator it);
        list<K, T> & operator *();
        typename list<K, T>::node* operator ->();
    };

    explicit hash_map(int size);
    ~hash_map();
    int get_hash(K key);
    typename list<K, T>::node* find(K key);
    void add(K key, T value);
    void remove(K key);
    void rehash();
    bool is_need_rehash();
    int unique_count();
    int get_count();
    iterator begin () const;
    iterator end () const;
};

//iterator methods
template <typename K, typename T>
hash_map<K, T>::iterator::iterator(list<K, T> *lists, typename list<K, T>::node *node, int index, int last_index) :
        lists(lists), node(node), index(index), last_index(last_index) {}

template <typename K, typename T>
typename hash_map<K, T>::iterator & hash_map<K, T>::iterator::operator++() {
    if (node->next != nullptr || check_final_item(index)) {
        node = node->next;
        return *this;
    } else {
        for (++index; index < last_index; index++) {
            if (lists[index].head != nullptr) {
                node = lists[index].head;
                return *this;
            }
        }
    }
    return *this;
}

template<typename K, typename T>
bool hash_map<K, T>::iterator::check_final_item(int ind) {
    for (int i = last_index - 1; i >= 0; i--) {
        if (lists[i].get_tail() != NULL) {
            if (ind == i) { return true; }
            return false;
        }
    }
}

template<typename K, typename T>
bool hash_map<K, T>::iterator::operator!=(iterator it) {
    if (node == it.node) { return false; }
    return true;
}

template<typename K, typename T>
list<K, T> & hash_map<K, T>::iterator::operator*() { return lists[index]; }

template<typename K, typename T>
typename list<K, T>::node* hash_map<K, T>::iterator::operator->() { return node; }


//hash_map methods
template<typename K, typename T>
hash_map<K, T>::hash_map(int size) : mapsize(size), count(0) { this->lists = new list<K, T> [mapsize]; }

template<typename K, typename T>
hash_map<K, T>::~hash_map() { delete[] this->lists; }

template<typename K, typename T>
int hash_map<K, T>::get_hash(K key) {
    std::hash<K> simple_hash;
    return abs((int)simple_hash(key)) % mapsize;
}

template<typename K, typename T>
typename list<K, T>::node* hash_map<K, T>::find(K key) {
    return lists[get_hash(key)].find(key);
}

template<typename K, typename T>
void hash_map<K, T>::add(K key, T value) {
    int i = get_hash(key);
    typename list<K, T>::node* check = lists[i].find(key);
    if (check == nullptr) {
        lists[i].push_front(key, value);
        count++;
    }else{
        check->update(value);
    }
    if (is_need_rehash()) { rehash(); }
}

template<typename K, typename T>
void hash_map<K, T>::remove(K key) {
    typename list<K, T>::node* toErase = find(key);
    if (find(key) != NULL) {
        lists[get_hash(key)].erase(toErase);
        count--;
    }
}

template<typename K, typename T>
void hash_map<K, T>::rehash() {
    int n = mapsize;
    mapsize *= step;
    int count_tmp = count;
    auto* tmp = new list<K, T>[mapsize];
    for (int i = 0; i < n; i++) {
        while (lists[i].head != nullptr) {
            int hash = get_hash(lists[i].head->key);
            tmp[hash].push_front(lists[i].head->key, lists[i].head->value);
            lists[i].pop_front();
        }
    }
    delete[] lists;
    count = count_tmp;
    lists = tmp;
}

template<typename K, typename T>
bool hash_map<K, T>::is_need_rehash() {
    for (int i = 0; i < mapsize; i++) {
        if (lists[i].size > maxlistsize) { return true; }
    }
    return false;
}

template<typename K, typename T>
int hash_map<K, T>::unique_count() {
    int unique = 0;
    auto it = begin();
    for (it; it != end(); ++it) {
        auto ij = it;
        ++ij;
        bool check = true;
        for (ij; ij != end(); ++ij) {
            if (it->value == ij->value) { check = false; }
        }
        unique += check;
    }
    return unique;
}

template<typename K, typename T>
int hash_map<K, T>::get_count() { return count; }

template<typename K, typename T>
typename hash_map<K, T>::iterator hash_map<K, T>::begin() const {
    for (int i = 0; i < mapsize; i++) {
        if (lists[i].head != nullptr) {
            return iterator(lists, lists[i].head, i, mapsize);
        }
    }
    return iterator(NULL, NULL, 0, mapsize);
}

template<typename K, typename T>
typename hash_map<K, T>::iterator hash_map<K, T>::end() const {
    for (int i = mapsize - 1; i >= 0; i--) {
        if (lists[i].head != nullptr) {
            return iterator(lists, lists[i].get_tail()->next, i, mapsize);
        }
    }
    return iterator(NULL, NULL, 0, mapsize);
}

#endif //INC_3_2_HASH_MAP_HASH_MAP_H
