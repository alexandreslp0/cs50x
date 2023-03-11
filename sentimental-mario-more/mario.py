def main():
    height = get_int()
    for i in range(height):
        block = (i + 1) * "#"
        print((height - 1 - i) * " " + block + "  " + block)


def get_int():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                return height
        except ValueError:
            print("Not a valid height")


main()