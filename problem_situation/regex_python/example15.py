# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

str = """The advancements in biomarine studies franky@google.com with the investments necessary and Davos sinatra123@yahoo.com 
    Then The New Yorker article on wind farms..."""

# Write a regex so that the full email addresses are extracted.
regex = r'\S+@'
emails = re.findall(regex, str)
print(emails)