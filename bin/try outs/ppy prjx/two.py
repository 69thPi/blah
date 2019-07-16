while 1:
    x=int(input("enter a number to check = "))
    flag=0
    """for i in range(2,x):
        for j in range(2,i):
            if i%j==0:
                break
        else:
           print(i)#prints prime nos"""
    for i in range(2,x):
        if x%i==0:
          print(x,"isnt prime",i,"*",x//i,"=",x)
          break
    else:
       print(x,"is prime")

    c=input("terminate = ")
    if c in('y','Y','yes','Yes','YES'):
      print("end")
      break;
