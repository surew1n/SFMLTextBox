tboxtest: tboxtest.cpp TextBox.cpp
	g++ tboxtest.cpp TextBox.cpp -o tboxtest -I/opt/homebrew/opt/sfml/include -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
	./tboxtest

clean:
	/bin/rm -f tboxtest
