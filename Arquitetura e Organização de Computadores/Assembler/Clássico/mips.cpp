#include "mips.h"

mips::mips()
{
    //Inicia todos os registradores com seus valores padrões.
    //this->init_Reg();

    //Carrega o programa(em hexadecimal) para a memória de instrução.
    //this->load_InsMem("rom.hex");

    //Carrega os dados (se houver) para a memória de dados.
    //this->load_DataMem("ram.hex");

    //Busca, decodifica e executa.
    //this->start_simulation();

    //Imprime na tela o valor dos registradores após a execução da simulação.
    //this->reg_output();

    //Imprime na tela o valor da memória após a execução da simulação.
    //this->data_output(20);
}

mips::~mips()
{
    //Libera o espaço de memória alocado
    free(DataMem);
    free(InsMem);
    this->DataMem = NULL;
    this->InsMem = NULL;
    printf("\n BYE\n");
}

unsigned int mips::string_to_hex(string line){
    unsigned int ins_hex=0;
    std::stringstream str;
    str << line;
    str >> std::hex >> ins_hex;
    return ins_hex;
}

int mips::get_DataMem(unsigned int addr){
    /*
    * No MIPS os endereçoes de memória possuem os 16 bits
    * mais significativos com o valor 0x1001
    * porém precisamos neste caso, por ser um simulador simplificado,
    * apenas dos 16 bits menos significativos com o valor do deslocamento.
    */
    addr = addr -0x10010000 ;

    /*
     * Este simulador manipula o conteúdo da memória de 4 em 4 bytes e
     * não em bytes separados, por este motivo, é necessário dividir o
     * endereço recebido por 4.
     */
    return this->DataMem[addr/4];
}

void mips::set_DataMem(unsigned int addr,int value){
    addr = addr -0x10010000;
    this->DataMem[addr/4]=value;
}

void mips::init_Reg(){
    int i;

    //Valor inicial do PC.
    this->pc=0x00400000;

    for (i = 0; i < N_REG; i++){
        //Inicia todos os registradores em 0.
        this->RegFile[i] = 0x0;
    }
}

void mips::alloc_InsMem(string url){
    unsigned int size=0;
    string line;
    ifstream myfile(url.c_str());

    //Conta a quantidade de instruções e aloca apenas a quantidade de memória necessária.
    for (size = 0; std::getline(myfile, line); ++size);

    myfile.close();

    //Armazena a quantidade de instruções.
    this->num_ins= size;

    this->InsMem  = (unsigned int *)malloc(size * sizeof(int));
    //Se a não houver memória disponível fecha o programa.
    if (this->InsMem == NULL) {
        exit(1);
    }else{
        //Inicializa todas as posições de memória.
        unsigned int i=0;
        for (i = 0; i < size; i++) {
            this->InsMem[i] = 0;
        }
    }
}

void mips::alloc_DataMem(){
    this->DataMem  = (int *)malloc(DATA_MEM_SIZE * sizeof(int));
    //Se a não houver memória disponível fecha o programa
    if (this->DataMem == NULL) {
        exit(1);
    }else{
        //Inicializa todas as posições de memória.
        unsigned int i=0;
        for (i = 0; i < DATA_MEM_SIZE; i++) {
            this->DataMem[i]= 0;
        }
    }
}

void mips::load_InsMem(string url){
    unsigned int i=0;
    string line;
    ifstream myfile(url.c_str());

    //Aloca espaço de memória para as instruções(ROM).
    this->alloc_InsMem(url);

    if (myfile.is_open())
    {
        while ( myfile.good() && i<this->num_ins)
        {
            getline (myfile,line);

            //Transforma uma string em um hexadecial.
            this->InsMem[i]=this->string_to_hex(line);
            //printf("InsMem[%d]		0x%08x\n",i, InsMem[i]);
            i++;
        }
        myfile.close();
    }
}

