/**
 * \file md5.cpp
 * \brief MD5 class implementation.
 *
 * \author Frank Thilo (thilo         @unix-ag.org)
 * \date Created: 1991
 * \date Last modified: Insert modification date
 *
 * This file contains the implementation of the MD5 class, converted from
 * the reference implementation of RFC 1321 by RSA Data Security, Inc.
 *
 * The original implementation was based on md5.h and md5.c.
 *
 * \see http://www.bzflag.org
 */

/**
 * \class MD5
 * \brief Implementation of the MD5 Message-Digest Algorithm.
 *
 * This class provides methods to calculate MD5 hashes for strings or byte arrays.
 * It is based on the reference implementation of RFC 1321 by RSA Data Security, Inc.
 *
 * \note This implementation is not intended for speed or security.
 *
 * \copyright Copyright (C) 1991-2, RSA Data Security, Inc. All rights reserved.
 * \license License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest Algorithm" in all
 * material mentioning or referencing this software or this function.
 * License is also granted to make and use derivative works provided that such works
 * are identified as "derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm"
 * in all material mentioning or referencing the derived work.
 * RSA Data Security, Inc. makes no representations concerning either the merchantability
 * of this software or the suitability of this software for any particular purpose.
 * It is provided "as is" without express or implied warranty of any kind.
 *
 * \note These notices must be retained in any copies of any part of this documentation and/or software.
 */

#include "md5.h"

// Implementation of MD5 methods follows here


#define _CRT_SECURE_NO_WARNINGS

/* interface header */
#include "md5.h"

/* system implementation headers */
#include <stdio.h>

#include <cstdio>
#include "definitions.h"


///////////////////////////////////////////////

/**
 * \brief F function in the MD5 algorithm.
 *
 * F, G, H, and I are basic MD5 functions defined in RFC 1321.
 *
 * \param x First input.
 * \param y Second input.
 * \param z Third input.
 * \return Result of the F function computation.
 */
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z)
{
    return (x & y) | (~x & z);
}

/**
 * \brief G function in the MD5 algorithm.
 *
 * \param x First input.
 * \param y Second input.
 * \param z Third input.
 * \return Result of the G function computation.
 */
inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z)
{
    return (x & z) | (y & ~z);
}

/**
 * \brief H function in the MD5 algorithm.
 *
 * \param x First input.
 * \param y Second input.
 * \param z Third input.
 * \return Result of the H function computation.
 */
inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z)
{
    return x ^ y ^ z;
}

/**
 * \brief I function in the MD5 algorithm.
 *
 * \param x First input.
 * \param y Second input.
 * \param z Third input.
 * \return Result of the I function computation.
 */
inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z)
{
    return y ^ (x | ~z);
}

/**
 * \brief Rotate left operation.
 *
 * rotate_left rotates x left by n bits.
 *
 * \param x Value to rotate.
 * \param n Number of bits to rotate by.
 * \return Rotated value.
 */
inline MD5::uint4 MD5::rotate_left(uint4 x, int n)
{
    return (x << n) | (x >> (32 - n));
}


/**
 * \brief FF transformation for MD5 round.
 *
 * FF transformation for MD5 round 1.
 *
 * \param a Reference to state variable A.
 * \param b Input variable B.
 * \param c Input variable C.
 * \param d Input variable D.
 * \param x Input data.
 * \param s Shift amount.
 * \param ac Constant addition.
 */
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x,
                    uint4 s,
                    uint4 ac)
{
    a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

/**
 * \brief GG transformation for MD5 round.
 *
 * GG transformation for MD5 round 2.
 *
 * \param a Reference to state variable A.
 * \param b Input variable B.
 * \param c Input variable C.
 * \param d Input variable D.
 * \param x Input data.
 * \param s Shift amount.
 * \param ac Constant addition.
 */
inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x,
                    uint4 s,
                    uint4 ac)
{
    a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

/**
 * \brief HH transformation for MD5 round.
 *
 * HH transformation for MD5 round 3.
 *
 * \param a Reference to state variable A.
 * \param b Input variable B.
 * \param c Input variable C.
 * \param d Input variable D.
 * \param x Input data.
 * \param s Shift amount.
 * \param ac Constant addition.
 */
inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x,
                    uint4 s,
                    uint4 ac)
{
    a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

/**
 * \brief II transformation for MD5 round.
 *
 * II transformation for MD5 round 4.
 *
 * \param a Reference to state variable A.
 * \param b Input variable B.
 * \param c Input variable C.
 * \param d Input variable D.
 * \param x Input data.
 * \param s Shift amount.
 * \param ac Constant addition.
 */
inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x,
                    uint4 s,
                    uint4 ac)
{
    a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}

