GRAPHLEVEL=../../
ltest : LayoutTester.cpp
	g++ LayoutTester.cpp -std=c++11 -g -I $(GRAPHLEVEL) -lsfml-system -lsfml-window -lsfml-graphics -o ltest
redo:
	rm ltest
	make
	./ltest