all:
	bison -d medlang.y
	flex medlang.l
	gcc medlang.tab.c lex.yy.c ast.c symtable.c semantic.c tac.c -o medlang.exe
	medlang.exe samples/test_scope.med