/**
 * \brief Default constructor for MD5 hash computation.
 *
 * Initializes the MD5 hashing algorithm by calling the init() function.
 * This constructor sets up the initial state of the MD5 calculation.
 */
MD5::MD5()
{
    init();
}

// nifty shortcut ctor, compute MD5 for string and finalize it right away
MD5::MD5(const std::string &text)
{
    init();
    update(text.c_str(), (size_type)text.length());
    finalize();
}

/**
 * \brief Initializes the MD5 hash computation.
 *
 * This function resets the internal state of the MD5 algorithm to its initial values.
 * It sets the count of processed bits to zero, sets the state with magic initialization
 * constants, and marks the hash computation as not finalized.
 */
void MD5::init()
{
    finalized = false;  ///< Indicates if the MD5 hash computation is finalized.
    count[0] = 0;       ///< Low-order 32 bits of the total bit length.
    count[1] = 0;       ///< High-order 32 bits of the total bit length.

    // Load magic initialization constants.
    state[0] = 0x67452301;   ///< Initial state value A.
    state[1] = 0xefcdab89;   ///< Initial state value B.
    state[2] = 0x98badcfe;   ///< Initial state value C.
    state[3] = 0x10325476;   ///< Initial state value D.
}

/**
 * \brief Decodes input bytes into output words (uint4).
 *
 * This function converts an array of unsigned char (input) into an array of uint4 (output).
 * It assumes the length (len) is a multiple of 4.
 *
 * \param output Array where the decoded uint4 values will be stored.
 * \param input Array of unsigned char containing the input bytes to be decoded.
 * \param len Length of the input array (must be a multiple of 4).
 */
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((uint4)input[j]) | (((uint4)input[j + 1]) << 8) |
                    (((uint4)input[j + 2]) << 16) | (((uint4)input[j + 3]) << 24);
}

/**
 * \brief Encodes input words (uint4) into output bytes (unsigned char).
 *
 * This function converts an array of uint4 (input) into an array of unsigned char (output).
 * It assumes the length (len) is a multiple of 4.
 *
 * \param output Array where the encoded bytes will be stored.
 * \param input Array of uint4 containing the input words to be encoded.
 * \param len Length of the input array (must be a multiple of 4).
 */
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
    for (size_type i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = input[i] & 0xff;
        output[j + 1] = (input[i] >> 8) & 0xff;
        output[j + 2] = (input[i] >> 16) & 0xff;
        output[j + 3] = (input[i] >> 24) & 0xff;
    }
}

/**
 * \brief Applies the MD5 algorithm on a block of data.
 *
 * This function performs the core MD5 transformations on a block of data (unsigned char array).
 * It updates the MD5 state based on the input block using four rounds (1, 2, 3, and 4).
 *
 * \param block Block of data to apply the MD5 algorithm on.
 * \pre The block size must be equal to MD5::blocksize (64 bytes).
 */
