#include "mips.h"
using namespace std;

int main()
{
    mips simulador;

    //Inicia todos os registradores com seus valores padr�es.
    simulador.init_Reg();

    //Carrega o programa(em hexadecimal) para a mem�ria de instru��o.
    simulador.load_InsMem("rom.hex");

    //Carrega os dados (se houver) para a mem�ria de dados.
    simulador.load_DataMem("ram.hex");

    //Busca, decodifica e executa.
    simulador.start_simulation();

    //Imprime na tela o valor dos registradores ap�s a execu��o da simula��o.
    //simulador.reg_output();

    //Imprime na tela o valor da mem�ria ap�s a execu��o da simula��o.
    simulador.data_output(16);
    return 0;
}


