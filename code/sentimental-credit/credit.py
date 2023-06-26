# TODO
from cs50 import get_string
import re

def main():
    card = ""
    # ensure proper usage;
    while not card.isdigit():
        card = get_string("Number: ")

    if isValid(card):
        checkCard(card)
    else:
        print("INVALID")

def isValid(card):
    # starts from second-to-last digit of card;
    index = -2
    digits = []
    # the loop iterates over even index digits from second-to-last appending values to digits list
    # until reach it's final (or almost, if length is odd then forces to append the first digit);
    while (index * -1) <= len(card):
        if (int(card[index]) * 2) > 9:
            digits.append(str(int(card[index]) * 2)[0])
            digits.append(str(int(card[index]) * 2)[1])
        else:
            digits.append(str(int(card[index]) * 2))
        digits.append(card[index+1])

        index += -2

    # if length of card is odd, add final digit to digits;
    if len(card) % 2 != 0:
        digits.append(card[0])

    sum = 0
    for number in digits:
        sum += int(number)

    if sum % 10 == 0:
        return True
    else:
        return False


# check if card matches any of standard card patterns
def checkCard(card):
    visaPattern = r'^4\d{12}(?:\d{3})?$'
    masterPattern = r'^5[1-5]\d{14}$'
    amexPattern = r'^3[3|7]\d{13}$'

    if re.search(visaPattern, card):
        print("VISA")
    elif re.search(masterPattern, card):
        print("MASTERCARD")
    elif re.search(amexPattern, card):
        print("AMEX")
    else:
        print("INVALID")


main()