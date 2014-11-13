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

class ABS_var
{
    protected:
        llvm::Value *ErrorV(const char *Str)
        {
            std::cout << Str << std::endl;
            return 0;
        }

    public:
        enum { ABS_SIMPLE_VAR, ABS_FIELD_VAR, ABS_SUBSCRIPT_VAR } kind;
        ABS_pos pos;
        union u
        {
            S_symbol simple;
            Field_var field;
            Subscript_var subscript;
        };

        ABS_var(ABS_pos pos, S_symbol sym) : kind (ABS_SIMPLE_VAR), pos(pos), u.simple(sym) { }
        ABS_var(ABS_pos pos, ABS_var var, S_symbol sym) : kind(ABS_FIELD_VAR), pos(pos), u.field(Field_var(var, sym)) { }
        ABS_var(ABS_pos pos, ABS_var var, ABS_expr expr) : kind(ABS_SUBSCRIPT_VAR), pos(pos), u.subscript(Subscript_var(var, expr)) { }

        virtual ~ABS_var() {};
        virtual llvm::Value *Codegen() = 0;
};

class Field_var
{
public:
    ABS_var var;
    S_symbol sym;
    Field_var(ABS_var var, S_symbol sym) : var(var),  sym(sym) { }
};

class Subscript_var
{
public:
    ABS_var var; 
    ABS_expr expr;
    Subscript_var(ABS_var var, ABS_expr expr) : var(var), expr(expr) { }
};

class Var_expr
{
public:
    S_symbol func; 
    ABS_expr_list args;
    Var_expr(S_symbol func, ABS_expr_list args) : func(func), args(args) { }
};

class Op_expr
{
public:
    ABS_oper oper;
    ABS_expr left;
    ABS_expr right;
    Op_expr(ABS_oper oper, ABS_expr left, ABS_expr, right) : oper(oper), left(left), right(right) { }
};

class Record_expr
{
public:
    S_symbol type;
    ABS_efield_list fields;
    Record_expr(S_symbol type, ABS_efield_list fields) : type(type), fields(fields) { }
};

class Assign_expr
{
public:
    ABS_var var;
    ABS_expr expr;
    Assign_expr(ABS_var var, ABS_expr expr) : var(var), expr(expr) { }
};

class If_expr
{
public:
    ABS_expr test, then, elsee;
    If_expr(ABS_expr test, ABS_expr then, ABS_expr elsee) : test(test), then(then), elsee(elsee) { }
};

class While_expr
{
public:
    ABS_expr test, body;
    While_expr(ABS_expr test, ABS_expr body) : test(test), body(body) { }
};

class For_expr
{
public:
    S_symbol var; 
    ABS_expr lo, hi, body; 
    bool escape;
    For_expr(S_symbol var, ABS_expr lo, ABS_expr hi, ABS_expr body) : var(var), lo(lo), hi(hi), body(body) { }
};

class Let_expr
{
public:
    ABS_dec_list decs; 
    ABS_expr body;
    Let_expr(ABS_dec_list decs, ABS_expr body) : decs(decs), body(body) { }
};

class Array_expr
{
public:
    S_symbol type; 
    ABS_expr size, init;
    Array_expr(S_symbol type, ABS_expr size, ABS_expr init) : type(type), size(size), init(init) { }
};

class ABS_expr 
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        enum 
        {
            ABS_VAR_EXPR, ABS_NIL_EXPR, ABS_INT_EXPR, ABS_STRING_EXPR,
            ABS_CALL_EXPR, ABS_OP_EXPR, ABS_RECORD_EXPR, ABS_SEQ_EXPR,
            ABS_ASSIGN_EXPR, ABS_IF_EXPR, ABS_WHILE_EXPR, ABS_FOR_EXPR,
            ABS_BREAK_EXPR, ABS_LET_EXPR, ABS_ARRAY_EXPR
        } kind;
        ABS_pos pos;
        union
        {
            ABS_var var;
            /* nil; */
            int intt;
            string stringg;
            Var_expr call;
            Op_expr op;
            Record_expr recordd;
            ABS_expr_list seq;
            Assign_expr assign;
            If_expr iff;
            While_expr whilee;
            For_expr forr;
            /* breakk; */
            Let_expr let;
            Array_expr array;
        } u;

        ABS_expr(ABS_pos pos, ABS_var var) : kind(ABS_VAR_EXPR), pos(pos), u.var(var) { }
        ABS_expr(ABS_pos pos) : kind(ABS_NIL_EXPR), pos(pos) { }
        ABS_expr(ABS_pos pos, int i) : kind(ABS_INT_EXPR), pos(pos), u.i(intt) { }
        ABS_expr(ABS_pos pos, string str) : kind(ABS_STRING_EXPR), pos(pos), u.stringg(str) { }
        ABS_expr(ABS_pos pos, S_symbol func, ABS_expr_list args) : kind(ABS_CALL_EXPR), pos(pos), u.call(Var_expr(func, args)) { }
        ABS_expr(ABS_pos pos, ABS_oper oper, ABS_expr expr, ABS_expr expr) : kind(ABS_OP_EXPR), pos(pos), u.op(Op_expr(oper, left, right)) { }
        ABS_expr(ABS_pos pos, S_symbol type, ABS_efield_list fields) : kind(ABS_RECORD_EXPR), pos(pos), u.recordd(Record_expr(type, fields)) { }
        ABS_expr(ABS_pos pos, ABS_expr_list seq) : kind(ABS_SEQ_EXPR), pos(pos), u.seq(seq);
        ABS_expr(ABS_pos pos, ABS_var var, ABS_expr expr) : kind(ABS_ASSIGN_EXPR), pos(pos), u.assign(Assign_expr(var, expr)) { }
        ABS_expr(ABS_pos pos, ABS_expr test, ABS_expr then, ABS_expr elsee) : kind(ABS_IF_EXPR), pos(pos), u.iff(If_expr(test, then, elsee)) { }
        ABS_expr(ABS_pos pos, ABS_expr test, ABS_expr body) : kind(ABS_WHILE_EXPR), pos(pos), u.whilee(While_expr(test, body)) { }
        ABS_expr(ABS_pos pos, S_symbol var, ABS_expr lo, ABS_expr hi, ABS_expr body) : kind(ABS_FOR_EXPR), pos(pos), u.forr(For_expr(var, lo, hi, body)) { }
        ABS_expr(ABS_pos pos) : kind(ABS_BREAK_EXPR), pos(pos) { }
        ABS_expr(ABS_pos pos, ABS_dec_list decs, ABS_expr body) : kind(ABS_LET_EXPR), pos(pos), u.let(Let_expr(decs, body)) { }
        ABS_expr(ABS_pos pos, S_symbol type, ABS_expr size, ABS_expr init) : kind(ABS_ARRAY_EXPR), pos(pos), u.array(Array_expr(type, size, init)) { }

        virtual ~ABS_expr() {};
        virtual llvm::Value *Codegen() = 0;
};