void mips::load_DataMem(string url){
    int i=0;
    string line;
    ifstream myfile(url.c_str());

    //Aloca espaço de memoria para os dados(RAM).
    this->alloc_DataMem();

    if (myfile.is_open())
    {
        while ( myfile.good()&& i<DATA_MEM_SIZE)
        {
            getline (myfile,line);
            //Transforma uma string em um hexadecial.
            this->DataMem[i] =this->string_to_hex(line);
            // printf("DataMem[%d]		0x%08x\n",i, DataMem[i]);
            i++;
        }
        myfile.close();
    }
}

void mips::start_simulation(){
    mips_instruction mips_ins;
    unsigned int next_pc= this->pc;

    while (((next_pc-0x00400000)/4) != this->num_ins){
        this->pc = next_pc;

        //Busca instrução
        mips_ins.ins = this->get_instruction(this->pc);

        //Decodifica
        mips_ins = this->decode_instruction(mips_ins);

        //Executa
        next_pc= this->execute(mips_ins);

        printf("-----------------------------------\n");
        printf("Ins                     0x%08x\n",mips_ins.ins);
        this->reg_output();
        //printf("next pc		        0x%08x\n\n", next_pc);
        //this->data_output(16);
        getchar();
    }
}

unsigned int mips::get_instruction(unsigned int pc){
    return this->InsMem[((pc-0x00400000)/4)];
}

mips_instruction mips::decode_instruction(mips_instruction mips_ins){

    /*
     * R-format
     *|--------------------------------------------------------|
     *|  OP   |    RS   |    RT   |    RD   |  SHAMT  | FUNCT  |
     *|-------|---------|---------|---------|---------|--------|
     *|6 bits |  5 bits |  5 bits |  5 bits |  5 bits | 6 bits |
     *|--------------------------------------------------------|
     *
     * I-format
     *|--------------------------------------------------------|
     *|  OP   |    RS   |    RT   |          IMMEDIATE         |
     *|-------|---------|---------|----------------------------|
     *|6 bits |  5 bits |  5 bits |           16 bits          |
     *|--------------------------------------------------------|
     *
     * J-format
     *|--------------------------------------------------------|
     *|  OP   |                    IMMEDIATE                   |
     *|-------|------------------------------------------------|
     *|6 bits |                     26 bits                    |
     *|--------------------------------------------------------|
     */
	 
	// não implementado ainda
	mips_ins.op_code = (mips_ins.ins >> OP_OFFSET) & MASK_6;
	mips_ins.rs = (mips_ins.ins >> RS_OFFSET) & MASK_5;
	mips_ins.rt = (mips_ins.ins >> RT_OFFSET) & MASK_5;
	mips_ins.rd = (mips_ins.ins >> RD_OFFSET) & MASK_5;
	mips_ins.shamt = (mips_ins.ins >> SHAMT_OFFSET) & MASK_5;
	mips_ins.funct = mips_ins.ins & MASK_6;

	mips_ins.immediate_16bits = mips_ins.ins & MASK_16;
	mips_ins.immediate_26bits = mips_ins.ins & MASK_26;

    return mips_ins;
}

unsigned int mips::execute(mips_instruction mips_ins){
    //if NOP
    if (mips_ins.ins==0) {
        return this->pc+4;
    }
	
    //R-format
    if (mips_ins.op_code == RTYPEOP) {
        switch (mips_ins.funct) {
        case ADD:
			printf("add %d, %d, %d\n", mips_ins.rd, mips_ins.rs, mips_ins.rt);
			RegFile[mips_ins.rd] = RegFile[mips_ins.rs] + RegFile[mips_ins.rt];
            break;
		case SUB:
			printf("sub %d, %d, %d\n", mips_ins.rd, mips_ins.rs, mips_ins.rt);
			RegFile[mips_ins.rd] = RegFile[mips_ins.rs] - RegFile[mips_ins.rt];
        default:
            printf("Instrucao nao encontrada!\n");
            exit(1);
            break;
        }

    //I or J-format
    }else{
        switch (mips_ins.op_code) {
        case ADDI:
			printf("addi %d, %d, %d\n", mips_ins.rt, mips_ins.rs, mips_ins.immediate_16bits);
			RegFile[mips_ins.rt] = RegFile[mips_ins.rs] + mips_ins.immediate_16bits;
            break;
		case LW:
			printf("lw %d, %d(%d)\n", mips_ins.rt, mips_ins.immediate_16bits, mips_ins.rs);
			RegFile[mips_ins.rt] = get_DataMem(mips_ins.immediate_16bits + RegFile[mips_ins.rs]);
			break;
		case SW:
			printf("sw %d, %d(%d)\n", mips_ins.rt, mips_ins.immediate_16bits, mips_ins.rs);
			set_DataMem(mips_ins.immediate_16bits + RegFile[mips_ins.rs], RegFile[mips_ins.rt]);
			break;
		case LUI:
			printf("lui %d, %d\n", mips_ins.rt, mips_ins.immediate_16bits);
			RegFile[mips_ins.rt] = mips_ins.immediate_16bits << 16;
			break;
		case ORI:
			printf("ori %d, %d, %d\n", mips_ins.rt, mips_ins.rs, mips_ins.immediate_16bits);
			RegFile[mips_ins.rt] = RegFile[mips_ins.rs] | mips_ins.immediate_16bits;
			break;
        default:
            printf("Instrucao nao encontrada!\n");
            exit(1);
            break;
        }
    }
    return this->pc+4;
}


