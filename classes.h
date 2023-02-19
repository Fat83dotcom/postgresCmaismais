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
using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef struct TabelaTeste{
    const string sqlInsertTTeste = "INSERT INTO teste (nome, idade) VALUES($1, $2)";
    const string sqlSelectTTest = "SELECT * FROM teste";
    vector<string> campos;
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

class ConectBD {
private:
    pqxx::connection con;

public:
    ConectBD() : con(DADOSBANCO) {}

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
            
            pqxx::work w(this->con);
            pqxx::params argumentos;
            for (const auto &arg : args){
                argumentos.append(arg);
                cout << arg << endl;
            }
            // cout << argumentos << endl;
            w.exec_prepared(nomeprepara, argumentos);
            w.commit();
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }

    void imprimirPreparaResult(const string &nomeprepara, const vector<string> &args){
        try{
            pqxx::result r;
            pqxx::work w(this->con);
            if (args.size() == 0) {
                r = w.exec_prepared(nomeprepara);
            }
            else{
                pqxx::params argumentos;
                for (const auto &arg : args){
                    argumentos.append(arg);
                }
                r = w.exec_prepared(nomeprepara, argumentos);
            }
            cout << "Id      Nome    Idade" << endl;
            for (const auto &row: r){
                for (const auto &field: row){
                    cout << field.c_str() << "   ";
                } 
                cout << endl;
            }
            w.commit();
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
};

#endif