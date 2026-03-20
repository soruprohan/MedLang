all:
	bison -d medlang.y
	flex medlang.l
	gcc medlang.tab.c lex.yy.c ast.c -o medlang.exe
	medlang.exe samples/test1.med