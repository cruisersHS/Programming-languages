#2017.5.23
#Tuples - like list, but cant be changed
word=("one","two","ein","zwei")
print(word[2])
#------------------------------------------------
a=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,1223]
print(a[0:5])
print(a[7:9])              #range
print(a[3:])
print(a[1:13:3])
print(a[15:10:-1])
print(a[::-1])
#------------------------------------------------
evennums=[i**2 for i in range(10) if i**2%2==0]
print(evennums)
