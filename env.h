#include "symbol.h"
#include "temp.h"
#include "types.h"

typedef struct ENV_entry_ *ENV_entry;
struct ENV_entry_
{
	enum { ENV_VAR_ENTRY, ENV_FUNC_ENTRY } kind;
	union
	{
		struct 
		{
			TY_type type;
		} var;

		struct
		{
			TY_type_list formals;
			TY_type result;
		} func;
	} u;
};

