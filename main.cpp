// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

#include <Core/Core.h>
#include <iostream>
#include <string>

/*
int main(){
	std::string test = "<main><power>33/dfdfd";
	char const * test_c_str {test.c_str()};
	std::cout << "test   = " << test << std::endl;
	std::cout << "c test = " << test_c_str << std::endl;

	
	std::cin.get();
	return 0;
}
*/
// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char modifiableString[] = "Hello from client"; 
	char *hello = modifiableString;
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT);
	

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}
	
	socklen_t len = sizeof(cliaddr); //len is value/resuslt 

	int n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Client : %s\n", buffer); 
	
	
	
	
	int i = 0;
	for(;;){
		if (i > 10) break;
		/*
		sendto(sockfd, (const char *)hello, strlen(hello), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				len); 
		
		
		cliaddr.sin_family = AF_INET; // IPv4 
		cliaddr.sin_addr.s_addr = INADDR_ANY; 
		cliaddr.sin_port = htons(PORT);
		*/
		sendto(sockfd, (const char *)hello, strlen(hello), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				len);  
		//printf("%s", len); 
		printf("Hello message sent.\n"); 
		i++;
	}
	
	close(sockfd);
	return 0; 
} 
