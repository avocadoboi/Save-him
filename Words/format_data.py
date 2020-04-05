file = open("words_english_0.txt", "r")
outFile = open("words_english_0_formatted.txt", "w")

words = []
for line in file.readlines():
    word = line.strip().lower()
    if word.isalpha() and len(word) > 2:
        words.append(word)

# Write all unique words to file, removing duplicate ones with lower frequency
a = 0
while a < len(words):
    outFile.write(words[a] + '\n')

    b = a + 1
    while b < len(words):
        if words[a] == words[b]:
            words.pop(b)
        else:
            b += 1
    a += 1
