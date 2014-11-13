#include <iostream>

#include "symbol.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace 
{
    llvm::LLVMContext &Context = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("main", Context);
    llvm::IRBuilder<> Builder(llvm::getGlobalContext());
    std::map<std::string, llvm::Value*> NamedValues;
}

typedef int ABS_pos;

typedef enum
{  
    ABS_PLUS, ABS_MINUS, ABS_TIMES, ABS_DIVIDE,
    ABS_EQ, ABS_NEQ, ABS_LT, ABS_LE, ABS_GT, ABS_GE,
} ABS_oper;

class ABS_node
{
protected:
    llvm::Value *ErrorV(const char *Str)
    {
        std::cout << Str << std::endl;
        return 0;
    }

public:
    virtual ~ABS_var() {};
    virtual llvm::Value *Codegen() = 0;
};

class ABS_var : public ABS_node
{

};

class ABS_expr : public ABS_node
{
    
};

class ABS_dec : public ABS_node
{
    
};

class ABS_type : public ABS_node
{
   
};

class ABS_field : public ABS_node
{
    S_symbol name, type;
    bool escape;
public:
    ABS_field(S_symbol name, S_symbol type) : name(name), type(type), escape(TRUE) { }
};

class ABS_field_list : public ABS_node
{
    ABS_field *head;
    ABS_field_list *tail;
public:
    ABS_field_list(ABS_field *head, ABS_field_list *tail) : head(head), tail(tail) { }
};

class ABS_efield : public ABS_node
{
    ABS_pos pos;
    S_symbol name;
    ABS_expr *expr;
public:
    ABS_efield(ABS_pos pos, S_symbol name, ABS_expr *expr) : pos(pos), name(name), expr(expr) { }
};

class ABS_efield_list : public ABS_node
{
    ABS_efield *head; 
    ABS_efield_list *tail;
public:
    ABS_efield_list(ABS_efield *head, ABS_efield_list *tail) : head(head), tail(tail) { }
};

class ABS_expr_list : public ABS_node
{
    ABS_expr *head;
    ABS_expr_list *tail;
public:
    ABS_expr_list(ABS_expr *head, ABS_expr_list *tail) : head(head), tail(tail) { }
};

class ABS_fundec : public ABS_node
{
public:
    ABS_pos pos; 
    S_symbol name; 
    ABS_field_list params; 
    S_symbol result; 
    ABS_expr body;
    ABS_fundec(ABS_pos pos, S_symbol name, ABS_field_list params, S_symbol result, ABS_expr body) : pos(pos), name(name), params(params), result(result), body(body) { }
};

class ABS_fundec_list : public ABS_node
{
    ABS_fundec *head; 
    ABS_fundec_list *tail;
public:
    ABS_fundec_list(ABS_fundec *head, ABS_fundec_list *tail) : head(head), tail(tail) { }
};

class ABS_dec_list : public ABS_node
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_dec head; 
        ABS_dec_list tail;

        ABS_dec_list(ABS_dec head, ABS_dec_list tail) : head(head), tail(tail) { }

        virtual ~ABS_dec_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_namety : public ABS_node
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        S_symbol name; 
        ABS_type type;

        ABS_namety(S_symbol name, ABS_type type) : name(name), type(type) { }

        virtual ~ABS_namety() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_namety_list : public ABS_node
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_namety head; 
        ABS_namety_list tail;
        
        ABS_namety_list(ABS_namety head, ABS_namety_list tail) : head(head), tail(tail) { }

        virtual ~ABS_namety_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_simple_var : public ABS_var
{
    ABS_pos pos;
    S_symbol *simple;
public:
    ABS_simple_var(ABS_pos pos, S_symbol *sym) : pos(pos), simple(sym) { }
};

class ABS_field_var : public ABS_var
{
    ABS_pos pos;
    ABS_var *var;
    S_symbol *sym;
public:
    ABS_field_var(ABS_pos pos, ABS_var *var, S_symbol *sym) : pos(pos), var(var), sym(sym)  { }
};

