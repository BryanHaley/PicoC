#ifndef AST_H
#define AST_H

typedef enum
{
	TYPE_VAR,
	TYPE_POINTER,
	TYPE_LITERAL_NUM,
	TYPE_LITERAL_STRING,
	TYPE_LITERAL_BOOL,
} data_types_e;

typedef struct 
{
	data_types_e type;
	char *name;
	double value;
} symbol_t;

typedef enum 
{
	NODE_GLOBAL_BLOCK,
	NODE_FUNC_DEF,
	NODE_ARG_DEF_BLOCK,
	NODE_ARG_DEF,
	NODE_STMNT_BLOCK,
	NODE_STMNT,
	NODE_ASSIGN,
	NODE_FUNC_CALL,
	NODE_ARG_BLOCK,
	NODE_ARG
} node_type_e;

typedef struct node_t node_t;

struct node_t
{
	node_t *parent;
	node_type_e node_type;
	
	void *data;
};

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
	data_types_e return_type;
	symbol_t *identifier;
	node_t *arg_def_block;
	node_t *statement_block;
} func_def_data;

typedef struct 
{
	symbol_t *identifier;
} arg_def_data;

typedef struct 
{
	node_type_e statement_type;
	node_t *statement;
} statement_data;

typedef struct 
{
	node_type_e statement_type;
	symbol_t *left_operand;
	symbol_t *right_operand;
} assign_data;

typedef struct 
{
	symbol_t *identifier;
	node_t *argument_block;
} func_call_data;

typedef struct 
{
	symbol_t *identifier;
} arg_data;

#endif