#ifndef __ROT32_H__
#define __ROT32_H__

#include <stdint.h>

static inline uint32_t rot32l1(uint32_t x) {
	return (x << 1) | (x >> 31);
}

static inline uint32_t rot32r1(uint32_t x) {
	return (x >> 1) | (x << 31);
}

static inline uint32_t rot32l8(uint32_t x) {
	return (x << 8) | (x >> 24);
}

static inline uint32_t rot32r8(uint32_t x) {
	return (x >> 8) | (x << 24);
}

static inline uint32_t rot32l3(uint32_t x) {
	return rot32l1(rot32l1(rot32l1(x)));	
}

static inline uint32_t rot32r3(uint32_t x) {
	return rot32r1(rot32r1(rot32r1(x)));	
}

static inline uint32_t rot32l5(uint32_t x) {
	return rot32r3(rot32l8(x));
}

static inline uint32_t rot32l9(uint32_t x) {
	return rot32l1(rot32l8(x));
}

static inline uint32_t rot32r5(uint32_t x) {
	return rot32l3(rot32r8(x));
}

static inline uint32_t rot32r9(uint32_t x) {
	return rot32r1(rot32r8(x));
}

static inline uint32_t rot32l2(uint32_t x) {
	return rot32l1(rot32l1(x));
}

static inline uint32_t rot32l4(uint32_t x) {
	return rot32l2(rot32l2(x));
}

static inline uint32_t rot32l6(uint32_t x) {
	return rot32r1(rot32r1(rot32l8(x)));
}

static inline uint32_t rot32l11(uint32_t x) {
	return rot32l3(rot32l8(x));
}


#endif