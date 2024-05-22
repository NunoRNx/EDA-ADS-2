cd src
del /Q output\*.o
del /Q output\*.lib
del /Q output\*.dll
del /Q output\*.exe

gcc -w -c graph_func.c -o output/graph_func.o
gcc -w -c graph.c -o output/graph.o
gcc -w -c main.c -o output/main.o
gcc -w -c pathFinder.c -o output/pathFinder.o
gcc -w -c stack.c -o output/stack.o

ar rcs output/graph_func.lib output/graph_func.o
ar rcs output/graph.lib output/graph.o
ar rcs output/pathFinder.lib output/pathFinder.o
ar rcs output/stack.lib output/stack.o

gcc -w -o output/main.exe output/main.o -Loutput -l:graph.lib -l:graph_func.lib -l:pathFinder.lib -l:stack.lib

cd output
del /Q *.o
cls
main.exe

pause
