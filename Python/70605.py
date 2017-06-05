#generators
def spell_word(chara):
  word=""
  for ch in chara:
    word+=ch
    yield word           #=return?
    
print(list(spell_word("wond")))
#--------------------------------------------------
#decorators - modify other functions
#--------------------------------------------------
for i in range(10):
  print()
#recursion
def factorial(x):
  if x==1 :
    return x
  else:
    return x*factorial(x-1)

print(factorial(5))
