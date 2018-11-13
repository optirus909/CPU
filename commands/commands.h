CMD_DEF(PUSHR, printf("PUSHR\n");)

CMD_DEF(PUSHD,                                                          \
        printf("PUSHD\n");                                              \
        char * buf = (char *) calloc(sizeof(elem_t), sizeof(char));     \
        pCPU->RPC++;                                                    \
        for (int i = 0; i < sizeof(elem_t); i++)                        \
            buf[i] = pcode[pCPU->RPC + i];                              \
        elem_t a = strtod(buf, &buf);                                   \
        printf("PUSHD: data: %lg\n", a);                                \
        StackPush(&pCPU->stk, a);                                       \
        pCPU->RPC += sizeof(elem_t) - 1;                                )

CMD_DEF(PUSHM, printf("PUSHM\n");)

CMD_DEF(POPR, printf("POPR\n");)

CMD_DEF(POPD,                                                           \
        printf("POPD\n");                                               \
        elem_t val = 0;                                                 \
        StackPop(&pCPU->stk, &val);                                      \
        printf("POPD: data: %lg\n", val);                               )

CMD_DEF(POPM, printf("POPM\n");)

CMD_DEF(ADD,                                                            \
        printf("ADD\n");                                                \
        elem_t a = 0;                                                   \
        elem_t b = 0;                                                   \
        StackPop(&pCPU->stk, &a);                                        \
        StackPop(&pCPU->stk, &b);                                        \
        printf("ADD: data: a = %lg, b = %lg\n", a, b);                  \
        StackPush(&pCPU->stk, a + b);                                   )

CMD_DEF(SUB,printf("SUB\n");                                            \
        elem_t a = 0;                                                   \
        elem_t b = 0;                                                   \
        StackPop(&pCPU->stk, &a);                                        \
        StackPop(&pCPU->stk, &b);                                        \
        printf("SUB: data: a = %lg, b = %lg\n", a, b);                  \
        StackPush(&pCPU->stk, b - a);                                   )

CMD_DEF(SQRT,                                                           \
        printf("SQRT\n");                                               \
        elem_t val = 0;                                                 \
        StackPop(&pCPU->stk, &val);                                      \
        printf("POPD: data: %lg\n", val);                               \
        StackPush(&pCPU->stk, sqrt(val));                                   )

CMD_DEF(MUL,printf("MUL\n");                                            \
        elem_t a = 0;                                                   \
        elem_t b = 0;                                                   \
        StackPop(&pCPU->stk, &a);                                        \
        StackPop(&pCPU->stk, &b);                                        \
        printf("MUL: data: a = %lg, b = %lg\n", a, b);                  \
        StackPush(&pCPU->stk, a * b);                                   )

CMD_DEF(DIV,printf("DIV\n");                                            \
        elem_t a = 0;                                                   \
        elem_t b = 0;                                                   \
        StackPop(&pCPU->stk, &a);                                        \
        StackPop(&pCPU->stk, &b);                                        \
        printf("DIV: data: a = %lg, b = %lg\n", a, b);                  \
        StackPush(&pCPU->stk, b / a);                                   )

CMD_DEF(IN,                                                     \
        printf("IN\n");                                         \
        elem_t val = 0;                                         \
        scanf("%lg", &val);                                     \
        StackPush(&pCPU->stk, val);                                        )

CMD_DEF(OUT,                                                            \
        printf("OUT\n");                                                \
        elem_t val = 0;                                                 \
        StackPop(&pCPU->stk, &val);                                     \
        printf("OUT: %lg\n", val);                                      )

CMD_DEF(END,printf("END\n");)