
height = [1,8,6,2,5,4,8,3,7]

maxi = 0
for i in range(len(height)):
            for j in range(i,len(height)):
                tmp = maxi
                maxi = max(maxi, min(height[i],height[j]) * j-i )
                if( tmp != maxi):
                    print("i = " + str(i) + " , j = " + str(j))

print(maxi)
