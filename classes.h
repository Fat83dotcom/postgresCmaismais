#ifndef CONECPOSTGRES_H
#define CONECPOSTGRES_H

#include <string>
#include <pqxx/pqxx>
#include <pqxx/pqxx>
#include <pqxx/transaction_base>
#include <iostream>
#include <vector>
#include "confidencial.h"


using std::cerr;
using std::string;
using std::vector;

typedef struct TabelaTeste{
    const string tabela = "teste";
    const string colunas = "nome, idade";
    vector<string> campos;
    // string nome;
    // string idade;
}TabelaTeste;

typedef struct TabelaCliente{
    const string tabela = "cliente";
    const string colunas = "nome_cliente, cpf_cliente, "
    "data_nasc, endereco_rua, endereco_numero, endereco_bairro, "
    "enderco_cep, endereco_estado, endereco_cidade";
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


// class ObjetosBd{
// public:
//     virtual void preparaDados(const string &nomePrepara, const string &sql) = 0;
//     virtual void executarPreparaInsert(const string &nomeprepara, ...) = 0;
// };


class ConectBD {
private:
    pqxx::connection con;

public:
    ConectBD() : con(DADOSBANCO) {}
    // void ConectBD::preparaDados(const string &nomePrepara, const string &sql);

    // void ConectBD::executarPreparaInsert(const string &nomeprepara, ...);

    void preparaDados(const string &nomePrepara, const string &sql){
        try{
            this->con.prepare(nomePrepara, sql);
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }

    void executarPreparaInsert(const string &nomeprepara, const vector<string> &args){
        try{
            pqxx::params argumentos;
            for (const auto &arg : args){
                argumentos.append(arg);
            }
            
            pqxx::work w(this->con);
            w.exec_prepared(nomeprepara, argumentos);
            w.commit();
            
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
};

#endif