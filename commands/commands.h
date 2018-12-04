CMD_DEF(NOPE,                                                                                       )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(PUSHR,                                                                                      \
        printf("PUSHR\n");                                                                          \
        pCPU->RPC++;                                                                                \
        StackPush(&pCPU->stk, pCPU->reg[ pCPU->code[ pCPU->RPC ] ]);                                \
        cpu_dump(pCPU);                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(PUSHD,                                                                                      \
        printf("PUSHD\n");                                                                          \
        char * buf = (char *) calloc(sizeof(elem_t), sizeof(char));                                 \
        pCPU->RPC++;                                                                                \
        for (int i = 0; i < sizeof(elem_t); i++)                                                    \
            buf[i] = pCPU->code[pCPU->RPC + i];                                                     \
        elem_t a = strtod(buf, &buf);                                                               \
        printf("PUSHD: data: %lg\n", a);                                                            \
        StackPush(&pCPU->stk, a);                                                                   \
        pCPU->RPC += sizeof(elem_t) - 1;                                                            )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(PUSHM,                                                                                      \
        printf("PUSHM\n");                                                                          \
        char * buf = (char *) calloc(sizeof(elem_t), sizeof(char));                                 \
        pCPU->RPC++;                                                                                \
        for (int i = 0; i < sizeof(elem_t); i++)                                                    \
            buf[i] = pCPU->code[pCPU->RPC + i];                                                     \
        elem_t a = strtod(buf, &buf);                                                               \
        int index = (int) a;                                                                        \
        printf("PUSHM: index: %d\n", index);                                                        \
        StackPush(&pCPU->stk, pCPU->RAM[index]);                                                    \
        pCPU->RPC += sizeof(elem_t) - 1;                                                            \
        cpu_dump(pCPU);                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(POPR,                                                                                       \
        printf("POPR\n");                                                                           \
        pCPU->RPC++;                                                                                \
        StackPop(&pCPU->stk, &pCPU->reg[ pCPU->code[ pCPU->RPC ] ]);                                \
        cpu_dump(pCPU);                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(POPD,                                                                                       \
        printf("POPD\n");                                                                           \
        elem_t val = 0;                                                                             \
        StackPop(&pCPU->stk, &val);                                                                 \
        printf("POPD: data: %lg\n", val);                                                           )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(POPM,                                                                                       \
        printf("POPM\n");                                                                           \
        char * buf = (char *) calloc(sizeof(elem_t), sizeof(char));                                 \
        pCPU->RPC++;                                                                                \
        for (int i = 0; i < sizeof(elem_t); i++)                                                    \
            buf[i] = pCPU->code[pCPU->RPC + i];                                                     \
        elem_t a = strtod(buf, &buf);                                                               \
        int index = (int) a;                                                                        \
        printf("PUSHM: index: %d\n", index);                                                        \
        StackPop(&pCPU->stk, &pCPU->RAM[index]);                                                    \
        pCPU->RPC += sizeof(elem_t) - 1;                                                            \
        cpu_dump(pCPU);                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(ADD,                                                                                        \
        printf("ADD\n");                                                                            \
        elem_t a = 0;                                                                               \
        elem_t b = 0;                                                                               \
        StackPop(&pCPU->stk, &a);                                                                   \
        StackPop(&pCPU->stk, &b);                                                                   \
        printf("ADD: data: a = %lg, b = %lg\n", a, b);                                              \
        StackPush(&pCPU->stk, a + b);                                                               )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(SUB,printf("SUB\n");                                                                        \
        elem_t a = 0;                                                                               \
        elem_t b = 0;                                                                               \
        StackPop(&pCPU->stk, &a);                                                                   \
        StackPop(&pCPU->stk, &b);                                                                   \
        printf("SUB: data: a = %lg, b = %lg\n", a, b);                                              \
        StackPush(&pCPU->stk, b - a);                                                               )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(MUL,printf("MUL\n");                                                                        \
        elem_t a = 0;                                                                               \
        elem_t b = 0;                                                                               \
        StackPop(&pCPU->stk, &a);                                                                   \
        StackPop(&pCPU->stk, &b);                                                                   \
        printf("MUL: data: a = %lg, b = %lg\n", a, b);                                              \
        StackPush(&pCPU->stk, a * b);                                                               )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(DIV,printf("DIV\n");                                                                        \
        elem_t a = 0;                                                                               \
        elem_t b = 0;                                                                               \
        StackPop(&pCPU->stk, &a);                                                                   \
        StackPop(&pCPU->stk, &b);                                                                   \
        printf("DIV: data: a = %lg, b = %lg\n", a, b);                                              \
        StackPush(&pCPU->stk, b / a);                                                               )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(IN,                                                                                         \
        printf("IN\n");                                                                             \
        elem_t val = 0;                                                                             \
        scanf("%ld", &val);                                                                         \
        StackPush(&pCPU->stk, val);                                                                 )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(OUT,                                                                                        \
        printf("OUT\n");                                                                            \
        elem_t val = 0;                                                                             \
        StackPop(&pCPU->stk, &val);                                                                 \
        printf("OUT: %ld\n", val);                                                                  )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JMP,                                                                                        \
        printf("JMP\n");                                                                            \
        char * num = &pCPU->code[pCPU->RPC + 1];                                                    \
        char * end;                                                                                 \
        long val = strtol(num, &end, 10);                                                           \
        printf("new pc = %ld\n", val);                                                              \
        pCPU->RPC = val - 1;                                                                        )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JA,                                                                                         \
        JUMP(JA, >);                                                                                \
        printf("JA\n");                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JB,                                                                                         \
        JUMP(JB, <);                                                                                \
        printf("JB\n");                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JE,                                                                                         \
        JUMP(JE, ==);                                                                               \
        printf("JE\n");                                                                             )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JAE,                                                                                        \
        JUMP(JAE, >=);                                                                              \
        printf("JAE\n");                                                                            )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JBE,                                                                                        \
        JUMP(JBE, <=);                                                                              \
        printf("JBE\n");                                                                            )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(JRE,                                                                                        \
        JUMP(JRE, !=);                                                                              \
        printf("JRE\n");                                                                            )

//-----------------------------------------------------------------------------------------------------

CMD_DEF(END,                                                                                        \
        printf("END\n");                                                                            )