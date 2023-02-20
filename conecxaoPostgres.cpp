#include <pqxx/pqxx>
#include <vector>
#include <iostream>
#include "classes.h"
#include "confidencial.h"

using std::vector;

TabelaTeste tb_t;

void executarTabelaTeste(ConectBD *c, TabelaTeste *tb_t,
    const string &declaracao, const string &sql, vector<string> v){
    for (auto i : v){
        tb_t->campos.push_back(i.c_str());
    }
    c->preparaDados(declaracao, sql);
    c->executarPrepara(declaracao, tb_t->campos);
    tb_t->campos.clear();
}

void mostrarTabelaTeste(ConectBD *c, const string &declaracao, vector<string> v){
    c->imprimirPreparaResult(declaracao, v);
}

int main(void){
    ConectBD c;
    vector<string> inserir, buscar, deletar;

    inserir = {"Fernando", "40"};
    executarTabelaTeste(&c, &tb_t, "inserirTTeste", tb_t.sqlInsertTTeste, inserir);

    buscar = {};
    executarTabelaTeste(&c, &tb_t, "selectAll", tb_t.sqlSelectTTestAll, buscar);
    mostrarTabelaTeste(&c, "selectAll", buscar);

    buscar = {"20"};
    executarTabelaTeste(&c, &tb_t, "selectId", tb_t.sqlSelectTTestId, buscar);
    mostrarTabelaTeste(&c, "selectId", buscar);

    buscar = {"Fernando"};
    executarTabelaTeste(&c, &tb_t, "selectNome", tb_t.sqltSelectTTestNome, buscar);
    mostrarTabelaTeste(&c, "selectNome", buscar);

    buscar = {"5"};
    executarTabelaTeste(&c, &tb_t, "selectIdade", tb_t.sqltSelectTTestIdade, buscar);
    mostrarTabelaTeste(&c, "selectIdade", buscar);

    deletar = {"13"};
    buscar = {};
    executarTabelaTeste(&c, &tb_t, "deleteId", tb_t.sqlDeleteTTestId, deletar);
    mostrarTabelaTeste(&c, "selectAll", buscar);

    return 0;
}
