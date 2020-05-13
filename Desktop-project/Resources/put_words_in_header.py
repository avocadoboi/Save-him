file = open("words_english_0.txt", "r")

outFile = open("Strings-upper.hpp", "w")

words = []
for line in file.readlines():
    word = line.strip().upper()
    if word.isalpha() and len(word) > 2:
        words.append(word)

outFile.write("inline char const* const words[] = \n{\n")

a = 0
while a < len(words):
    outFile.write("\t\"" + words[a] + "\",\n")

    b = a + 1
    while b < len(words):
        if words[a] == words[b]:
            words.pop(b)
        else:
            b += 1
    a += 1

outFile.write("}")
