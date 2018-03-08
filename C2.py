def init(i,j):
    return .5 +((i+j)%50 - 30)/50.0

def z_1(i):
    tot = 0
    for j in range(50176):
       w = init(i,j)
       x = init(j,1)
       tot += w*x
    z = max(0, tot)
    return(z)

def z_2(i):
    tot = 0
    for j in range(4000):
        print(j)
        w = init(i,j)
        x = z_1(j)
        tot += w*x
    z = max(0, tot)
    return(z)

def main():

    checksum = 0
    for i in range(1000):
        print(i)
        checksum += z_2(i)

    print("CHECKSUM {%.2f}".format(checksum))

if __name__ == "__main__":
    main()
