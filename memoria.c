#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char bash_cmd[256] = "ps v 1 | awk '{print $12}' | grep -v MEM";
	char buffer[1000];
	FILE *pipe;
	int len; 
	pipe = popen(bash_cmd, "r");

	if (NULL == pipe) {
		perror("pipe");
		exit(1);
	} 
	
	char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
	len = strlen(bash_cmd);
	bash_cmd[len-1] = '\0'; 
	pclose(pipe);

	printf("mem_usage == %s", mem_usage);
}
