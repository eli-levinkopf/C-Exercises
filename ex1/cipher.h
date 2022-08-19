
#ifndef CIPHER
#define CIPHER
#define ALPHABET_SIZE 26

/**
 * Encrypts text
 * @param p Pointer to string for encryption
 * @param k Encryption key
 */
void encode (char *p, int k);

/**
 * Decrypts text
 * @param p Pointer to string for decryption
 * @param k Decryption key
 */
void decode (char *p, int k);

void encode (char *p, int k)
{
  int i = 0;
  if (k < 0)
    {
      k = k % ALPHABET_SIZE + ALPHABET_SIZE;
    }
  while (p[i] != '\0')
    {
      if (p[i] >= 'a' && p[i] <= 'z')
        {
          p[i] = (char)((p[i] + (k - 'a')) % ALPHABET_SIZE + 'a');
        }
      if (p[i] >= 'A' && p[i] <= 'Z')
        {
          p[i] = (char)((p[i] + k - 'A') % ALPHABET_SIZE + 'A');
        }
      i++;
    }
}


void decode (char *p, int k)
{
  encode (p, -k);
}

#endif