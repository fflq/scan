#ifndef _PRINT_H_
#define _PRINT_H_

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

#define stdout_info(fmt, ...)	fprintf(stdout, fmt"\n", ##__VA_ARGS__) 
#define stderr_info(fmt, ...)	fprintf(stderr, fmt"\n", ##__VA_ARGS__) 
#define syslog_info(fmt, ...)	syslog(LOG_INFO, fmt"\n", ##__VA_ARGS__) 

#ifdef SYSLOG
#define info(fmt, ...)	syslog(LOG_INFO, "[%d]: " fmt"\n", __LINE__, ##__VA_ARGS__) 
#define error(fmt, ...)	syslog(LOG_ERR, "[%d]: " fmt"\n", __LINE__, ##__VA_ARGS__)
#define die(fmt, ...)	\
	do { syslog(LOG_ERR, "[%d][quit]: " fmt"\n", __LINE__, ##__VA_ARGS__); \
		 exit(EXIT_FAILURE); } while(0) 
#else 
#define info(fmt, ...)	fprintf(stdout, "[%d][%s]: " fmt"\n", __LINE__, __FUNCTION__, ##__VA_ARGS__) 
#define error(fmt, ...)	fprintf(stderr, "[%d][%s][error]: " fmt"\n", __LINE__, __FUNCTION__, ##__VA_ARGS__) 
#define die(fmt, ...)	\
	do { fprintf(stderr, "[%d][%s][quit]: " fmt"\n", __LINE__, __FUNCTION__, ##__VA_ARGS__); \
		 exit(EXIT_FAILURE); } while(0) 
#endif 

#ifdef DEBUG
#define debug_info	stdout_info	
#else
#define debug_info(fmt, ...)
#endif

#endif
