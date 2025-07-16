Descrição: O projeto Philosophers é uma implementação do clássico problema dos Filósofos Comilões, usado para ensinar os fundamentos da programação concorrente. O objetivo é simular filósofos que precisam pegar dois garfos para comer, mas devem evitar deadlocks (impasse) e race conditions (condições de corrida) usando mecanismos de sincronização.

Desafios e Implementação:

Gerenciamento de Threads: Criar e gerenciar múltiplas threads (uma para cada filósofo) que executam simultaneamente.

Sincronização com Mutexes: Utilizar mutexes (pthread_mutex_t) para proteger recursos compartilhados (os garfos) e garantir que apenas um filósofo possa pegar um garfo por vez, evitando condições de corrida.

Prevenção de Deadlocks: Implementar estratégias para evitar que os filósofos entrem em um estado de impasse onde nenhum deles pode comer (por exemplo, ordenando a aquisição de garfos ou usando um controle de recursos global).

Controle de Tempo: Simular as ações dos filósofos (pensar, comer, dormir) usando funções de tempo.

O que aprendi:

Programação Concorrente: Fundamentos teóricos e práticos de threads e concorrência.

Sincronização: Domínio do uso de mutexes para proteção de recursos compartilhados.

Debugging de Concorrência: Identificar e resolver problemas complexos como deadlocks e race conditions.

Gestão de Recursos: Estratégias para alocar e liberar recursos em um ambiente multithreaded.
