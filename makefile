lextest: driver.o lex.yy.o errormsg.o utils.o
	cc -g -o lextest driver.o lex.yy.o errormsg.o utils.o

driver.o: driver.c tokens.h errormsg.h utils.h
	cc -g -c driver.c

errormsg.o: errormsg.c errormsg.h utils.h
	cc -g -c errormsg.c

lex.yy.o: lex.yy.c tokens.h errormsg.h utils.h
	cc -g -c lex.yy.c

lex.yy.c: lexical.l
	flex lexical.l

utils.o: utils.c utils.h
	cc -g -c utils.c

clean: 
	rm -f a.out utils.o driver.o lex.yy.o lex.yy.c errormsg.o
