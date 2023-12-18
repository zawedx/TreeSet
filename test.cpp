#include <iostream>
#include "./treeset.h"
using namespace std;
TreeSet a[10];
int main(){
    for (int i=0; i<10; i++){
        // a[i].insert((templateType){i, 1, i});
        for (int j=0; j<=i; j++){
            a[i].insert((templateType){j, 1, j});
        }
        a[i].display();
    }
    a[4].merge(a[7]);
    a[4].display();
    return 0;
}