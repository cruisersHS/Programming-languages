#string format
num=[4,5,6]
message="Numbers: {0} {1} {2}". format(num[0], num[1], num[2])
print(message)
#------------------------------------------------------------------------
print(", ".join(["spam", "eggs", "ham"]))
#prints "spam, eggs, ham"

print("Hello ME".replace("ME", "world"))
#prints "Hello world"

print("This is a sentence.".startswith("This"))
# prints "True"

print("This is a sentence.".endswith("sentence."))
# prints "True"

print("This is a sentence.".upper())
# prints "THIS IS A SENTENCE."

print("AN ALL CAPS SENTENCE".lower())
#prints "an all caps sentence"

print("spam, eggs, ham".split(", "))
#prints "['spam', 'eggs', 'ham']"
#------------------------------------------------------------------------
#all, any, enumerate argument
num1=[11,22,33,44,55]
if all([i>10 for i in num1]):
  print("all are bigger than 10")
if any([i%2==0 for i in num1]):
  print("al least an oven")
for v in enumerate(num1):
  print(v)
nu2=[1,1,1,1,1,1,1,1,1,1,1,1,2,32,23,3,2,2,23,3,22,334]
for s in enumerate(nu2):
  print(s)
#------------------------------------------------------------------------
