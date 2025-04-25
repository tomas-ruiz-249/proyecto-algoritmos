#include <iostream>
#include <string>
#include "hashmap.h"

using namespace std;

int main(){
    HashMap<string, int> h;
    for(int i = 0; i < 100; i++){
        h.insert(to_string(i * 2), i);
        h.print();
    }
    return 0;
}