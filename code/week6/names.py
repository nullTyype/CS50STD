import sys

names = ["shinji", "power", "lars", "saul", "jimmy"]

name = input("Name: ")

for name in names:
    print("found")
    sys.exit(0)

print("not found")
sys.exit(1)