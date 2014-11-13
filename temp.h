#include <stdio.h>

#include "symbol.h"

typedef struct TEMP_temp_ *TEMP_temp;
TEMP_temp TEMP_new_temp(void);

typedef struct TEMP_temp_list_ *TEMP_temp_list;
struct TEMP_temp_list_ { TEMP_temp head; TEMP_temp_list tail; };
TEMP_temp_list TEMP_Temp_list(TEMP_temp head, TEMP_temp_list tail);

typedef S_symbol TEMP_label;
TEMP_label TEMP_new_label(void);
TEMP_label TEMP_named_label(string s);
string TEMP_label_string(TEMP_label s);

typedef struct TEMP_label_list_ *TEMP_label_list;
struct TEMP_label_list_ { TEMP_label head; TEMP_label_list tail; };
TEMP_label_list TEMP_Label_list(TEMP_label head, TEMP_label_list tail);

typedef struct TEMP_map_ *TEMP_map;
TEMP_map TEMP_empty(void);
TEMP_map TEMP_layer_map(TEMP_map over, TEMP_map under);
void TEMP_enter(TEMP_map map, TEMP_temp temp, string s);
string TEMP_lookup(TEMP_map map, TEMP_temp temp);
void TEMP_dump_map(FILE *fp, TEMP_map map);
TEMP_map TEMP_name(void);
