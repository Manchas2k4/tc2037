# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

str = """Some of the prices were as following TSLA:749.50, ORCL: 50.50, GE: 10.90, MSFT: 170.50, BIDU: 121.40. 
         As the macroeconomic developments continue we will update the prices. """

# You are given stock prices for related financial tickers. (Symbols 
# representing companies in the stock market). Find a way to extract the 
# tickers mentioned in the report.
regex = r'[A-Z]{2,}'
data = re.findall(regex, str)
print(data)
