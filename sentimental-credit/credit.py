# get the number of the credit from the user
number = int(input("please enter the number of the credit card: "))
# getting the second-to-last digit
i = number // 10
# some variables we will use in the sum
counter = 0
sum = 0
first = 0
second = 0
# Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
while i > 0:
    last_num = i % 10
    counter += 1
    last_num = last_num * 2
    if last_num >= 10:
        second = last_num // 10
        first = last_num % 10
        sum = first + sum + second
        i = i // 100
        continue
    sum = last_num + sum
    i = i // 100
# Add the sum to the sum of the digits that weren’t multiplied by 2.

i = number
while i > 0:
    last_num = i % 10
    counter += 1
    sum = last_num + sum
    i = i // 100
# check for card length and starting digits
result1 = number // 10000000000000
result2 = number // 100000000000000
result3 = number // 1000000000000
result4 = number // 1000000000000000

if sum % 10 == 0:
    # American Express uses 15-digit numbers,All American Express numbers start with 34 or 37
    if (counter == 15 and (result1 == 34 or result1 == 37)):
        print("AMEX")
    # MasterCard uses 16-digit numbers,MasterCard numbers start with 51, 52, 53, 54, or 55
    elif (counter == 16 and (result2 == 51 or result2 == 52 or result2 == 53 or result2 == 54 or result2 == 55)):
        print("MASTERCARD")
    # Visa uses 13,all Visa numbers start with 4
    elif ((counter == 13) and (result3 == 4)):
        print("VISA")
    # Visa uses 16,all Visa numbers start with 4
    elif ((counter == 16) and (result4 == 4)):
        print("VISA")
    # if the other conditions not true then the card is invalid
    else:
        print("INVALID")
# if the total modulo 10 is not congruent to 0
else:
    print("INVALID")
