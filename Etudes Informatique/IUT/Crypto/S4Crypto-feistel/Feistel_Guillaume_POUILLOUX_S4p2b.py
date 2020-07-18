#######################################################################################################################################
# Guillaume POUILLOUX - S4p2b - DUT Informatique - IUT Bordeaux 1																	  #
#																																	  #
# S4_Crypto - Implementation d'un reseau de Feistel																					  #
#																																	  #
# Le programme execute l'algo en fonction du nombre de rondes consecutives															  #
# La fonction d'encryption est relativement simple (xor entre le sous-bloc et la sous-cle)								              #
#######################################################################################################################################

import sys

class FeistelNetwork:

	# n is the block's length we will encrypt/decrypt
	# keyLength is the key's length
	# r is the number of rounds
    def __init__(self,n=64,keyLength=32,rounds=4):
		self.n=n
		self.keyLength=keyLength
		self.rounds=rounds
		
		self.l = []
		self.r = []
		self.key = []
		
		# here we are initializing our block but we assume it should be given as an argument (file as sys.argv..)
		self.bloc = []
		for i in range(0, n/2):
			self.bloc.append(0)
		for i in range(n/2, n):
			self.bloc.append(1)
			
		for i in range(0, n/2):
			self.l.append(self.bloc[i])
		for i in range(n/2, n):
			self.r.append(self.bloc[i])
		
		# define the key / could define a tricky key here ... ;-)
		for i in range(0, keyLength):
			if((i*i)%keyLength/self.rounds == 0):
				self.key.append(0)
			else:
				self.key.append(1)

	# define the XOR function - we assume we have the same size for both lists
    def xor(self, a, b):
		ret = []
		for i in range(len(a)):
			ret.append(a[i] ^ b[i])
		return ret

    # define the encrypt function - in fact, it's an XOR between the subblock and the subkey here..
    def fun_encrypt(self, sub_block,index):
	    for i in xrange(0,len(sub_block)):
			sub_block[i] = sub_block[i] ^ self.subkeys[index][i%len(self.subkeys[index])]
	    return sub_block

	# generate 'l' subkeys from the global key
    def generateSubKeys(self, l):
		self.subkeys = []
		subkeys_length = len(self.key)/l
				
		for i in range(0, l):
			tmp = []
			for j in range(i*l, (i*l)+subkeys_length):
				tmp.append(self.key[j])
			self.subkeys.append(tmp)
		
	# definition of what we do during a round
    def round2(self, l0, r0, i):
		l1 = r0
		r1 = self.xor(l0, self.fun_encrypt(r0, i))
		return(l1,r1)
		
	# This function repeats the rounds and return the encrypted message
    def encrypt(self):
        for i in xrange(self.rounds):
		    self.l,self.r = self.round2(self.l, self.r, i)
        return self.l + self.r
     
    # useful to track left and right parts before and after the encryption process
    def to_string(self):
		print 'Le bloc est : '
		print self.bloc
		print '-----------------'
		
		print 'La partie L est : '
		print self.l
		print '-----------------'
		  
		print 'La partie R est : '
		print self.r
		print '-----------------'
		
		print 'La cle est : '
		print self.key
		print '-----------------'
		
		print 'Les sous-cles sont : '
		print self.subkeys
		print '-----------------'


def main(argv):
	fn = FeistelNetwork()
	fn.generateSubKeys(fn.rounds)
	fn.to_string()
	print 'Le bloc crypte est :'
	print fn.encrypt()
	fn.to_string()
	
if __name__ == '__main__':
    main(sys.argv)
