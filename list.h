#ifndef INC_3_2_HASH_MAP_LIST_H
#define INC_3_2_HASH_MAP_LIST_H

template <typename K, typename T>
struct list {
    struct node {
        K key;
        T value;
        node *next;
        node();
        node(K key, T value);
        ~node();
        void update(T value);
    };
    list();
    ~list();
    bool is_empty();
    void push_front(K key, T value);
    void pop_front();
    void clear();
    void erase(node* del);
    node* find(K key);
    node* get_tail();
    int size;
    node* head;
};

//node methods
template <typename K, typename T>
list<K, T>::node::node() : key(K()), value (T()) { this->next = nullptr; }

template <typename K, typename T>
list<K, T>::node::node(K key, T value) : key(key), value(value) { this->next = nullptr; }

template <typename K, typename T>
list<K, T>::node::~node() { next = nullptr; }

template <typename K, typename T>
void list<K, T>::node::update(T value) { this->value = value; }

//list methods
template<typename K, typename T>
list<K, T>::list() : size(0), head(nullptr) {}

template<typename K, typename T>
list<K, T>::~list() { clear(); }

template<typename K, typename T>
bool list<K, T>::is_empty() { return !size; }

template <typename K, typename T>
void list<K,T>::push_front(K key, T value) {
    if (is_empty()) {
        head = new node(key, value);
    }
    else {
        node *curr = head;
        head = new node(key, value);
        head->next = curr;
    }
    size++;
}

template<typename K, typename T>
void list<K, T>::pop_front() {
    node *tmp = head;
    head = head->next;
    delete tmp;
    size--;
}

template<typename K, typename T>
void list<K, T>::clear() {
    while (size) { pop_front(); }
}

template<typename K, typename T>
void list<K, T>::erase(node* del) {
    node *tmp = head;
    if (!is_empty())
    {
        if (tmp != del) {
            while (tmp != nullptr && tmp->next != del) { tmp = tmp->next; }
            tmp->next = del->next;
            delete del;
            size--;
        }
        else {
            pop_front();
        }
    }
}

template<typename K, typename T>
typename list<K, T>::node* list<K,T>::find(K key) {
    node *curr = head;
    while (curr != nullptr && curr->key != key) { curr = curr->next; }
    return curr;
}

template<typename K, typename T>
typename list<K,T>::node* list<K, T>::get_tail() {
    node* curr = head;
    if (curr) {
        while (curr->next != nullptr) { curr = curr->next; }
    }
    return curr;
}
#endif //INC_3_2_HASH_MAP_LIST_H
