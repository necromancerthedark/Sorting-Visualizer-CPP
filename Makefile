build:
	g++ -Wfatal-errors \
	main.cpp \
	-I"C:\TDM-GCC-64\sdlfiles\SDL2-2.0.10\x86_64-w64-mingw32\include" \
	-L"C:\TDM-GCC-64\sdlfiles\SDL2-2.0.10\x86_64-w64-mingw32\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-o SortingViz.exe
