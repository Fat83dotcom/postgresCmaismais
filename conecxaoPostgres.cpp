#include <pqxx/pqxx>
#include <vector>
#include <iostream>
#include "classes.h"
#include "confidencial.h"

using std::vector;

int main(void){
    TabelaTeste tb_t;
    ConectBD c;
    tb_t.campos.push_back("guduxinha");
    tb_t.campos.push_back("6");
    
    c.preparaDados("tabelaTesteInsert", tb_t.sqlInsertTTeste);
    c.executarPreparaInsert("tabelaTesteInsert", tb_t.campos);
    tb_t.campos.clear();
   
    c.preparaDados("tabelaTesteSelect", tb_t.sqlSelectTTest);
    c.imprimirPreparaResult("tabelaTesteSelect", tb_t.campos);

    return 0;
}
