# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

# Write a Python program to find sequences beginning with 
# upper letters joined with lower case letters by 
# an underscore.
def text_match(text):
    patterns = '^[A-Z]+_[a-z]+$'
    if re.search(patterns,  text):
        return 'Found a match!'
    else:
        return 'Not matched!'

print(text_match("aab_cbbbc"))
print(text_match("aab_Abbbc"))
print(text_match("Aaab_abbbc"))
print(text_match("AAAB_abbbc"))