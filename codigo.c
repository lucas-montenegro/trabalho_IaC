#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void memoria() {
	char bash_cmd[256] = "ps v 0 | awk '{print $9}' | grep -v MEM";
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

int main (int argc, char *argv[], char *envp[]) {
	int i = 1; // contador de segundos
	int pid ; /* identificador de processo */

	pid = fork () ; /* replicacção do processo */

	if ( pid < 0 ) { /* se o fork não funcionou */
		perror ("Erro: ") ;
		exit (-1) ; /* encerra o processo com código de erro -1 */
	}
	else if( pid > 0 ) /* se sou o processo pai*/
	{
		while(i <= 10) {
			memoria();
			i++;
			sleep(1);
		}

		kill(0, SIGKILL); // mata o processo filho
	//TODO guarde a cada segundo o consumo de memória (em Kilobytes) e CPU (em porcentagem) do processo filho
	//TODO após 10 segundos de execução, mate o proceso filho
	}
	else /* senão, sou o processo filho (pid == 0) */
	{
	if(strcmp(argv[1], "cpu") == 0) { //TODO se argv[1] for igual a 'cpu', executar código com utilização intensa da UCP
		for(; ;) {

		}
	}
	else if(strcmp(argv[1], "cpu-mem") == 0) { 	//TODO se argv[1] for igual a 'cpu-mem', executar código com utilização intensa da UCP e da memória
			for(; ;) {
				malloc(sizeof(100000));
			}
		}
	}
	perror ("Erro: "); /* execve nãoo funcionou */

	printf ("Tchau !\n");
	exit(0) ; /* encerra o processo com sucesso (código 0) */
}
