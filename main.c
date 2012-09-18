#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFERRSIZE 256

#define NAGIOSOK 0
#define NAGIOSWARNING 1
#define NAGIOSCRITICAL 2
#define NAGIOSUNKNOWN 3

int checkSSH(char *host, int port, char *user, char *password, char* error, int errorsize)
{
        int rc;
        ssh_session my_ssh_session = ssh_new();

        if (my_ssh_session == NULL)
                return 1;

        ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host);
        rc = ssh_connect(my_ssh_session);
        if (rc != SSH_OK)
        {
                snprintf(error, errorsize, "Error connecting to localhost: %s\n",
                ssh_get_error(my_ssh_session));
                return 2;
        }

        rc = ssh_userauth_password(my_ssh_session, user, password);
        if (rc != SSH_AUTH_SUCCESS)
        {
                snprintf(error, errorsize, "Error authenticating with password: %s\n",
                ssh_get_error(my_ssh_session));
                ssh_disconnect(my_ssh_session);
                ssh_free(my_ssh_session);
                return 3;
        }

        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
	return 0;
}


int main(int argc, char* argv[])
{
	char error_password[BUFFERRSIZE];
	char error_default_password[BUFFERRSIZE];
	
	char *host;
	int port;
	char *user;
	char *password;
	char *password_default="calvin";

	if((argc<5)||(argc>6))
	{
		printf("missing operand\n %s <host> <port> <user> <password> [defaultpassword]\n",argv[0]);	
		exit(NAGIOSUNKNOWN);
	}
	
	host=argv[1];
	port=atoi(argv[2]);
	if(port==0) port=22;
	user=argv[3];
	password=argv[4];
	
	if(argc==6)
		password_default=argv[5];
	
	if(checkSSH(host,port,user,password,error_password,BUFFERRSIZE)==0)
	{
		printf("OK - DRAC %s\n",argv[1]);
		exit(NAGIOSOK);
	}
	else if(checkSSH(host,port,user,password_default,error_default_password,BUFFERRSIZE)==0)
	{
		printf("WARNING - DRAC %s with default password(%s)\n",host,password_default);
		exit(NAGIOSWARNING);	
	}
		
	printf("CRITICAL - DRAC %s: %s\n",host,error_default_password);
	exit(NAGIOSCRITICAL);	
}

