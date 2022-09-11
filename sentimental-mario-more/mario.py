# take the height from the user
# reject this input as invalid, as by re-prompting the user to type in another number.
flag = True
while flag:
    try:
        tall = int(input("height:"))
        if not tall <= 0 or tall > 8:
            flag = False
    except ValueError:
        continue

while True:
    if tall <= 0 or tall > 8:
        tall = int(input("height:"))
        continue
    else:
        break
# the outer loop is for the rows
# the inner loop is for the columns
for i in range(1, tall + 1):
    for j in range(1, 11 + i):
        if (j > tall - i) and (j <= tall):
            print("#", end="")
            continue
        if (j > tall + 2) and (j <= tall + 2 + i):
            print("#", end="")
            continue
        if j <= tall + 2:
            print(" ", end="")
    print()