/*
* ip.h
* cross-platform compatible IPv4 header
* From Sockets, Shellcode, Porting, and Coding: Reverse Engineering Exploits and Tool Coding for Security Professionals
*/
#ifndef __IP_H__
#define __IP_H__

#if defined(WIN32) || defined(_WIN32)
	#include <windows.h>
	#ifndef LITTLE_ENDIAN
		#define LITTLE_ENDIAN 1234
	#endif
	#ifndef BIG_ENDIAN
		#define BIG_ENDIAN 4321
	#endif
	#ifndef BYTE_ORDER
		// if intel x86 or alpha proc, little endian
		#if defined(_M_IX86) || defined(_M_ALPHA)
			#define BYTE_ORDER LITTLE_ENDIAN
		#endif
		// if power pc or MiPS RX000, big endian.
		#if defined(_M_PPC) || defined(_M_MX000)
			#define BYTE_ORDER BIG_ENDIAN
		#endif
	#endif
#else
	// include byte ordering constants
	#include <sys/types.h>
#endif
/*
 * WIN32, define IPv4 header, assume little endian byte ordering
 */
 struct ip {
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned char 	ip_hl:4; 	// header length
	unsigned char	ip_v:4;  	// version
#else
	unsigned char	ip_v:4;  	// version
	unsigned char	ip_hl;		// header length
#endif
	unsigned char	ip_tos;		// type of service
	short			ip_len;		// total length
	unsigned short	ip_id;		// id
	short			ip_off;		// fragment offset
	unsigned char	ip_ttl;		// time to live
	unsigned char	ip_p;		// proto
	unsigned short	ip_sum;		// checksum
	struct in_addr	ip_src;		// source address
	struct in_addr	ip_dst;		// dest address
};
#endif