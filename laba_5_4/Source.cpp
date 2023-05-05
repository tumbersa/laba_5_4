//Воспользуйтесь программой из упражнения 5 для вычисления хеш-функции 618033*x % 10000 для ключей,
// которые являются случайными положительными целыми числами, меньшими 10^6.
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

class HashTable
{
    int capacity;
    list<int>* table;

public:
    HashTable(int V);
    void insertItem(int key, int data);
    int hashFunction(int key)
    {
        return (capacity * (key * ((sqrt(5) - 1) / 2) - floor(key * ((sqrt(5) - 1) / 2))));
    }
    int hashFunction2(int key)
    {
        return 618033 * key % 10000;
    } 
    void displayHash();
    int searchHash(int key,int data);
};
HashTable::HashTable(int c)
{
    capacity = c;
    table = new list<int>[c];
}
void HashTable::insertItem(int key, int data)
{
    int index = hashFunction2(key);
    table[index].push_back(data);
}


void HashTable::displayHash()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "table[" << i << "]";
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}
int HashTable::searchHash(int key,int data) {
    int k = 0;
    int index = hashFunction2(key);

    list<int>::iterator i;
    for (i = table[index].begin();
        i != table[index].end(); i++)
    {
        k++;
        if (*i == data)
            break;
    }
    if (i == table[index].end())
        return 0;
    return k;
}
double criterion(int N,int M,int* f) {
    double temp = 0;
    for (int i = 0; i < M; i++) {
        temp += pow(f[i] - (double)N /(double) M, 2);
    }
    return (double)M/(double)N * temp;
}
int main()
{
    srand(time(NULL));
    int n = 10001;
    int* keys = new int[n];
    for (int i = 0; i < n; i++) {
        keys[i] = 1 + rand() % ((int)pow(10, 6) - 1);
    }
    int m = 10000;
    int* data = new int[m];
    for (int i = 0; i < m; i++) {
        data[i] = rand() % 500;//любые случайные данные
    }
    int* f = new int[m];
    for (int i = 0; i < m; i++)
        f[i] = 0;
    HashTable h2(m);
    for (int i = 0; i < n; i++) {
        f[h2.hashFunction2(keys[i])]++;
    }
    double arr[100];
    arr[0] = criterion(n,m,f);
    for (int i = 0; i < m; i++)
        f[i] = 0;
    for (int i = 1; i < 100; i++) {
        for (int i = 0; i < n; i++) {
            keys[i] = 1 + rand() % ((int)pow(10, 6) - 1);
        }
        for (int i = 0; i < n; i++) {
            f[h2.hashFunction2(keys[i])]++;
        }
        arr[i] = criterion(n, m, f);
        for (int i = 0; i < m; i++)
            f[i] = 0;
    }
    for (int i = 0; i < 100; i++)
        cout << arr[i]<<endl;
    double ver=0;
    for (int i = 0; i < 100; i++) {
        if (arr[i]>=m-sqrt(m) && arr[i]<=m+sqrt(m))
        ver ++;
    }
    ver /= 100;
    cout << ver << endl;
    double c = 1 / (1 - ver);//c всегда больше 1
    cout << c << endl;
    if (n > c * m) cout << 1;//при n=10001 c=1 => хеш-функция не является случайной 
    return 0;
}