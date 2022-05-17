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
#extend euclidean gcd
def euclidean(a,b):
    if b == 0:
        return 1, 0, a
    else:
        s, t, gcd = euclidean(b, a%b)
        s, t = t, (s - (a//b) * t)
        return s, t, gcd


# In[4]:


#to find the inverse of e
def inverse(e,phi):
    a, b, gcd = euclidean(e, phi)
    return a%phi


# In[5]:


#The main function to do the RSA and also to be used in the Miller Rabin Test. Similar to pow(base,power,n) in python
def square_and_multiply(base, power, n):
    x = 1
    power = bin(power)[2:]
    for i in range(len(power)):
        x = (x ** 2) % n
        if power[i] == '1':
            x = (x * base) % n
    return x


# In[6]:


#The Miller Rabin Test to check whether the given number is prime or not
def miller_rabin_test(n, check = 40):
    #if can be divided by 2, it is not prime, used to accelerate the search of prime
    if n%2 == 0:
        return False
    
    #to write n-1 in the form (2^power)*multiplier
    power, multiplier = 0, n-1
    while multiplier%2 == 0:
        power += 1
        multiplier //= 2
    
    #check for reassurance
    for i in range(check):
        #pick a random number
        a = random.randrange(2,n-1)
        if a%2==0:
            a = random.randrange(2,n-1)
        #let x = a^s mod n
        x = square_and_multiply(a, multiplier, n)
        
        #if it is 1 or -1, then pick another number, else
        if x != 1 and x!= n-1:
            #loop x = x^2 % n. If x == n-1, return to the first loop
            for j in range(power-1):
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


#for production large prime of p and q (1024 bits probable prime)
def generate_primenum(bits = 1024):
    primenum = random.getrandbits(bits)
    #miller_rabin_test works for values above 3. If the random number is not prime, then find new values
    while miller_rabin_test(primenum) == False or primenum < 4:
        primenum = random.getrandbits(bits)
    return primenum


# In[8]:


#production of p, q, N, phi, e, d
def generate_key(bits = 1024):
    p = generate_primenum()
    q = generate_primenum()
    phi = (p-1) * (q-1)
    N = p * q
    
    e = random.randrange(phi)
    while gcd(e,phi) != 1:
        e = random.randrange(phi)
    d = inverse(e, phi)
    
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
def CRT_decrypt(ciphertext, p, q, d):
    decipher_p = d % (p-1)
    decipher_q = d % (q-1)
    q_inverse = inverse(q, p)
    
    cipher_bytes = int.from_bytes(base64.b64decode(ciphertext.encode('ascii')),"big")
    squaremultiply1 = square_and_multiply(cipher_bytes, decipher_p, p)
    squaremultiply2 = square_and_multiply(cipher_bytes, decipher_q, q)
    temp = (q_inverse* (squaremultiply1 - squaremultiply2)) % p
    cipher_int = squaremultiply2 + temp * q
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
        print(CRT_decrypt(sys.argv[2],int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5])))
