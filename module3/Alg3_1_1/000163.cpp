#include <iostream>
#include <vector>
#include <iostream>

#define EMPTY -1
#define DELETED -2
#define USED -3

#define TABLE_DEFAULT_SIZE 8


using namespace std;

//Храню в хеш-таблице пары состояние-значение
struct HashTableNode {
    int state;
    string data;

    HashTableNode() : state(EMPTY) { }
};

size_t Hash(const string &key) {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); i++) {
        hash = (hash * 127 + key[i]);
    }
    return hash;
}

class HashTable {
private:
    vector<HashTableNode> table;
    int keyAmount;

    void AddUnique(const string &key);

    void grow();

public:
    HashTable();

    bool Has(const string &key) const;

    bool Add(const string &key);

    bool Remove(const string &key);

};

HashTable::HashTable() : keyAmount(0) {
    table.resize(TABLE_DEFAULT_SIZE);
}

bool HashTable::Has(const string &key) const {
    size_t hash = Hash(key);

    for (size_t prob = 0; prob < table.size(); ++prob) {
        hash = (hash + prob + 1) % table.size();

        if (table[hash].state == USED) {
            if (table[hash].data == key) {
                return true;
            }
        } else if (table[hash].state == EMPTY) {
            return false;
        }
    }
    return false;
}

bool HashTable::Add(const string &key) {

    if (Has(key))
        return false;

    if (keyAmount >= 0.75 * table.size()) {
        grow();
    }

    size_t hash = Hash(key);
    for (size_t prob = 0; prob < table.size(); ++prob) {
        hash = (hash + prob + 1) % table.size();
        if (table[hash].state != USED) {
            table[hash].state = USED;
            table[hash].data = key;
            keyAmount++;
            return true;
        }
    }
    return false;
}

//Функция добавления когда точно известно что ключи уникальны
void HashTable::AddUnique(const string &key) {

    size_t hash = Hash(key);
    for (size_t prob = 0; prob < table.size(); ++prob) {
        hash = (hash + prob + 1) % table.size();
        if (table[hash].state != USED) {
            table[hash].state = USED;
            table[hash].data = key;
            break;
        }
    }
}


bool HashTable::Remove(const string &key) {

    size_t hash = Hash(key);

    for (size_t prob = 0; prob < table.size(); ++prob) {
        hash = (hash + prob + 1) % table.size();
        if (table[hash].state == USED) {
            if (table[hash].data == key) {
                table[hash].state = DELETED;
                keyAmount--;
                return true;
            }
        } else if (table[hash].state == EMPTY)
            return false;
    }
    return false;
}

//Во время раcширения таблицы пользуемся более быстрой функцией добавления уникальных элементов
void HashTable::grow() {
    vector<HashTableNode> tmp(table.size() * 2);
    std::swap(table, tmp);
    for (vector<HashTableNode>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        if (it->state == USED) {
            AddUnique(it->data);
        }
    }
}

int main() {

    HashTable t;
    char op = 0;
    string str;
    bool result = false;
    while (cin >> op >> str) {
        switch (op) {
            case '+':
                result = t.Add(str);
                break;
            case '?':
                result = t.Has(str);
                break;
            case '-':
                result = t.Remove(str);
                break;
            default:
                break;
        }
        if (result == true) {
            cout << "OK" << endl;
        } else if (result == false) {
            cout << "FAIL" << endl;
        }
    }
    return 0;
}
