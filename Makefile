all:
	bison -d medlang.y
	flex medlang.l
	gcc medlang.tab.c lex.yy.c ast.c symtable.c semantic.c interp.c -o medlang.exe -lm
	medlang.exe samples/se_undeclared.med