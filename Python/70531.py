def runtwice(func,arg):       #func is the function who need to run twice
  return func(func(arg))
def add_5(x):
  return x+5
print(runtwice(add_5,10))
#---------------------------------------
triple=lambda x: x*3
add=lambda x,y:x+y
print(add(triple(3),4))
#---------------------------------------
nums=[11,22,33,44,55]
res=list(filter(lambda x:x%2==0,nums))
print(res)
