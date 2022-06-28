# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

str="""<div class="tut-list tut-list-new tut-row "> 
<div class="tut-list-primary"> <div class="tut-vote"> 
<video>intro</video> 
<span class="count">50</span> <span class="tut-upvotes-text hidden">Upvotes</span> </a> </div>  
<center>k="11" rel="nofollow"></center>
<span class="tutorial-title-txt">Automate the Boring Stuff with Python</span> 
<span class="tut-title-link">  <span class="js-tutorial" data-id="3529" 
title="Automate the Boring Stuff with Python" target="_blank">(udemy.com)</span>  
</span>  </a></div> <div class="action-footer">
<form class="save-tutorial-form" method="post" <button></button> </form>"""

# Find the html tags that are more than 4 letters.
regex = r'</([a-z]{5,})>'
data = re.findall(regex, str)
print(data)