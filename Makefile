all:
	bison -d medlang.y
	flex medlang.l
	gcc medlang.tab.c lex.yy.c ast.c symtable.c semantic.c tac.c interp.c -o medlang.exe -lm
	medlang.exe samples/10_math_trigonometry.med