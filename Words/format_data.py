file = open("words_english_0.txt", "r")
outFile = open("words_english_0_formatted.txt", "w")

for line in file.readlines():
    word = line.strip().lower()
    if word.isalpha() and len(word) > 2:
        outFile.write(word + ",")
