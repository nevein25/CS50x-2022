from cs50 import get_int
# Prompot user for the height
height = get_int("Height: ")
# Make sure the height is from 1 to 8
while True:
    if height in range(1, 9):
        break
    else:
        height = get_int("Height: ")
        
# Main loop for the height
for i in range(height):
    for j in range(height-1, i, -1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print()