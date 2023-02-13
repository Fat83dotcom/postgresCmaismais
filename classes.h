#ifndef CONECPOSTGRES_H
#define CONECPOSTGRES_H

#include <string>
#include <pqxx/pqxx>
#include <iostream>


using namespace pqxx;
using std::cerr;

class conecPostgres{
private:
    char config[200];
    
public:
    conecPostgres(const char *sConfig);
    ~conecPostgres();
    void conne(const char sConfig);
};

conecPostgres::conecPostgres(const char *sConfig){
    strcpy(this->config, sConfig);
}

void conecPostgres::conne(const char sConfig){
    try{
        conecPostgres dB(config);
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    
}

conecPostgres::~conecPostgres(){
    
}


#endif