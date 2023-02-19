#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "confidencial.h"
#include "classes.h"

using std::cout;
using std::vector;

int main(void){
    
    ConectBD c;
    vector<string> b;
    b.push_back("Guduxinho");
    b.push_back("6");

    c.preparaDados("testando", "insert into teste (nome, idade) values ($1, $2)");
    c.executarPreparaInsert("testando", b);

    return 0;
}
