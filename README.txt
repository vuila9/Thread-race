Program author: John Nguyen (ID: 101162387)

Purpose: The program will create a GUI of a race track, the program will use multiple thread to operate multiple runners
         There will be dwarf-orc (dorc) stopping the runner, each dorc is also a separated thread
         All the thread will operate concurrently, the program will give wait call for thread that need to change some variable
         

Source: This zip file includes: README.txt, defs.h, main.c, initFunc.c, util.c, graphics.c, runnerGUI.c, dorcGUI.c, makefile

Header files:   string.h: for string usage (strcmp, strcpy)
                "defs.h": for struct initialization and functions declaration
                stdlib.h: for access to malloc(), calloc(), and free() tools
                 stdio.h: for output on console
             semaphore.h: for access to sem_wait, sem_post, sem_init;
                curses.h: for access to functions in graphics.c
                  time.h: for access to usleep()
               pthread.h: for access to pthread_join(), pthread_cancel()
                 
Launching Instruction:  open gnome-terminal on Ubuntu VM
                        redirect to the location where you have the file: defs.h, main.c, initFunc.c, util.c, 
                        graphics.c, runnerGUI.c, dorcGUI.c
                        
                        type "make a4" to create a combine file
                        type "./a4" to run the program
                        type "make valgrind" to run the program with valgrind (full)                       
