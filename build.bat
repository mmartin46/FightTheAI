set arg = %1

if [%arg%] == ["build"] (
    g++ -I src/include -L src/lib -o main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    main.exe
)
else (
    git add .
    git commit -m "General Changes"
    git push -u origin
)
