# TODO
from cs50 import get_string
import re

def main():
    text = get_string("text: ")
    grade = setGrade(text)

    if grade >= 16:
        print("Grade 16+")

    elif grade <= 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {grade}")


def setGrade(text):
    # letter, words, and sentences definition;
    L = 0
    W = 1
    S = 0

    # iterates over each char, if matches pattern sets variables properly;
    for char in text:
        if re.search(r'([a-zA-Z])', char):
            L += 1
        elif re.search(r'[?!\.]', char):
            S += 1
        elif re.search(r'\s', char):
            W += 1

    # print(f"letters: {L}\nwords: {W}\nsentences: {S}")

    L = (L * 100) / W
    S = (S * 100 ) / W

    grade = round(0.0588 * L - 0.296 * S - 15.8)
    return grade


main()