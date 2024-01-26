import math
charConvertString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def convertNum(originalNum: str, originalRadix: int, newRadix: int) -> str:
    '''Given a string in a given radix, returns you the equivalent number
    value in the new radix with 5 digits after the floating point. Returns string "Error" if original
    string contains a digit not in the specified radix. Returned number is not rounded but cut-off.'''

    for char in originalNum:
        if char not in charConvertString[:originalRadix] and char != '.':
            return "Error"

    decimalVal = 0
    if "." not in originalNum:
        originalNum += '.'
    
    floatingPointIndex = originalNum.find('.')
    for i in range(0, len(originalNum)):
        if i == floatingPointIndex:
            continue
        
        decimalVal += charConvertString.find(originalNum[i]) * pow(originalRadix, (floatingPointIndex - (1 if i < floatingPointIndex else 0)) - i)
    
    currentDigitVal = 0
    outputString = ""

    while pow(newRadix, currentDigitVal) < decimalVal:
        currentDigitVal += 1
    currentDigitVal -= 1
    
    for i in range(currentDigitVal, -7, -1):
        outputString += charConvertString[math.floor(decimalVal/pow(newRadix, i))]
        decimalVal -= math.floor(decimalVal/pow(newRadix, i)) * pow(newRadix, i)

        if i == 0:
            outputString += '.'


    return outputString

