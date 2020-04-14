from Crypto.Cipher import AES
key='1234567890123456'
aes=AES.new(key,AES.MODE_ECB)
print(aes.encrypt('wuyikoeidaisuki!'))

