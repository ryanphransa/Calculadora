operator = 0

def isoperator(temp):
    if temp in {'+', '-', '*', '/'}:
        global operator
        operator = temp
        return True
    else:
        return operator

temp = input()
i = j = 0
num = [0, 0]
while i < len(temp):
    if (temp[i].isdigit()):
        n = n * 10 + int(temp[i])
        num[j] = int(temp[i])
        j += 1
    elif (temp[i] == '='):
        if (isoperator(1) == '+'):
            print(num[0] + num[1])
        elif (isoperator(1) == '-'):
            print(num[0] - num[1])
        elif (isoperator(1) == '*'):
            print(num[0] * num[1])
        elif (isoperator(1) == '/'):
            print(num[0] / num[1])

    isoperator(temp[i])

    i = i + 1
