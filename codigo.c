#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void consumo_cpu(int pid) {
	char p1[10] = "ps -p"; // primeira parte do comando
	char p2[40] = "-o %cpu | grep -v %CPU"; // parte final do comando
	char bash_cmd[256]; // vai receber o comando "completo" a partir da concatenacao

	sprintf(bash_cmd,"%s %d %s", p1, pid, p2); // concatena a string para usar o pid

	system(bash_cmd); // faz a chamada de sistema para calcular o uso da cpu

	return;
}

void consumo_memoria(int pid) {
	char m1[10] = "pmap"; // primeira parte do comando
	char m2[40] = "| grep -i total | awk '{print $2}'"; // parte final do comando
	char bash_cmd2[256]; // vai receber o comando "completo" a partir da concatenacao

	sprintf(bash_cmd2,"%s %d %s", m1, pid, m2); // concatena a string para usar o pid

	system(bash_cmd2); // faz a chamada de sistema para calcular o uso da cpu

	return;
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
			printf("Consumo da CPU(em %%):\n");
			consumo_cpu(pid); // a funcao retorna em % o consumo da cpu pelo processo filho

			if(strcmp(argv[1], "cpu-mem") == 0)
			{
				printf("Consumo de Memoria(em Kilobytes):\n"); 
				consumo_memoria(pid); // a funcao retorna em kilobytes a memoria usada pelo processo filho
			}

			printf("-----------------------------------\n");
			i++; // contador 
			sleep(1); // funcao para contar os segundos
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
		//int begin = time(NULL), end, i;
		clock_t start_t, end_t, total_t;
		int i;
		
		start_t = clock(); //começo do "cronômetro"
		while(1)
		{	
			end_t = clock(); //fim do "cronômetro" a cada iteração
			total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC; //total de segundos passados

			if (total_t == 0.0000 || total_t == 1.0000 || total_t == 2.0000 || total_t == 3.0000 || total_t == 4.0000 || total_t == 5.0000 || total_t == 6.0000 || total_t == 7.0000 || total_t == 8.0000 || total_t == 9.0000)
			{
				malloc(10 * sizeof(100000));
			}
		}	
	}
	perror ("Erro: "); /* execve nãoo funcionou */

	printf ("Tchau !\n");
	exit(0) ; /* encerra o processo com sucesso (código 0) */
	}
}
