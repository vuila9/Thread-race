LIBS = -lpthread -lncurses

a4:		main.c initFunc.c graphics.c runnerGUI.c dorcGUI.c util.c defs.h
		gcc -o a4 main.c initFunc.c graphics.c runnerGUI.c dorcGUI.c util.c defs.h $(LIBS)
			
valgrind:	a4
		valgrind --leak-check=full ./a4