void mips::reg_output() {
    printf("-----------------------------------\n");
    printf("pc      		0x%08x\n", this->pc);
    printf("-----------------------------------\n");
    printf("$zero   0		0x%08x\n", this->RegFile[0]);
    printf("$at     1 		0x%08x\n", this->RegFile[1]);
    printf("$v0     2 		0x%08x\n", this->RegFile[2]);
    printf("$v1     3 		0x%08x\n", this->RegFile[3]);
    printf("$a0     4 		0x%08x\n", this->RegFile[4]);
    printf("$a1     5 		0x%08x\n", this->RegFile[5]);
    printf("$a2     6 		0x%08x\n", this->RegFile[6]);
    printf("$a3     7 		0x%08x\n", this->RegFile[7]);
    printf("$t0     8 		0x%08x\n", this->RegFile[8]);
    printf("$t1     9 		0x%08x\n", this->RegFile[9]);
    printf("$t2     10		0x%08x\n", this->RegFile[10]);
    printf("$t3     11		0x%08x\n", this->RegFile[11]);
    printf("$t4     12		0x%08x\n", this->RegFile[12]);
    printf("$t5     13		0x%08x\n", this->RegFile[13]);
    printf("$t6     14		0x%08x\n", this->RegFile[14]);
    printf("$t7     15		0x%08x\n", this->RegFile[15]);
    printf("$s0     16		0x%08x\n", this->RegFile[16]);
    printf("$s1     17		0x%08x\n", this->RegFile[17]);
    printf("$s2     18		0x%08x\n", this->RegFile[18]);
    printf("$s3     19		0x%08x\n", this->RegFile[19]);
    printf("$s4     20		0x%08x\n", this->RegFile[20]);
    printf("$s5     21		0x%08x\n", this->RegFile[21]);
    printf("$s6     22		0x%08x\n", this->RegFile[22]);
    printf("$s7     23		0x%08x\n", this->RegFile[23]);
    printf("$t8     24		0x%08x\n", this->RegFile[24]);
    printf("$t9     25		0x%08x\n", this->RegFile[25]);
    printf("$k0     26		0x%08x\n", this->RegFile[26]);
    printf("$k1     27		0x%08x\n", this->RegFile[27]);
    printf("$gp     28		0x%08x\n", this->RegFile[28]);
    printf("$sp     29		0x%08x\n", this->RegFile[29]);
    printf("$fp     30		0x%08x\n", this->RegFile[30]);
    printf("$ra     31		0x%08x\n", this->RegFile[31]);
    printf("-----------------------------------\n");

}

void mips::data_output(unsigned int n) {
    printf("-----------------------------------\n");
    printf("\n.DATA\n");
    printf("-----------------------------------\n");

    unsigned int var,addr;
    addr=0x10010000;
    for (var = 0; var < n; ++var) {
        printf("ADDR 0x%08x:	0x%08x\n",addr+(var * 4), this->DataMem[var]);
    }
    printf("-----------------------------------\n");
}
