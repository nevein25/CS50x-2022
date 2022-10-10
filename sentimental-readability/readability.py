from cs50 import get_string


def main():
    # Get input text from the user
    text = get_string("Enter text: ")

    # Count number of letters
    letters = count_letters(text)
    # Count sentences
    sentences = count_sentences(text)
    # Count words
    words = count_words(text)
    # Count the grade
    grade = count_grade(letters, sentences, words)

    # Print the grade
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    counter = 0
    for i in text:
        if i.isalpha():
            counter = counter + 1
    return counter


def count_sentences(text):

    countPeriod = text.count(".")
    countQuMark = text.count("?")
    countExclaMark = text.count("!")

    return countQuMark + countPeriod + countExclaMark


def count_words(text):

    return text.count(" ") + 1


def count_grade(letters, sentences, words):
    S = (sentences / words) * 100.0
    L = (letters / words) * 100.0
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)


main()