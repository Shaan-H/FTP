#include <unistd.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
 
int main(int argc, char const *argv[]) 
{ 
	int soc, newSoc; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addressLength = sizeof(address);
	char buff[1000] = {0};
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
	
	if (soc == 0){
		printf("socket creation failed"); 
		exit(EXIT_FAILURE); 
	}
	
	if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
		
		printf("set options failed");
		exit(EXIT_FAILURE); 
		
	} 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( 8080 );
	
	int binding = bind(soc, (struct sockaddr *)&address, sizeof(address));
	
	if (binding<0){ 
		printf("binding failed"); 
		exit(EXIT_FAILURE); 
	}
 
	if (listen(soc, 3) < 0){ 
		printf("listen"); 
		exit(EXIT_FAILURE); 
	} 
	
	newSoc = accept(soc, (struct sockaddr *)&address, (socklen_t*)&addressLength);
	
	if (newSoc<0){ 
		printf("accept");
		exit(EXIT_FAILURE);
	}
	return 0;
}