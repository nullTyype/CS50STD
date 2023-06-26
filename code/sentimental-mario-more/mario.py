# TODO
from cs50 import get_int

height = 0
while height < 1 or height > 8:
    height = get_int("height: ")

spaces = height - 1
increment = 1
while spaces >= 0:
    print(spaces * " " + "#" * increment + 2 * " " + increment * "#" , end="\n")
    increment += 1
    spaces -= 1
