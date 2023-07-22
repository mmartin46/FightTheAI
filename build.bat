set arg = %1

@REM if (%arg% == "build") (
@REM     g++ -I src/include -L src/lib -o main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
@REM     main.exe
@REM ) 

@REM if (%arg% == "save") (
@REM     git add .
@REM     git commit -m "General Changes"
@REM     git push -u origin
@REM )

    g++ -I src/include -L src/lib -o main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    main.exe