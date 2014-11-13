#include "temp.h"
#include "table.h"

struct TEMP_temp_
{
	int num;
};

string TEMP_label_string(TEMP_label s)
{
	return S_name(s);
}

static int labels = 0;

TEMP_label TEMP_new_label(void)
{
	char buf[100];
	sprintf(buf, "L%d", labels++);
	return TEMP_named_label(String(buf));
}

TEMP_label TEMP_named_label(string s)
{
	return S_Symbol(s);
}

static int temps = 100;

TEMP_temp TEMP_new_temp(void)
{
	TEMP_temp p = (TEMP_temp) checked_malloc(sizeof(*p));
	p->num = temps++;
	{
		char r[16];
		sprintf(r, "%d", p->num);
		TEMP_enter(TEMP_name(), p, String(r));
	}
	return p;
}

struct TEMP_map_ { TAB_table tab; TEMP_map under; };

TEMP_map TEMP_name(void)
{
	static TEMP_map map = NULL;
	if (!map) map = TEMP_empty();
	return map;
}

TEMP_map new_map(TAB_table tab, TEMP_map under)
{
	TEMP_map map = checked_malloc(sizeof(*map));
	map->tab = tab;
	map->under = under;
	return map;
}

TEMP_map TEMP_empty(void)
{
	return new_map(TAB_empty(), NULL);
}

TEMP_map TEMP_layer_map(TEMP_map over, TEMP_map under)
{
	if (over == NULL) return under;
	else return new_map(over->tab, TEMP_layer_map(over->under, under));
}

void TEMP_enter(TEMP_map map, TEMP_temp temp, string s)
{
	assert(map && map->tab);
	TAB_enter(map->tab, temp, s);
}

string TEMP_lookup(TEMP_map map, TEMP_temp temp)
{
	string s;
	assert(map && map->tab);
	s = TAB_lookup(map->tab, temp);
	if (s) return s;
	else if(map->under) return TEMP_lookup(map->under, temp);
	else return NULL;
}

TEMP_temp_list TEMP_Temp_list(TEMP_temp head, TEMP_temp_list tail)
{
	TEMP_temp_list p = (TEMP_temp_list) checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

TEMP_label_list TEMP_Label_list(TEMP_label head, TEMP_label_list tail)
{
	TEMP_label_list p = (TEMP_label_list) checked_malloc(sizeof(*p));
	p->head = head;
	p->tail = tail;
	return p;
}

static FILE *_fp;

void showit(TEMP_temp temp, string str)
{
	fprintf(_fp, "temp%d -> %s\n", temp->num, str);
}

void TEMP_dump_map(FILE *fp, TEMP_map map)
{
	_fp = fp;
	TAB_dump(map->tab, (void (*)(void *, void *))showit);
	if (map->under)
	{
		fprintf(fp, "---------\n");
		TEMP_dump_map(fp, map->under);
	}
}
