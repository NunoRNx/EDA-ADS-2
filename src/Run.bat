cd src

gcc -w -c graph_func.c -o output\graph_func.o
gcc -w -c graph.c -o output\graph.o
gcc -w -c main.c -o output\main.o
gcc -w -c pathFinder.c -o output\pathFinder.o

gcc -w -shared -o output\graph_func.dll output\graph_func.o
gcc -w -shared -o output\graph.dll output\graph.o -Loutput -lgraph_func
gcc -w -shared -o output\pathFinder.dll output\pathFinder.o -Loutput -lgraph_func

gcc -w -o output\main.exe output\main.o -Loutput -lgraph -lgraph_func -lpathFinder

cd output



main.exe

pause

cd output

main.exe

pause
