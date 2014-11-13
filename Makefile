bison:
	bison -d parser.y
flex:
	flex lexical.l
clang:
	flex lexical.l
	bison -d parser.y
	clang-3.5 main.c absyn.c errormsg.c prabsyn.c symbol.c table.c temp.c types.c utils.c parser.tab.c lex.yy.c -g
all:
	flex lexical.l
	bison -d parser.y
	gcc main.c absyn.c errormsg.c prabsyn.c symbol.c table.c temp.c types.c utils.c parser.tab.c lex.yy.c -g
