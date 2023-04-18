# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

str = """
>Venues
>Marketing
>medalists
>Controversies
>Paralympics
>snowboarding
>[1]
>Netherlands
>[2]
>Norway
>[10]
>[11]
>References
>edit
>[12]
>Norway
>Germany
>Canada
>Netherlands
>Japan
>Italy
>Belarus
>China
>Slovakia
<$#%#$%
<#$#$$
<**&&^^
>Slovenia
>Belgium
>Spain
>Kazakhstan
>[15]
>1964
>1968
>1972
>1992
>1996
>2000"""

# Keep only the lines that start with a number or a letter after > sign.
data = re.findall('>\w+', str)
print(data)