import os

size = 0
for file in os.listdir("sprites//player/"):
    if file.endswith(".png"):
        size += 1
print(size)