class Var_dec
{
    S_symbol var; 
    S_symbol type; 
    ABS_expr init; 
    bool escape;
    Var_dec(S_symbol var, S_symbol type, ABS_expr init) : var(var), type(type), init(init), escape(TRUE) { }
};

class ABS_dec
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        enum { ABS_FUNCTION_DEC, ABS_VAR_DEC, ABS_TYPE_DEC } kind;
        ABS_pos pos;
        union 
        {
            ABS_fundec_list function;
            Var_dec var;
            ABS_namety_list type;
        } u;

        ABS_dec(ABS_pos pos, ABS_fundec_list function) : kind(ABS_FUNCTION_DEC), pos(pos), u.function(function) { }
        ABS_dec(ABS_pos pos, S_symbol var, S_symbol type, ABS_expr init) : kind(ABS_VAR_DEC), pos(pos), u.var(Var_dec(var, type, init)) { }
        ABS_dec(ABS_pos pos, ABS_namety_list type) : kind(ABS_TYPE_DEC), pos(pos), u.type(type) { }

        virtual ~ABS_dec() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_type
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        enum { ABS_NAME_TYPE, ABS_RECORD_TYPE, ABS_ARRAY_TYPE } kind;
        ABS_pos pos;
        union
        {
            S_symbol name;
            ABS_field_list record;
            S_symbol array;
        } u;

        ABS_type(ABS_pos pos, S_symbol name) : kind(ABS_NAME_TYPE), pos(pos), u.name(name) { }
        ABS_type(ABS_pos pos, ABS_field_list record) : kind(ABS_RECORD_TYPE), pos(pos), u.record(record) { }
        ABS_type(ABS_pos pos, S_symbol array) : kind(ABS_ARRAY_TYPE), pos(pos), u.array(array) { }

        virtual ~ABS_type() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_field
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        S_symbol name, type;
        bool escape;

        ABS_field(S_symbol name, S_symbol type) : name(name), type(type), escape(TRUE) { }

        virtual ~ABS_field() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_field_list
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_field head;
        ABS_field_list tail;

        ABS_field_list(ABS_field head, ABS_field_list tail) : head(head), tail(tail) { }

        virtual ~ABS_field_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_efield
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_pos pos;
        S_symbol name;
        ABS_expr expr;

        ABS_efield(ABS_pos pos, S_symbol name, ABS_expr expr) : pos(pos), name(name), expr(expr) { }

        virtual ~ABS_efield() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_efield_list
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_efield head; 
        ABS_efield_list tail;

        ABS_efield_list(ABS_efield head, ABS_efield_list tail) : head(head), tail(tail) { }

        virtual ~ABS_efield_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_expr_list
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_expr head;
        ABS_expr_list tail;

        ABS_expr_list(ABS_expr head, ABS_expr_list tail) : head(head), tail(tail) { }

        virtual ~ABS_expr_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_fundec
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_pos pos; 
        S_symbol name; 
        ABS_field_list params; 
        S_symbol result; 
        ABS_expr body;
        
        ABS_fundec(ABS_pos pos, S_symbol name, ABS_field_list params, S_symbol result, ABS_expr body) : pos(pos), name(name), params(params), result(result), body(body) { }
        
        virtual ~ABS_fundec() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_fundec_list
{
    protected:
        llvm::Value *ErrorV(const char *Str) 
        {
            std::cout << Str << std::endl; 
            return 0; 
        }

    public:
        ABS_fundec head; 
        ABS_fundec_list tail;

        ABS_fundec_list(ABS_fundec head, ABS_fundec_list tail) : head(head), tail(tail) { }

        virtual ~ABS_fundec_list() {};
        virtual llvm::Value *Codegen() = 0;
};

class ABS_dec_list
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

class ABS_namety
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

class ABS_namety_list
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
