import random

class RSA:
    alphabet1 = "abcdefghijklmnopqrstuvwxyz"
    alphabet2 = ".,?! \t\n\rabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    print("Alphabet2:", len(alphabet2))

    def ToBase10(self, alphabet, number):
        b = len(alphabet)
        x = 0
        for character in number:
            v = alphabet.find(character)
            if v != -1:
                x = x * b + v
        return x

    def FromBase10(self, alphabet, number):
        base = len(alphabet)
        result = ""
        while number > 0:
            result = alphabet[number % base] + result
            number //= base
        if result == "":  # Handle case when number is 0
            return alphabet[0]
        return result

    def miller_test2(self, n):
        if n <= 2 or n % 2 == 0:
            return False
        s = 0
        t = n - 1
        while t % 2 == 0:
            s += 1
            t //= 2
        b = random.randrange(2, n - 1)
        x = pow(b, t, n)
        if x == 1 or x == n - 1:
            return True
        for i in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                return True
        return False

    def miller_prime(self, n):
        for i in range(10):
            if not self.miller_test2(n):
                return "Not Prime"
        return "Prime"

    def GCD(self, a, b):
        while b != 0:
            a, b = b, a % b
        return a

    def FindInverse(self, a, n):
        t, newt = 0, 1
        r, newr = n, a
        while newr != 0:
            quotient = r // newr
            t, newt = newt, t - quotient * newt
            r, newr = newr, r - quotient * newr
        if r > 1:
            raise Exception("a is not invertible")
        if t < 0:
            t += n
        return t

    def GenerateKeys(self, string1, string2):
        # Convert strings to base 10 using alphabet1
        p = self.ToBase10(self.alphabet1, string1)
        q = self.ToBase10(self.alphabet1, string2)
        
        # Check if p or q is less than 10^200
        if p < 10**200 or q < 10**200:
            print("Error: input strings are too short to generate 200-digit primes.")
            return False
        
        # Mod by 10^200 to ensure they're not too long
        p = p % (10**200)
        q = q % (10**200)
        
        # Make them odd if they were even
        if p % 2 == 0:
            p += 1
        if q % 2 == 0:
            q += 1
        
        print("P length:", len(str(p)))
        print("Q length:", len(str(q)))
        
        # Find the next prime numbers for p and q
        max_attempts = 1000
        attempts = 0
        
        while self.miller_prime(p) == "Not Prime" and attempts < max_attempts:
            p += 2
            attempts += 1
        
        attempts = 0
        while self.miller_prime(q) == "Not Prime" and attempts < max_attempts:
            q += 2
            attempts += 1
        
        print("P prime:", self.miller_prime(p))
        print("Q prime:", self.miller_prime(q))
        
        # Verify we found prime numbers
        if self.miller_prime(p) != "Prime" or self.miller_prime(q) != "Prime":
            print("Error: could not find suitable prime numbers after maximum attempts.")
            return False
        
        # Calculate n and r
        n = p * q
        r = (p - 1) * (q - 1)
        
        # Find e - a 398 digit number that is relatively prime with r
        e = 10**398 + 1
        while self.GCD(e, r) != 1:
            e += 2
        
        # Find d - the inverse of e mod r
        d = self.FindInverse(e, r)
        
        # Save public key
        with open("public.txt", "w") as pub:
            pub.write(str(n) + "\n")
            pub.write(str(e) + "\n")
        
        # Save private key
        with open("private.txt", "w") as priv:
            priv.write(str(n) + "\n")
            priv.write(str(d) + "\n")
        
        return True

    def Encrypt(self, input_file, output_file):
        # Read public key
        with open("public.txt", "r") as f:
            n = int(f.readline().strip())
            e = int(f.readline().strip())
        
        # Read input file in binary mode and convert to text
        with open(input_file, "rb") as fin:
            plaintext_binary = fin.read()
            plaintext = plaintext_binary.decode("utf-8")
        
        # Break plaintext into blocks of 216 characters
        max_chars = 216
        blocks = [plaintext[i:i + max_chars] for i in range(0, len(plaintext), max_chars)]
        
        result = ""
        for block in blocks:
            # Convert block to base 10
            base10 = self.ToBase10(self.alphabet2, block)
            
            # Encrypt using RSA formula: C = M^e mod n
            encrypted = pow(base10, e, n)
            
            # Convert encrypted number back to base 70 (alphabet2)
            encrypted_text = self.FromBase10(self.alphabet2, encrypted)
            
            # Add block separator
            result += encrypted_text + "$"
        
        # Write to output file in binary mode
        with open(output_file, "wb") as fout:
            fout.write(result.encode("utf-8"))

    def Decrypt(self, input_file, output_file):
        # Read private key
        with open("private.txt", "r") as f:
            n = int(f.readline().strip())
            d = int(f.readline().strip())
        
        # Read encrypted file in binary mode
        with open(input_file, "rb") as fin:
            encrypted_binary = fin.read()
            encrypted_text = encrypted_binary.decode("utf-8")
        
        # Split into blocks using $ as separator
        blocks = encrypted_text.split('$')
        
        result = ""
        for block in blocks:
            if block == "":
                continue
            
            # Convert encrypted block from base 70 to base 10
            base10 = self.ToBase10(self.alphabet2, block)
            
            # Decrypt using RSA formula: M = C^d mod n
            decrypted = pow(base10, d, n)
            
            # Convert decrypted number back to base 70 (alphabet2)
            decrypted_text = self.FromBase10(self.alphabet2, decrypted)
            
            result += decrypted_text
        
        # Write to output file in binary mode
        with open(output_file, "wb") as fout:
            fout.write(result.encode("utf-8"))


def main():
    rsa = RSA()
    
    # Create long strings for key generation
    string1 = "ajdhfdbjdajddajlkdjafkdjasidjfkalsdnfklasnfklnjkcnkandkfnaisidurfioayrthfaksfljdnsadkfjdsagnbjnbdshjifflsngdffdsajbjkaadfnjfkdsjasknkcnasdifndskanfgnasjsdkfjdsklbfnjdsbfjdsaihfduahfdjafnsdhjfhjkahjsdf"
    string2 = "ajdfahfddhkafjasdfjkdsjgifjwiorutioruetyieruwhtejbnfmcnbvmzcxbjhfsadhryuiwtyfshgjbcnxzbvnmzbmvsfgjriuwtsiosthfgjnvcxmnvjkfdhasiurtehfjgkncvxzmmdjahfrudbnvcxjdfhursifhasdbjxcvnnjkfdashusefdhsjcxvnkjdfs"
    
    # Generate keys
    success = rsa.GenerateKeys(string1, string2)
    
    if not success:
        print("Key generation failed. Cannot proceed with encryption/decryption.")
        return
    
    # Create a plaintext file with more than 216 characters
    with open("plain.txt", "w") as f:
        f.write("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" * 12)
    
    # Encrypt and decrypt
    rsa.Encrypt("plain.txt", "cipher.txt")
    rsa.Decrypt("cipher.txt", "decrypted.txt")
    
    # Verify the result
    with open("plain.txt", "r") as f1, open("decrypted.txt", "r") as f2:
        plain_text = f1.read()
        decrypted_text = f2.read()
        if plain_text == decrypted_text:
            print("Success: Decrypted text matches original!")
        else:
            print(f"Error: Mismatch between decrypted and original text.")
            print(f"Plain text length: {len(plain_text)}")
            print(f"Decrypted text length: {len(decrypted_text)}")


if __name__ == '__main__':
    main()