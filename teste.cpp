#include <iostream>
# include <pqxx/pqxx>
#include <chrono>
#include "confidencial.h"

using std::cerr;
using std::string;
using std::cout;
using std::cin;
using std::stringstream;
using std::getline;
using std::endl;

int main(void){
    string nome, idade;
    int idadeInt;
    try{
        pqxx::connection c(DADOSBANCO);
        if (c.is_open()){
            cout << "Banco conectado com sucesso" << endl;
        }
        else{
            cout << "Banco não conectado" << endl;
            return -1;
        }
        
        c.prepare("insertDados", "INSERT INTO teste (nome, idade) values ($1, $2)");
        pqxx::work objT(c);
        cout << "Entre com 3 registros nome e idade:" << endl;
        for (int i = 0; i < 3; i++){
            cout << "Digite um nome: ";
            getline(cin, nome);
            cout <<"Digite a idade: ";
            getline(cin, idade);
            int j = 0;
            bool numero;
            while (idade[j]){
                if (!isalpha(idade[j])){
                    numero = true;
                }
                else{
                    numero = false;
                    break;
                }
                j++;
            }
            if (numero){
                stringstream(idade) >> idadeInt;
                objT.exec_prepared("insertDados", nome, idadeInt);
                // objT.commit();
                cout << "dado inserido com sucesso" << endl;
            }
            else{
                cout << "A idade não é um número." << endl;
                cout << "O dado não foi inserido." << endl;
            }
        }

        pqxx::result consulta = objT.exec("SELECT * FROM teste");
        cout << "Id      Nome    Idade" << endl;
        for (const auto &row: consulta){
            for (const auto &field: row){
                cout << field.c_str() << "   ";
            } 
            cout << endl;
        }

        // const int num_rows = consulta.size();
        // for (int rownum=0; rownum < num_rows; ++rownum){
        //     const pqxx::row row = consulta[rownum];
        //     const int num_cols = row.size();
        //     for (int colnum=0; colnum < num_cols; ++colnum){
        //         const pqxx::field field = row[colnum];
        //         cout << field.c_str() << '\t';
        //     }
        //     cout << std::endl;
        // }

        objT.commit();
        // c.disconnect();
    }
    catch(const std::exception& e){
        cerr << e.what() << '\n';
    }
    
    return 0;
}
