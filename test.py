def binary_search(a, x): 
    start = 0 
    end = len(a) - 1; 
    while start<=end: 
        mid = (start+end)//2 
        print(start,mid,end) 
        
        if x==a[mid]: 
            return mid 
        elif x>a[mid]: 
            start = mid+1 
        else: 
            end = mid-1 
        
    return -100 

d = [1,4,9,16,25,36,59,64,81] 
print(d) 
print(binary_search(d,36))