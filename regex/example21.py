# https://cheatography.com/davechild/cheat-sheets/regular-expressions/
import re

str="""
#include <iostream>

using namespace std;

void pow(double x, int n, double &result) {
  result = 1;
  for (int i = 1; i <= n; i++) {
    result *= x;
  }
}

double pow(double x, int n) {
  double result = 1;
  for (int i = 1; i <= n; i++) {
    result *= x;
  }
  return result;
}

int main(int argc, char* argv[]) {
  double result;

  pow(10, 2, result);
  cout << "Result = " << result << "\n";
  result = pow(10, 2);
  cout << "Result = " << result << "\n";
  return 0;
}
"""

# Find the html tags that are more than 4 letters.
regex = r'</([a-z]{5,})>'
data = re.findall(regex, str)
print(data)