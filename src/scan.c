#include "scan.h"


// set the socket lingering(RST connection) instead of wasting bandwidth with the four step close  
void socket_linger_off(const int sockfd) 
{
    struct linger l = {
		.l_onoff = 1,
		.l_linger = 0,
	} ;

    if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER,  &l, sizeof(struct linger)))
		error ("socket SO_LINGER") ;
}


int port_scan(const char *host, const int port)
{
	int ret = -1 ;
	int sockfd ;
	struct sockaddr_in server ;

    signal(SIGPIPE, SIG_IGN); 


	if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
        error ("tcp socket: %s", strerror(errno));
		goto end ;
	}
	socket_linger_off (sockfd) ;


    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    inet_aton(host, &server.sin_addr);
    server.sin_port = htons(port);

    if (0 > connect(sockfd, (struct sockaddr *)&server, sizeof(server)))
	{
        //error ("tcp socket connect [%s:%d]: %s", host, port, strerror(errno));
		goto end ;
	}

	ret = 1 ;

end :
	close (sockfd) ;
	// shutdown() will cause many faults - "Too many open files" in socket(), but close() not
	//shutdown (sockfd, SHUT_RDWR) ;	

	return ret ;
}


int main(int argc, char **argv)
{
	if (argc < 2)	die ("input host") ;


	char *host = argv[1] ;

	int i ;
	for (i = 1; i <= 65535; ++ i)
	{
		if (0 < port_scan(host, i))
			stdout_info ("* port %d is on", i) ;
	}

	return 0 ;
}




