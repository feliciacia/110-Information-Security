#!/usr/bin/env python
# coding: utf-8

# In[1]:


import sys #to do argc/argv in python
import random #for rng
import base64 #for converting between binary and base64
sys.setrecursionlimit(100000) #setting the recursion limit to be greater so that deeper recursions still can run


# In[2]:


#for finding the gcd between a and b
def gcd(a,b):
    if a == 0:
        return b
    if b == 0:
        return a
    if a == b:
        return a
    if a > b:
        return gcd(a%b,b)
    return gcd(a,b%a)


# In[3]:


#to find not only the gcd, but also Bezout's Identity (sa + bt = gcd(a,b))
def extend_gcd(a,b):
    if b == 0:
        return 1, 0, a
    else:
        s, t, gcd = extend_gcd(b, a%b)
        s, t = t, (s - (a//b) * t)
        return s, t, gcd


# In[4]:


#to find the inverse of e
def invert(e,phi):
    x, y, gcd = extend_gcd(e, phi)
    return x%phi


# In[5]:


#The main function to do the RSA and also to be used in the Miller Rabin Test. Similar to pow(x,h,n) in python
def square_and_multiply(x, h, n):
    y = 1
    h = bin(h)[2:]
    for i in range(len(h)):
        y = (y ** 2) % n
        if h[i] == '1':
            y = (y * x) % n
    return y


# In[6]:


#The Miller Rabin Test to check whether the given number is prime or not
def miller_rabin_test(n, repeat = 70):
    #if can be divided by 2, it is not prime, used to accelerate the search of prime
    if n%2 == 0:
        return False
    
    #to write n-1 in the form (2^r)*s
    r, s = 0, n-1
    while s%2 == 0:
        r += 1
        s //= 2
    
    #repeat for reassurance
    for i in range(repeat):
        #pick a random number
        a = random.randrange(2,n-1)
        if a%2==0:
            a = random.randrange(2,n-1)
        #let x = a^s mod n
        x = square_and_multiply(a, s, n)
        
        #if it is 1 or -1, then pick another number, else
        if x != 1 and x!= n-1:
            #loop x = x^2 % n. If x == n-1, return to the first loop
            for j in range(r-1):
                if x == n-1:
                    break
                x = (x**2)%n
                if x == 1:
                    return False
            #it is composite (not prime)
            if x!=n-1:
                return False
    return True


# In[7]:


#for production of p and q (1024 bits probable prime)
def produce_big_prime(bits = 1024):
    b_prime = random.getrandbits(bits)
    #miller_rabin_test works for values above 3. If the random number is not prime, then find new values
    while miller_rabin_test(b_prime) == False or b_prime < 4:
        b_prime = random.getrandbits(bits)
    return b_prime


# In[8]:


#production of p, q, N, phi, e, d
def produce_key(bits = 1024):
    p = produce_big_prime()
    q = produce_big_prime()
    phi = (p-1) * (q-1)
    N = p * q
    
    e = random.randrange(phi)
    while gcd(e,phi) != 1:
        e = random.randrange(phi)
    d = invert(e, phi)
    
    return p, q, N, phi, e, d


# In[9]:


#convert the given plaintext, assumed 8-bit, to numerical value so that it can encrypted
def encrypt(plaintext, N, e):
    plaintext_int = 0
    for c in plaintext:
        plaintext_int *= 256
        plaintext_int += ord(c)
    cipher = ""
    cipher_int = square_and_multiply(plaintext_int, e, N)
    #write the value as 256 byte
    cipher_bytes = cipher_int.to_bytes(256,"big")
    return str(base64.b64encode(cipher_bytes))[2:-1]


# In[10]:


#convert the given ciphertext (base64 written as string) to the plaintext
def decrypt(ciphertext, N, d):
    cipher_bytes = int.from_bytes(base64.b64decode(ciphertext.encode('ascii')),"big")
    cipher_int = square_and_multiply(cipher_bytes, d, N)
    ans = ""
    while cipher_int%256!=0:
        ans = str(chr(cipher_int%256)) + ans
        cipher_int = cipher_int // 256
    return ans


# In[11]:


#decipher using chinese remainder theorem
def decrypt_with_CRT(ciphertext, p, q, d):
    dp = d % (p-1)
    dq = d % (q-1)
    q_inverse = invert(q, p)
    
    cipher_bytes = int.from_bytes(base64.b64decode(ciphertext.encode('ascii')),"big")
    m1 = square_and_multiply(cipher_bytes, dp, p)
    m2 = square_and_multiply(cipher_bytes, dq, q)
    h = (q_inverse* (m1 - m2)) % p
    cipher_int = m2 + h * q
    ans = ""
    while cipher_int%256!=0:
        ans = str(chr(cipher_int%256)) + ans
        cipher_int = cipher_int // 256
    return ans


# In[12]:


#main function
if __name__ == "__main__":
    if sys.argv[1] == "-i":
        p, q, N, phi, e, d = produce_key()
        print("p = " + str(p))
        print("q = " + str(q))
        print("N = " + str(N))
        print("phi = "+ str(phi))
        print("e = " + str(e))
        print("d = " + str(d))
    if sys.argv[1] == "-e":
        print(encrypt(sys.argv[2], int(sys.argv[3]), int(sys.argv[4])))
    if sys.argv[1] == "-d":
        print(decrypt(sys.argv[2], int(sys.argv[3]), int(sys.argv[4])))
    if sys.argv[1] == '-CRT':
        print(decrypt_with_CRT(sys.argv[2],int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5])))

