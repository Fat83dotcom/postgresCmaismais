#ifndef CONECPOSTGRES_H
#define CONECPOSTGRES_H

#include <string>
#include <pqxx/pqxx>
#include <iostream>


using namespace pqxx;
using std::cerr;
using std::string;

typedef struct TabelaCliente{
    string nome_cliente;
    string cpf_cliente;
    string data_nasc;
    string endereco_rua;
    string endereco_numero;
    string endereco_bairro;
    string endereco_cep;
    string endereco_estado;
    string endereco_cidade;
}TabelaCliente;


class ObjetosBd{
public:
    virtual void insertDados() = 0;
};


class ConecPostgres : public ObjetosBd{
private:
    string config;
    string sqlInsert;
    
public:
    ConecPostgres(const string &sConfig);
    string ConecPostgres::recebeSqlInsert(const string &sql);
    
    ConecPostgres::ConecPostgres(const string &sConfig){
        try{
            this->config = sConfig;
        }
        catch(const std::exception &e){
            std::cerr << e.what() << '\n';
        }
    }

    string ConecPostgres::recebeSqlInsert(const string &sql){
        this->sqlInsert = sql;
    }

    void ConecPostgres::insertDados() override{
        try{
            pqxx::connection conn(this->config);
            pqxx::work txn(conn);
            txn.exec0(sqlInsert);
            txn.commit();
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
};

#endif