class ABS_subscript_var : public ABS_var
{
    ABS_pos pos;
    ABS_var *var; 
    ABS_expr *expr;
public:
    ABS_subscript_var(ABS_pos pos, ABS_var *var, ABS_expr *expr) : pos(pos), var(var), expr(expr) { }
};


class ABS_var_expr
{
    ABS_pos pos;
    S_symbol *func; 
    ABS_expr_list *args;
public:
    ABS_var_expr(ABS_pos pos, S_symbol *func, ABS_expr_list *args) : pos(pos), func(func), args(args) { }
};

class ABS_op_expr
{
    ABS_pos pos;
    ABS_oper *oper;
    ABS_expr *left;
    ABS_expr *right;
public:
    ABS_op_expr(ABS_pos pos, ABS_oper *oper, ABS_expr *left, ABS_expr *right) : pos(pos) oper(oper), left(left), right(right) { }
};

class ABS_record_expr
{
    ABS_pos pos;
    S_symbol *type;
    ABS_efield_list *fields;
public:
    ABS_record_expr(ABS_pos pos, S_symbol *type, ABS_efield_list *fields) : pos(pos) type(type), fields(fields) { }
};

class ABS_assign_expr
{
    ABS_pos pos;
    ABS_var *var;
    ABS_expr *expr;
public:
    ABS_assign_expr(ABS_pos pos, ABS_var *var, ABS_expr *expr) : pos(pos) var(var), expr(expr) { }
};

class ABS_if_expr
{
    ABS_pos pos;
    ABS_expr *test, *then, *elsee;
public:
    ABS_if_expr(ABS_pos pos, ABS_expr *test, ABS_expr *then, ABS_expr *elsee) : pos(pos) test(test), then(then), elsee(elsee) { }
};

class ABS_while_expr
{
    ABS_pos pos;
    ABS_expr *test, *body;
public:
    ABS_while_expr(ABS_pos pos, ABS_expr *test, ABS_expr *body) : pos(pos) test(test), body(body) { }
};

class ABS_for_expr
{
    S_symbol var; 
    ABS_expr *lo, *hi, *body;
    bool escape;
public: 
    ABS_for_expr(ABS_pos pos, S_symbol var, ABS_expr *lo, ABS_expr *hi, ABS_expr *body) : pos(pos) var(var), lo(lo), hi(hi), body(body) { }
};

class ABS_let_expr
{
    ABS_pos pos;
    ABS_dec_list *decs; 
    ABS_expr *body;
public:
    ABS_let_expr(ABS_pos pos, ABS_dec_list *decs, ABS_expr *body) : pos(pos) decs(decs), body(body) { }
};

class ABS_array_expr
{
    ABS_pos pos;
    S_symbol type; 
    ABS_expr *size, *init;
public:
    ABS_array_expr(ABS_pos pos, S_symbol type, ABS_expr size, ABS_expr init) : pos(pos) type(type), size(size), init(init) { }
};

class ABS_function_dec
{
    ABS_pos pos;
    ABS_fundec_list *function;
public:
    ABS_function_dec(ABS_pos pos, ABS_fundec_list *function) : pos(pos), function(function) { }
};

class ABS_var_dec
{
    S_symbol var; 
    S_symbol type; 
    ABS_expr *init; 
    bool escape;
public:
    ABS_var_dec(ABS_pos pos, S_symbol var, S_symbol type, ABS_expr init) : pos(pos) var(var), type(type), init(init), escape(TRUE) { }
};

class ABS_type_dec
{
    ABS_pos pos;
    ABS_namety_list *type;
public:
    ABS_type_dec(ABS_pos pos, ABS_namety_list *type) : pos(pos), function(function) { }
};

class ABS_name_type
{
    ABS_pos pos;
    S_symbol name;
public:
    ABS_name_type(ABS_pos pos, S_symbol name) : pos(pos), name(name)
};

class ABS_record_type
{
    ABS_pos pos;
    ABS_field_list *record;
public:
    ABS_record_type(ABS_pos pos, ABS_field_list *record) : pos(pos), record(record)
};

class ABS_array_type
{
    ABS_pos pos;
    S_symbol array;
public:
    ABS_array_type(ABS_pos pos, S_symbol array) : pos(pos), array(array)
};