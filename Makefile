run:
	g++ -I src/include -L src/lib -o main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	./main


save:
	git add .
	git commit -m "$(message)"
	git push -u origin