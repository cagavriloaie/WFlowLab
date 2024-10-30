/**
 *  \file md5.h
 *  \brief Header file for the MD5 class.
 *
 * This file defines the MD5 class, which provides functionality for
 * calculating MD5 hashes of strings or byte arrays.
 *
 *  \author Frank Thilo (thilo@unix-ag.org)
 *  \date Converted to C++ class on unknown date (based on md5.h and md5.c)
 *  \copyright Copyright (C) 1991-2, RSA Data Security, Inc.
 *            All rights reserved.
 *
 * This class is based on the reference implementation of the MD5 Message-Digest Algorithm,
 * as specified in RFC 1321.
 *
 * License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 * Algorithm" in all material mentioning or referencing this software
 * or this function.
 *
 * License is also granted to make and use derivative works provided
 * that such works are identified as "derived from the RSA Data
 * Security, Inc. MD5 Message-Digest Algorithm" in all material
 * mentioning or referencing the derived work.
 *
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 *
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
 */

#ifndef BZF_MD5_H
#define BZF_MD5_H

#include <cstring>  // C-style string manipulation functions
#include <iostream> // Standard input/output stream objects

/**
 *  \brief The MD5 class computes MD5 hashes of strings or byte arrays.
 *
 * It is not designed for speed or security, but rather as a simple
 * implementation for educational purposes.
 *
 * Usage:
 * 1) Feed it blocks of uchars with update()
 * 2) Finalize()
 * 3) Get hexdigest() string or use MD5(std::string).hexdigest()
 *
 * Assumes that char is 8-bit and int is 32-bit.
 */
class MD5 {
  public:
    typedef unsigned int size_type; // must be 32bit

    /**
     *  \brief Default constructor initializes the MD5 state.
     */
    MD5();

    /**
     *  \brief Constructor that initializes the MD5 state with an initial string.
     *  \param text Initial string to hash using MD5.
     */
    explicit MD5(const std::string& text);

    /**
     *  \brief Update the hash with a block of unsigned characters.
     *  \param buf Pointer to the buffer of unsigned characters.
     *  \param length Length of the buffer in size_type units.
     */
    void update(const unsigned char* buf, size_type length);

    /**
     *  \brief Update the hash with a block of characters.
     *  \param buf Pointer to the buffer of characters.
     *  \param length Length of the buffer in size_type units.
     */
    void update(const char* buf, size_type length);

    /**
     *  \brief Finalize the MD5 computation.
     *  \return Reference to the MD5 object.
     */
    MD5& finalize();

    /**
     *  \brief Get the hexadecimal representation of the MD5 hash.
     *  \return Hexadecimal string representing the MD5 hash.
     */
    std::string hexdigest() const;

    /**
     *  \brief Output operator to stream the MD5 object.
     *  \param os Output stream.
     *  \param md5 MD5 object to output.
     *  \return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, MD5 md5);

  private:
    /**
     *  \brief Initialize the MD5 state.
     */
    void init();

    typedef unsigned char uint1; //  8bit
    typedef unsigned int  uint4; // 32bit
    enum { blocksize = 64 };     // VC6 won't eat a const static int here

    /**
     *  \brief Core transformation function for MD5 processing.
     *  \param block Block of data to process.
     */
    void transform(const uint1 block[blocksize]);

    /**
     *  \brief Decode input data into 32-bit words.
     *  \param output Output array of 32-bit words.
     *  \param input Input array of bytes.
     *  \param len Length of the input in size_type units.
     */
    static void decode(uint4 output[], const uint1 input[], size_type len);

    /**
     *  \brief Encode 32-bit words into output data.
     *  \param output Output array of bytes.
     *  \param input Input array of 32-bit words.
     *  \param len Length of the input in size_type units.
     */
    static void encode(uint1 output[], const uint4 input[], size_type len);

    // low level logic operations
    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 rotate_left(uint4 x, int n);
    static inline void  FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                           uint4 s, uint4 ac);
    static inline void  GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                           uint4 s, uint4 ac);
    static inline void  HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                           uint4 s, uint4 ac);
    static inline void  II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                           uint4 s, uint4 ac);

    bool  finalized;         ///< Flag indicating if the hash computation has been finalized.
    uint1 buffer[blocksize]; ///< Buffer for data that didn't fit in the last 64-byte chunk.
    uint4 count[2];          ///< 64-bit counter for number of bits (lo, hi).
    uint4 state[4];          ///< Current digest state.
    uint1 digest[16];        ///< Resultant MD5 hash.
};

std::string md5(const std::string& str);

#endif
