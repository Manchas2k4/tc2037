# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

# Write a Python program that matches a string that has an a followed 
# by zero or more b's
def text_match(text):
        patterns = 'ab*'
        if re.search(patterns,  text):
                return 'Found a match!'
        else:
                return 'Not matched!'

print(text_match("ac"))
print(text_match("abc"))
print(text_match("abbc"))
