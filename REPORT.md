# Trabalho Prático - AB2

Disciplina - Introdução à Computação.

Professor - André Lage.

# Identificação

- Discente 1

    -- Nome: Lucas Montenegro Andrade Assunção.
    -- Matrícula: 18110496.

- Discente 2

    -- Nome: Luís Antônio da Silva Nascimento.
    -- Matrícula: 18110497.

- Discente 3

    -- Nome: Vinícius Monteiro Pontes.
    -- Matrícula: 18110528.

**Observação:** A nota deverá ser distribuída de forma igualitária entre os integrantes da equipe.


# Resultados

Gráfico de consumo da UCP (%):

![alt text](https://github.com/lucas-montenegro/trabalho_IaC/blob/master/src/grafico_ucp.jpeg "Gráfico de consumo da UCP")

Gráfico de consumo de memória (KB):

![alt text](https://github.com/lucas-montenegro/trabalho_IaC/blob/master/src/grafico_memoria.jpeg "Gráfico de consumo de memória")

# Discussão
#### Utilização intensa da UCP

Ao analisarmos o [gráfico](https://github.com/lucas-montenegro/trabalho_IaC/blob/master/src/grafico_ucp.jpeg "Curva de uso da UCP") referente ao uso intenso de UCP, e antes disso os resultados obtidos durante o desenvolvimento do programa, logo verificamos que sua curva de crescimento inicial se mostrava desproporcional ao restante da execução. Com exceção ao primeiro segundo, o gráfico sempre mostrou pequeno desvio, dificilmente ultrapassando a marca de uma dúzia (%), o que foi contra nosso instinto de que um laço vazio de 'for' teria um crescimento grande, mas constante. Foi contraintuitivo também o fato de que a porcentagem de uso da UCP frequentemente ultrapassou os 100 porcento, e após pesquisa inferimos que devido à natureza do comando `ps -p -o %cpu | grep -v %CPU` , esse número é a soma do uso de todos os núcleos do processador. Após esse entendimento, nossas expectativas se tornaram mais alinhadas com os resultados.

#### Utilização intensa da memória

Na análise dos [resultados](https://github.com/lucas-montenegro/trabalho_IaC/blob/master/src/grafico_memoria.jpeg "Curva de uso da memória") reunidos pela execução do programa com uso intenso de memória, percebemos que eles estavam dessa vez mais nivelados com nossas expectativas, visto que apresentaram um crescimento grande, mas muito mais constante. Entretanto, tivemos que antes chegar na compreensão de que `malloc(sizeof(100000))` , da forma recebida como referência do trabalho, nos daria o mesmo resultado que `malloc(sizeof(int))` . Isso se daria independente da ordem de grandeza do número, fazendo assim necessária a utilização de uma multiplicação da quantidade de bytes, como em `malloc(10 * sizeof(int))`.

# Experiência no desenvolvimento

Inicialmente, o grupo procurou entender as solicitações requisitadas nos **TODO** presentes no arquivo _main.c_. Após isso, buscamos entender o funcionamento da função `fork()` para darmos início ao nosso código. Em seguida, pesquisamos sobre funções que limitassem um comando de repetição por determinado tempo, para que pudéssemos monitorar o uso de CPU e memória por 10 segundos, então encontramos a função `sleep()`, que cessa um processo durante o tempo, em segundos, passado como parâmetro.

Então, analisamos formas de monitorar o uso de **CPU** que está sendo utilizado por um processo, em %, e após pesquisarmos bastante sobre como o comando os funciona, descobrimos que a chamada de sistema `ps –p "pid" -o %cpu | grep –v %CPU` retornaria o uso da **CPU** do processo cujo o **PID** é inserido nesse comando. Com isso, a nossa dificuldade era de inserir o **PID** do processo filho dentro desse comando, que foi resolvido com a concatenação do **PID** do processo filho com o comando através da função `sprintf()`, que recebe como parâmetro a _string_ que deverá receber a concatenação e o que deve ser concatenado, em nosso caso foram 2 _strings_ e um inteiro.

Com o monitoramento do uso da **CPU** pronto, restou o acompanhamento da memória alocada pelo processo filho, que é alocada dinamicamente através de um `malloc(sizeof(type))`. O maior obstáculo era impedir que essa alocação consumisse toda a memória disponível e após muitas tentativas, decidimos limitar a quantidade de vezes que a função `malloc` era executada a cada segundo com a função `clock()`. Para monitorar o uso da memória em **KB** , nós pesquisamos bastante sobre o comando **pmap** e utilizamos a chamada de sistema `pmap "pid" | grep –i total | awk '{print $2}'` , que retorna a quantidade de **KB** que é utilizado pelo processo filho durante a sua execução.

Após o fim do _loop_ e do controle da **CPU** e da memória, a última tarefa era a de matar o processo filho, que foi realizada através da função `kill()`, que recebe como parâmetros o **PID** do processo que desejamos matar e **SIGKILL**.

Além disso, é necessário informar que durante a criação do programa foi essencial a inclusão de novas bibliotecas para que as funções inseridas funcionassem perfeitamente.
