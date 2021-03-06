/* ast.h
 * 
 * Contains definitions of the node data structure, and the data structs used by 
 * respective nodes.
 */

#ifndef AST_H
#define AST_H

#include <stdbool.h>

/* WHEN CREATING A NEW NODE TYPE:
 * Add its type to the node_type_e enum.
 * Declare its data struct below.
 * Write "create" method in tree_handler.c
 * Add a case to the switch in create_node in tree_handler.c
 * Write "check" method in tree_checker.c
 * Add a case to the switch in check_node in tree_checker.c
 * Write "generate" method in code_gen.c
 * Add a case to the switch in generate_node in code_gen.c
 * Don't forget to use breaks in above switch statements.
 * If adding a loop, add a condition in check_continue_statement in tree_checker.c
 */

typedef enum 
{
    NODE_GLOBAL_BLOCK,
    NODE_ARG_BLOCK,
    NODE_ARG_DEF,
    NODE_ARG_DEF_BLOCK,
    NODE_ARR_ACCESS,
    NODE_ARR_ACCESSOR,
    NODE_ARR_DEC,
    NODE_ARR_DIM,
    NODE_ARR_DIM_BLOCK,
    NODE_ARR_MULTI_ACCESSOR,
    NODE_ARR_MULTI_DIM_DEC,
    NODE_ASSIGN,
    NODE_ASSIGN_DEST,
    NODE_BIN_EXPR,
    NODE_BREAK,
    NODE_CASE,
    NODE_CASE_BLOCK,
    NODE_CONTINUE,
    NODE_DEC,
    NODE_DEC_W_ASSIGN,
    NODE_FOR_LOOP,
    NODE_DO_UNTIL_LOOP,
    NODE_DO_WHILE_LOOP,
    NODE_WHILE_LOOP,
    NODE_FUNC_CALL,
    NODE_FUNC_DEF,
    NODE_GOTO,
    NODE_IF_STMNT,
    NODE_ELSEIF_STMNT,
    NODE_ELSE_STMNT,
    NODE_ELSEIF_BLOCK,
    NODE_LABELMAKER,
    NODE_LIT_BLOCK,
    NODE_METHOD_CALL,
    NODE_NULL_STMNT,
    NODE_NULL,
    NODE_OBJ_ACCESSOR_BLOCK,
    NODE_RETURN,
    NODE_POSTFIX,
    NODE_PRI,
    NODE_PRIMARY,
    NODE_STMNT_BLOCK,
    NODE_STRUCT_DEF,
    NODE_STRUCT_CONSTRUCTOR,
    NODE_STRUCT_INIT,
    NODE_STRUCT_MEM_BLOCK,
    NODE_SWITCH,
    NODE_FAST_SWITCH,
    NODE_FSWITCH_CALL,
    NODE_SYMBOL
} node_type_e;

typedef struct node_t node_t;

struct node_t
{
    node_t *parent;
    node_type_e node_type;

    bool end_line;
    bool increase_indent;
    bool global; // global or local
    bool global_statement; // is this node in the global scope
    bool dont_specify_global; // prevents printing of "local" or "global"
    bool member; // member of a data structure like a struct or class

    int line_no;
    
    void *data;
};

typedef enum
{
    PRI_LITERAL_NUM,
    PRI_LITERAL_STR,
    PRI_LITERAL_BOOL
} primary_type_e;

typedef union
{
    double numValue;
    char* strValue;
    bool boolValue;
    node_t* nodeValue;
} primary_value;

typedef struct 
{
    node_t *global_block;
} tree_t;

typedef struct 
{
    int num_children;
    node_t **children;
} parent_block_data;

typedef struct 
{
    node_t* return_type;
    node_t* identifier;
    node_t* arg_def_block;
    node_t* statement_block;
} func_def_data;

typedef struct 
{
    node_t* identifier;
    node_t* arg_block;
} func_call_data;

typedef struct 
{
    node_t* type;
    node_t* identifier;
} arg_def_data;

typedef struct 
{
    node_t* dest;
    node_t* expr;
    char* op;
} assign_data;

typedef struct 
{
    node_t* type;
    node_t* identifier;
} declaration_data;

typedef struct 
{
    node_t* type;
    node_t* identifier;
    node_t* expr;
} declaration_with_assign_data;

typedef struct
{
    node_t* left_node;
    node_t* right_node;
    char* op;
    
    bool in_parentheses;
    char* unary;
} bin_expr_data;

typedef struct
{
    primary_type_e val_type;
    primary_value val;

    bool in_parentheses;
    char* unary;
} primary_data;

typedef struct
{
    node_t* identifier;
    char* op;
} postfix_data;

typedef struct
{
    node_t* identifier;
    node_t* accessors;
} array_access_data;

typedef struct
{
    node_t* expr;
} array_accessor_data;

typedef struct
{
    node_t* identifier;
    int size;
    node_t* literal_block;
} array_dec_data;

typedef struct
{
    node_t* identifier;
    node_t* member_block;
} struct_def_data;

typedef struct
{
    node_t* type;
    
    node_t* func_call;
} struct_init_data;

typedef struct
{
    int num;
} array_dim_data;

typedef struct
{
    node_t* identifier;
    node_t* dimensions;
    node_t* literal_block;
} array_multidim_dec_data;

typedef struct
{
    char* identifier;
    bool is_type;
} symbol_data;

typedef struct
{
    node_t* obj_access;
    node_t* func_call;
} method_call_data;

typedef struct
{
    node_t* rel_expr;
    node_t* stmnt_block;
    node_t* elseif_block;
    node_t* else_stmnt;
} if_stmnt_data;

typedef struct
{
    node_t* rel_expr;
    node_t* stmnt_block;
} elseif_stmnt_data;

typedef struct
{
    node_t* stmnt_block;
} else_stmnt_data;

typedef struct
{
    node_t* rel_expr;
    node_t* stmnt_block;

    node_t* continue_statement;
} while_loop_data;

typedef struct
{
    node_t* rel_expr;
    node_t* stmnt_block;

    node_t* continue_statement;
} do_while_loop_data;

typedef struct
{
    node_t* rel_expr;
    node_t* stmnt_block;

    node_t* continue_statement;
} do_until_loop_data;

typedef struct
{
    node_t* assign_stmnt;
    node_t* rel_expr;
    node_t* inc_stmnt;
    node_t* stmnt_block;

    node_t* continue_statement;
} for_loop_data;

typedef struct
{
    node_t* identifier;
} labelmaker_data;

typedef struct
{
    node_t* identifier;
} continue_statement_data;

typedef struct
{
    node_t* identifier;
} goto_statement_data;

typedef struct
{
    node_t* expr;
} return_statement_data;

typedef struct
{
    node_t* expr;
    node_t* case_block;

    node_t* break_me;
    node_t* default_bool;

    bool has_default;
} switch_statement_data;

typedef struct
{
    node_t* type;
    node_t* identifier;

    node_t* params;
    node_t* case_block;

    bool has_default;
} fast_switch_data;

typedef struct
{
    node_t* expr;
    node_t* stmnt_block;

    bool has_break;
} case_data;

typedef struct
{
    node_t* identifier;
    node_t* expr;
    node_t* arg_block;
} fswitch_call_data;

typedef struct
{
    node_t* arg_def_block;
    node_t* stmnt_block;
} struct_constructor_data;

#endif
