#include "mips.h"
using namespace std;

int main()
{
    mips simulador;

    //Inicia todos os registradores com seus valores padrões.
    simulador.init_Reg();

    //Carrega o programa(em hexadecimal) para a memória de instrução.
    simulador.load_InsMem("rom.hex");

    //Carrega os dados (se houver) para a memória de dados.
    simulador.load_DataMem("ram.hex");

    //Busca, decodifica e executa.
    simulador.start_simulation();

    //Imprime na tela o valor dos registradores após a execução da simulação.
    //simulador.reg_output();

    //Imprime na tela o valor da memória após a execução da simulação.
    simulador.data_output(16);
    return 0;
}


