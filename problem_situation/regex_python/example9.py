# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

#  Write a Python program that matches a string that has an 'a' followed 
# by anything, ending in 'b'.
def text_match(text):
        patterns = 'a.*?b$'
        if re.search(patterns,  text):
                return 'Found a match!'
        else:
                return 'Not matched!'

print(text_match("aabbbbd"))
print(text_match("aabAbbbc"))
print(text_match("accddbbjjjb"))