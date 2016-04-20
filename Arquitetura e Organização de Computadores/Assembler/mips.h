#ifndef MIPS_H
#define MIPS_H

#include "mips_definitions.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

class mips
{
    public:
        //Atributos
        int RegFile[N_REG];//Banco de registradores
        int *DataMem;//Memória de dados
        unsigned int *InsMem;//Memória de instrução
        unsigned int pc;
        unsigned int num_ins;

        //Métodos
        unsigned int string_to_hex(string);
        void init_Reg(void);
        void alloc_InsMem(string);
        void alloc_DataMem(void);
        void load_InsMem(string);
        void load_DataMem(string);
        int get_DataMem(unsigned int);
        void set_DataMem(unsigned int,int);
        void start_simulation(void);

        unsigned int get_instruction(unsigned int);
        mips_instruction decode_instruction(mips_instruction);
        unsigned int execute(mips_instruction);

        void reg_output(void);
        void data_output(unsigned int);

        mips();
        ~mips();
};

#endif // MIPS_H
