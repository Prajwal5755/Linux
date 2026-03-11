n=int(input())
a=0
b=1
c=0

if n==1:
    print(0)


if n<3:
    print(a+b)

else:
    for i in range(n):
        c=a+b
        a=b
        b=c

        print(c)


    
