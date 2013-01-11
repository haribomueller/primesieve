///
/// @file  SieveOfEratosthenes.h
///
/// Copyright (C) 2013 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the New BSD License. See the
/// LICENSE file in the top level directory.
///

#ifndef SIEVEOFERATOSTHENES_H
#define SIEVEOFERATOSTHENES_H

#include "config.h"

#include <stdint.h>
#include <string>

namespace soe {

class PreSieve;
class EratSmall;
class EratMedium;
class EratBig;

/// @brief  The abstract SieveOfEratosthenes class sieves primes using
///         the segmented sieve of Eratosthenes.
///
/// SieveOfEratosthenes uses 3 different sieve of Eratosthenes
/// algorithms optimized for small, medium and big sieving primes to
/// cross-off multiples. Its main method is sieve(uint_t prime) which
/// must be called consecutively for all primes up to sqrt(n) in order
/// to sieve the primes up to n. PrimeNumberFinder and
/// PrimeNumberGenerator are derived from SieveOfEratosthenes.
///
class SieveOfEratosthenes {
public:
  enum {
    /// SieveOfEratosthenes uses dense bit packing with 30 numbers per
    /// byte. Each byte of the sieve_ array holds the values
    /// i * 30 + k  with k = { 7, 11, 13, 17, 19, 23, 29, 31 }, that
    /// is 8 values per byte and thus one for each bit.
    NUMBERS_PER_BYTE = 30
  };
  static uint64_t getMaxStop();
  static std::string getMaxStopString();
  uint64_t getStart() const;
  uint64_t getStop() const;
  uint_t getSqrtStop() const;
  uint_t getSieveSize() const;
  uint_t getPreSieve() const;
  void sieve(uint_t);
  void finish();
protected:
  SieveOfEratosthenes(uint64_t, uint64_t, uint_t, uint_t);
  virtual ~SieveOfEratosthenes();
  virtual void segmentProcessed(const byte_t*, uint_t) = 0;
  uint64_t getNextPrime(uint64_t*, uint_t) const;
private:
  static const uint_t bitValues_[8];
  static const uint_t bruijnBitValues_[64];
  /// Lower bound of the current segment
  uint64_t segmentLow_;
  /// Upper bound of the current segment
  uint64_t segmentHigh_;
  /// Sieve primes >= start_
  const uint64_t start_;
  /// Sieve primes <= stop_
  const uint64_t stop_;
  /// sqrt(stop_)
  uint_t sqrtStop_;
  /// Copy of eratSmall_->getLimit()
  uint_t limitEratSmall_;
  /// Copy of eratMedium_->getLimit()
  uint_t limitEratMedium_;
  /// Pre-sieve multiples of tiny sieving primes
  PreSieve* preSieve_;
  /// Cross-off multiples of small sieving primes
  EratSmall* eratSmall_;
  /// cross-off multiples of medium sieving primes
  EratMedium* eratMedium_;
  /// cross-off multiples of big sieving primes
  EratBig* eratBig_;
  /// Sieve of Eratosthenes array
  byte_t* sieve_;
  /// Size of sieve_ (must be power of 2)
  uint_t sieveSize_;
  static uint64_t getByteRemainder(uint64_t);
  void allocate(uint_t);
  void cleanUp();
  void preSieve();
  void crossOffMultiples();
  void sieveSegment();
  DISALLOW_COPY_AND_ASSIGN(SieveOfEratosthenes);
};

} // namespace soe

#endif
