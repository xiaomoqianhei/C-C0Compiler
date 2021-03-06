#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#define MAX_SIZE 50

typedef struct exp* EXP;
typedef struct cmd* CMD;
typedef struct decl* DECL;
typedef struct instruction_list* I_List;
typedef enum {
    OpPlus, OpMinus, OpTimes, OpDiv
} A_Operand;

typedef enum {
    OpG, OpL, OpLEQ, OpGEQ, OpEQ, OpNOTEQ, OpOR, OpAND, OpASSIGN
} B_Operand;

typedef enum {
    BOOL_TYPE, INT_TYPE
} Type;

typedef enum {
    EXP_A_Op, EXP_B_Op, EXP_int, EXP_bool, EXP_Var
} EXP_Kind;

typedef enum {
    WHILE_KIND, IF_KIND, ASSIGN_KIND
} CMD_Kind;

typedef enum {
    CMD_, DECL_
} IL_Kind;


// ----- Expression ----- //
struct exp {
    EXP_Kind kind;
    union {
        int integer;
        bool boolean;
        char var[MAX_SIZE];
        struct {
            A_Operand oper;
            EXP left;
            EXP right;
        } opA;
        struct {
            B_Operand oper;
            EXP left;
            EXP right;
        } opB;
    } u;
};

EXP make_Int_EXP_(int i);
EXP make_Bool_EXP_(bool b);
EXP make_Var_EXP_(char* c);
EXP make_A_Op_EXP_(A_Operand op, EXP l, EXP r);
EXP make_B_Op_EXP_(B_Operand op, EXP l, EXP r);
// ----- Expression ----- //


// ----- Commands ----- //
struct cmd {
    CMD_Kind kind;
    union {
        struct {
            EXP if_;
            I_List then_I_list_;
            I_List else_I_list_;
        } if_cmd;
        struct {
            EXP while_;
            I_List while_I_list_;
        } while_cmd;
        struct {
            char var_[MAX_SIZE];
            EXP assignment_;
        } assign_cmd;
    } u;
};

CMD CMD_if_then_else(EXP if_exp, I_List then_list, I_List else_list);
CMD CMD_while(EXP exp, I_List il);
CMD CMD_assignment(char* var, EXP exp);
// ----- Commands ----- //


// ----- Declarations ----- //
struct decl {
    Type type;
    char var[MAX_SIZE];
};

DECL DECL_declare(Type t, char* v);
// ----- Declarations ----- //


// ----- Instruction List ----- //
struct instruction_list {
    IL_Kind kind;
    union {
        CMD cmd;
        DECL decl;
    } head;
    I_List tail;
};

I_List make_List_CMD_Head(CMD head, I_List tail);
I_List make_List_DECL_Head(DECL head, I_List tail);
// ----- Instruction List ----- //


#endif // TREE_H
