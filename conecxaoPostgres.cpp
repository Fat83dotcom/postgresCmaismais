#include <pqxx/pqxx>
#include <vector>
#include <iostream>
#include "classes.h"
#include "confidencial.h"

using std::vector;

int main(int argc, char const *argv[]){
    TabelaTeste tb_t;
    ConectBD c;
    tb_t.campos.push_back("Gudulinhosidade");
    tb_t.campos.push_back("5");
    const string sqlInsertTTeste = "INSERT INTO " + tb_t.tabela + " (" + tb_t.colunas + ") " + 
    " VALUES($1, $2)";
    c.preparaDados("tabelaTeste", sqlInsertTTeste);
    c.executarPreparaInsert("tabelaTeste", tb_t.campos);
    return 0;
}