void MD5::transform(const uint1 block[blocksize])
{
    uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode(x, block, blocksize);
    /* Round 1 */
    FF(a, b, c, d, x[0], S11, 0xd76aa478);  /* 1 */
    FF(d, a, b, c, x[1], S12, 0xe8c7b756);  /* 2 */
    FF(c, d, a, b, x[2], S13, 0x242070db);  /* 3 */
    FF(b, c, d, a, x[3], S14, 0xc1bdceee);  /* 4 */
    FF(a, b, c, d, x[4], S11, 0xf57c0faf);  /* 5 */
    FF(d, a, b, c, x[5], S12, 0x4787c62a);  /* 6 */
    FF(c, d, a, b, x[6], S13, 0xa8304613);  /* 7 */
    FF(b, c, d, a, x[7], S14, 0xfd469501);  /* 8 */
    FF(a, b, c, d, x[8], S11, 0x698098d8);  /* 9 */
    FF(d, a, b, c, x[9], S12, 0x8b44f7af);  /* 10 */
    FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG(a, b, c, d, x[1], S21, 0xf61e2562);  /* 17 */
    GG(d, a, b, c, x[6], S22, 0xc040b340);  /* 18 */
    GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);  /* 20 */
    GG(a, b, c, d, x[5], S21, 0xd62f105d);  /* 21 */
    GG(d, a, b, c, x[10], S22, 0x2441453);  /* 22 */
    GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);  /* 24 */
    GG(a, b, c, d, x[9], S21, 0x21e1cde6);  /* 25 */
    GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG(c, d, a, b, x[3], S23, 0xf4d50d87);  /* 27 */
    GG(b, c, d, a, x[8], S24, 0x455a14ed);  /* 28 */
    GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG(d, a, b, c, x[2], S22, 0xfcefa3f8);  /* 30 */
    GG(c, d, a, b, x[7], S23, 0x676f02d9);  /* 31 */
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH(a, b, c, d, x[5], S31, 0xfffa3942);  /* 33 */
    HH(d, a, b, c, x[8], S32, 0x8771f681);  /* 34 */
    HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH(a, b, c, d, x[1], S31, 0xa4beea44);  /* 37 */
    HH(d, a, b, c, x[4], S32, 0x4bdecfa9);  /* 38 */
    HH(c, d, a, b, x[7], S33, 0xf6bb4b60);  /* 39 */
    HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH(d, a, b, c, x[0], S32, 0xeaa127fa);  /* 42 */
    HH(c, d, a, b, x[3], S33, 0xd4ef3085);  /* 43 */
    HH(b, c, d, a, x[6], S34, 0x4881d05);   /* 44 */
    HH(a, b, c, d, x[9], S31, 0xd9d4d039);  /* 45 */
    HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH(b, c, d, a, x[2], S34, 0xc4ac5665);  /* 48 */

    /* Round 4 */
    II(a, b, c, d, x[0], S41, 0xf4292244);  /* 49 */
    II(d, a, b, c, x[7], S42, 0x432aff97);  /* 50 */
    II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II(b, c, d, a, x[5], S44, 0xfc93a039);  /* 52 */
    II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II(d, a, b, c, x[3], S42, 0x8f0ccc92);  /* 54 */
    II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II(b, c, d, a, x[1], S44, 0x85845dd1);  /* 56 */
    II(a, b, c, d, x[8], S41, 0x6fa87e4f);  /* 57 */
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II(c, d, a, b, x[6], S43, 0xa3014314);  /* 59 */
    II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II(a, b, c, d, x[4], S41, 0xf7537e82);  /* 61 */
    II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II(c, d, a, b, x[2], S43, 0x2ad7d2bb);  /* 63 */
    II(b, c, d, a, x[9], S44, 0xeb86d391);  /* 64 */

    // Update state
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    // Zeroize sensitive information.
    memset(x, 0, sizeof(x));
}

/**
 * \brief MD5 block update operation.
 *
 * Continues an MD5 message-digest operation, processing another message block.
 *
 * \param input Pointer to the input data block.
 * \param length Length of the input data block in bytes.
 */
