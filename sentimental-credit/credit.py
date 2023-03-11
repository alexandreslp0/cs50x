from math import log10


def main():
    card_number = get_card_number()
    card_number_str = str(card_number)
    if (13 <= len(card_number_str) <= 16) and check_card_number_sintax(card_number_str):
        check_card(card_number_str)
    else:
        print("INVALID")


def get_card_number():
    while True:
        try:
            card_number = int(input("Credit card number: "))
            return card_number
        except ValueError:
            print("Not a valid card number.")


def check_card_number_sintax(card_number_str):
    count = 0
    lenght = len(card_number_str)
    for i in range(lenght):
        # getting every other digit, starting with the number’s second-to-last digit
        digit = int(card_number_str[lenght - 1 - i])
        if (i % 2) != 0:
            double_digit = digit * 2
            if double_digit > 9:
                count += int(str(double_digit)[0]) + int(str(double_digit)[1])
            else:
                count += double_digit
        else:
            count += digit

    if count % 10 == 0:
        return True
    else:
        return False


def check_card(card_number_str):
    if card_number_str[:2] in ["34", "37"]:
        print("AMEX")
    elif card_number_str[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    elif card_number_str[0] == "4":
        print("VISA")
    else:
        print("INVALID")


main()