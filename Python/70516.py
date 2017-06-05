print("test files")
fils=open("001.txt")
ContsOfFiles=fils.read()
print(ContsOfFiles)
print("the text has " + str(len(ContsOfFiles))  + " words dagai")
for i in range(3):
	print(fils.read(1))       # 因为之前已经被read过一次了，所以再次read输出会是空白
fils.close()
#-------------------------------------------------------
fils=open("nfile.txt","w")                 #在这里写上的文件名如果没有，会自己创建。但仅限于w mode
fils.write("aaaaaaaaaaaaaaaoooooooooooooeeeeeeeeeeeeeeeeeee")
fils.close()

fils=open("nfile.txt","r")
print(fils.read())
fils.close()
#-------------------------------------------------------
fils=open("nfile.txt","w")                 #若文件以w mode打开，其原来的内容会删掉
fils.write("谁说的")
fils.close()

fils=open("nfile.txt","r")
print(fils.read())
fils.close()
#-------------------------------------------------------
