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

gcc -w -shared -o output/graph_func.dll output/graph_func.o
gcc -w -shared -o output/graph.dll output/graph.o -Loutput -lgraph_func
gcc -w -shared -o output/stack.dll output/stack.o -Loutput -lgraph_func
gcc -w -shared -o output/pathFinder.dll output/pathFinder.o -Loutput -lgraph_func -lstack

gcc -w -o output/main.exe output/main.o -Loutput -lgraph -lgraph_func -lpathFinder -lstack

cd output
del /Q *.o
cls
main.exe

pause
