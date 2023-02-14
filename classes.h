#ifndef CONECPOSTGRES_H
#define CONECPOSTGRES_H

#include <string>
#include <pqxx/pqxx>
#include <iostream>


using namespace pqxx;
using std::cerr;
using std::string;

class ObjetosBd{
public:
    virtual void insertDados() = 0;
};


class ConecPostgres : public ObjetosBd{
private:
    string config;
    
public:
    ConecPostgres(const string &sConfig);
    
    ConecPostgres::ConecPostgres(const string &sConfig){
        try{
            this->config = sConfig;
        }
        catch(const std::exception &e){
            std::cerr << e.what() << '\n';
        }
    }

    void ConecPostgres::insertDados() override{
        try{
            pqxx::connection conn(this->config);
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
};

#endif