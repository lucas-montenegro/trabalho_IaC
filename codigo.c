#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

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
		printf("%d\n", i);
		i++;
		sleep(1);
	}
	//TODO guarde a cada segundo o consumo de memória (em Kilobytes) e CPU (em porcentagem) do processo filho
	//TODO após 10 segundos de execução, mate o proceso filho
}
else /* senão, sou o processo filho (pid == 0) */
{
	if(strcmp(argv, "cpu") == 0) { //TODO se argv[1] for igual a 'cpu', executar código com utilização intensa da UCP
		for(; ;) {

		}
	}
	else if(strcmp(argv, "cpu-mem") == 0) { 	//TODO se argv[1] for igual a 'cpu-mem', executar código com utilização intensa da UCP e da memória
		for(; ;) {
			malloc(sizeof(100000));
		}
	}
}
perror ("Erro: ") ; /* execve nãoo funcionou */

printf ("Tchau !\n") ;
exit(0) ; /* encerra o processo com sucesso (código 0) */

}
