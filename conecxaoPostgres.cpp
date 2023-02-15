#include <pqxx/pqxx>
#include <iostream>
#include "classes.h"
#include "confidencial.h"


int main(int argc, char const *argv[]){
    TabelaCliente tb_c;
    ConecPostgres c(DADOSBANCO);
    const string sqlInsert = "INSERT INTO" + tb_c.tabela + tb_c.colunas + 
    "VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10)";
    return 0;
}
