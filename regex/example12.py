# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

# Write a Python program that matches a word at the end of string, with 
# optional punctuation.
def text_match(text):
    patterns = '\w+\.?$'
    if re.search(patterns,  text):
            return 'Found a match!'
    else:
            return 'Not matched!'

print(text_match("The quick brown fox jumps over the lazy dog."))
print(text_match("The quick brown fox jumps over the lazy dog. "))
print(text_match("The quick brown fox jumps over the lazy dog "))