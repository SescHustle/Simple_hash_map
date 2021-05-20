#include<string>
#include<iostream>
#include<fstream>
#include "hash_map.h"

template<typename K, typename T>
void work_function(K key, T value, std::ifstream& fin, std::ofstream & fout, int n){
    hash_map<K, T> hashmap(n);
    for (int i = 0; i < n; i++) {
        std::string tmp;
        fin >> tmp;
        if (tmp[0] == 'A') {
            fin >> key;
            fin >> value;
            hashmap.add(key, value);
        } else {
            if (tmp[0] == 'R') {
                fin >> key;
                hashmap.remove(key);
            }
        }
    }
    fout << hashmap.get_count() << " " << hashmap.unique_count();
}


template<typename K>
void read_value(K key, char value, std::ifstream& fin, std::ofstream & fout, int n) {
    switch (value) {
        case ('I'):
        {
            int tmp = 0;
            work_function(key, tmp, fin, fout, n);
            break;
        }
        case('D'):
        {
            double tmp = 0;
            work_function(key, tmp, fin, fout, n);
            break;
        }
        case('S'):
        {
            std::string tmp = "";
            work_function(key, tmp, fin, fout, n);
            break;
        }
    }
}


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    std::string tmp;
    std::getline(fin, tmp);
    char data_types[2] = {'\0' };
    data_types[0] = tmp[0];
    data_types[1] = tmp[2];
    fin >> n;
    getline(fin, tmp);

    switch (data_types[0])
    {
        case ('I'):
        {
            int tmp_key = 0;
            read_value(tmp_key, data_types[1], fin, fout, n);
            break;
        }
        case('D'):
        {
            double tmp_key = 0;
            read_value(tmp_key, data_types[1], fin, fout, n);
            break;
        }
        case('S'):
        {
            std::string tmp_key = "";
            read_value(tmp_key, data_types[1], fin, fout, n);
            break;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
