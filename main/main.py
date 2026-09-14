operator = []
operand = []
# Apply PEMDAS

def endme ():
    operand[0] operator[0] operand[1]
    operand[2] oeprator[1] operand[3]
    operand[4] operator[2] operand[5] 
    result = operation[operator[0]](operand[0], operand[1]) 

def isoperator(string):
    if string in {'+', '-', '*', '/'}:
        global operator
        operator.append(string)
        return True
    else:
        return operator

string = input()
i = j = 0

while i < len(string):
    if (string[i].isdigit()):
        operand.append(string[i])
    elif (string[i] == '='):
        endme()
    elif (isoperator(string[i])):
        print('a')

    i += 1

print("Operands:") 
for x in operand:
    print(x)
print("Operators:")
for x in operator:
    print(x)
