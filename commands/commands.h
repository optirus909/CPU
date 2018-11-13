CMD_DEF(PUSHR, printf("PUSHR\n");)
CMD_DEF(PUSHD,                                                          \
        printf("PUSHD\n");                                              \
        char * buf = (char *) calloc(sizeof(elem_t), sizeof(char));     \
        pCPU->RPC++;                                                    \
        for (int i = 0; i < sizeof(elem_t); i++)                        \
            buf[i] = pcode[pCPU->RPC + i];                              \
        elem_t a = strtod(buf, &buf);                                   \
        printf("PUSHD: data: %lg\n", a);                                \
        StackPush(&(pCPU->stk), a);                                     \
        pCPU->RPC += sizeof(elem_t) - 1;                                )
CMD_DEF(PUSHM, printf("PUSHM\n");)
CMD_DEF(POPR, printf("POPR\n");)
CMD_DEF(POPD, printf("POPD\n");)
CMD_DEF(POPM, printf("POPM\n");)
CMD_DEF(ADD, printf("ADD\n");)
CMD_DEF(SUB,printf("SUB\n");)
CMD_DEF(SQRT,printf("SQRT\n");)
CMD_DEF(MUL,printf("MUL\n");)
CMD_DEF(DIV,printf("DIV\n");)
CMD_DEF(IN,printf("IN\n");)
CMD_DEF(OUT,printf("OUT\n");)
CMD_DEF(END,printf("END\n");)