void MD5::update(const unsigned char input[], size_type length)
{
    // compute number of bytes mod 64
    size_type index = count[0] / 8 % blocksize;

    // Update number of bits
    if ((count[0] += (length << 3)) < (length << 3))
    {
        count[1]++;
    }
    count[1] += (length >> 29);

    // number of bytes we need to fill in buffer
    size_type firstpart = blocksize - index;
    size_type i;

    // transform as many times as possible
    if (length >= firstpart)
    {
        // fill buffer first, transform
        memcpy(&buffer[index], input, firstpart);
        transform(buffer);

        // transform chunks of blocksize (64 bytes)
        for (i = firstpart; i + blocksize <= length; i += blocksize)
        {
            transform(&input[i]);
        }
        index = 0;
    }
    else
    {
        i = 0;
    }

    // buffer remaining input
    memcpy(&buffer[index], &input[i], length - i);
}

// for convenience provide a version with signed char
/**
 * \brief MD5 block update operation (signed char version).
 *
 * Provides a convenience wrapper to handle input as signed characters,
 * delegating to the main update function with unsigned characters.
 *
 * \param input Pointer to the input data block (signed characters).
 * \param length Length of the input data block in bytes.
 */
void MD5::update(const char input[], size_type length)
{
    update(reinterpret_cast<const unsigned char *>(input), length);
}

/**
 * \brief Finalizes the MD5 message-digest operation.
 *
 * Finalizes the current MD5 context, computes the message digest,
 * and clears sensitive information from the context for security.
 * This function should be called once after all updates are done.
 *
 * \return Reference to the current MD5 instance.
 */
MD5 &MD5::finalize()
{
    if (!finalized)
    {
        static unsigned char padding[64] =
            {
                0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            };

        // Save number of bits
        unsigned char bits[8];
        encode(bits, count, 8);

        // Pad out to 56 mod 64
        size_type index = count[0] / 8 % 64;
        size_type padLen = (index < 56) ? (56 - index) : (120 - index);
        update(padding, padLen);

        // Append length (before padding)
        update(bits, 8);

        // Store state in digest
        encode(digest, state, 16);

        // Zeroize sensitive information
        memset(buffer, 0, sizeof buffer);
        memset(count, 0, sizeof count);
        finalized = true;
    }
    return *this;
}

// Return hex representation of digest as string.
/**
 * \brief Returns the hexadecimal representation of the MD5 digest.
 *
 * Converts the 16-byte MD5 digest into a hexadecimal string representation.
 * The function returns an empty string if the MD5 context has not been finalized.
 *
 * \return Hexadecimal string representation of the MD5 digest.
 */
std::string MD5::hexdigest() const
{
    if (!finalized)
    {
        return ""; // Return empty string if not finalized
    }

    char buf[33]; // Buffer to hold the hexadecimal string (16 bytes * 2 + 1 null terminator)

    // Convert each byte of the digest to its two-character hexadecimal representation
    for (int i = 0; i < 16; i++)
    {
        sprintf(buf + i * 2, "%02x", digest[i]); // Append two characters representing one byte
    }
    buf[32] = 0; // Null-terminate the string

    return std::string(buf); // Return as std::string
}

/**
 * \brief Overloaded operator to output the hexadecimal representation of the MD5 digest to an output stream.
 *
 * This operator allows the MD5 digest to be output directly to an ostream. It calls the hexdigest() method of the MD5
 * object to obtain the hexadecimal representation and outputs it to the specified ostream.
 *
 * \param out The output stream to which the MD5 digest will be written.
 * \param md5 The MD5 object whose digest will be written to the output stream.
 * \return Reference to the output stream after writing the MD5 digest.
 */
std::ostream &operator<<(std::ostream &out, const MD5 &md5)
{
    return out << md5.hexdigest(); // Output the hexadecimal digest to the ostream
}

/**
 * \brief Computes the MD5 hash of a given string and returns its hexadecimal representation.
 *
 * This function computes the MD5 hash of the input string using the MD5 class. It then converts the computed digest
 * into a hexadecimal string representation using the hexdigest() method and returns it.
 *
 * \param str The input string for which the MD5 hash will be computed.
 * \return Hexadecimal string representation of the MD5 hash of the input string.
 */
std::string md5(const std::string &str)
{
    MD5 md5 = MD5(str); // Create an MD5 object initialized with the input string
    return md5.hexdigest(); // Return the hexadecimal representation of the MD5 digest
}
