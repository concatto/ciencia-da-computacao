# MAGIA: Um Sistema Baseado em Realidade Aumentada para Melhoramento da Capacidade de Abdução de Seres Humanos

_por Fernando Concatto e Arthur Passos_

_Publicado no DXXXVIII Simpósio Intergalático de Tecnologia Anti-humana_

---

## 1. Introdução

$\quad$ Nos anos recentes, é possível observar um considerável aumento na frequência de tentativas de abdução de seres humanos pela população alienígena. Verifica-se também um grande interesse da comunidade científica em favor do desenvolvimento de metodologias para tornar tal atividade mais eficaz e menos propensa a erros. Um dos principais avanços no contexto de sistemas de abdução dos últimos anos, o Painel Abdutivo Intergalático Neoquântico (PAIN), proposto por MacDiablo et al. (2479), mostrou-se altamente efetivo em diversos estudos de caso publicados em múltiplos periódicos renomados.

$\quad$No entanto, alguns estudos apontam que o sistema PAIN apresenta uma alta propensão a erros, os quais frequentemente acarretam na aniquilação do humano alvo (uma consequência geralmente indesejável). Desta maneira, buscando usufruir do conhecimento tecnológico acumulado pela civilização humana nos últimos séculos, este trabalho propõe a utilização do conceito de Realidade Aumentada, explorado pela humanidade nos séculos XX e XXI, para providenciar um processo de abdução mais confortável e menos suscetível a erros. O sistema proposto neste trabalho foi denominado Máquina Abdutiva Geométrica de Interação Amplificatória (MAGIA), evidenciando algumas de suas principais capacidades.

$\quad$Buscando explanar a proposta de forma clara e objetiva, este trabalho foi organizado da seguinte forma: a seção 2 apresenta os conceitos fundamentais do sistema, habilitando sua construção por outros grupos; a seção 3 efetua uma análise crítica do sistema proposto, utilizando estratégias de avaliação disponíveis na literatura; a seção 4 ilustra todas as funcionalidades e pontos críticos do sistema.

## 2. Projeto

O sistema MAGIA consiste na união de tecnologias recentes (e.g, controle de campo magnético e materialização) com a tecnologia vintage de óculos VR, permitindo a imersão e controle do ambiente. O sistema será composto pelos seguintes componentes: 

* **Drone IJD - Espião dourado, versão limitada**: Drone de tamanho reduzido controlado pelo ET que percorre o ambiente e realiza a transmissão de vídeo.

* **Controle Eletromagnético Dazr Reathadder**: Responsável pelo controle do drone, suspensão do corpo e abdução. Para realizar as três ações, o controle conta com sistema de sensibilidade eletromagnética de três níveis, no primeiro estágio o ET pode movimentar o drone para melhorar seu campo de visão e analisar outra perspectiva, já no segundo estágio, é possível manter o corpo do individuo suspenso no local em que ele está e no ultimo estágio é realizado a abdução.

* **Controle Softmicro 063**: Responsável por controles gerais do sistema, como modo de visão (normal, térmico, sonda e raio x), manipulação do tempo (parar, avançar e retroceder) e sincronia de movimento do corpo com o movimento do ET.

* **Materializador Daishinkan**: Responsável por materializar o ser humano em miniatura para permitir a manipulação de sua posição no espaço, com o intuito de facilitar a passagem por uma abertura estreita ou algo similar.

* **Painel Tranmissor 65536K**: Responsável por transmitir a imagem do óculos VR no telão, de forma que possa haver espectadores, como o chefe ou algum aprendiz.

* **Salão de Abdução**: Local onde todos os componentes do sistema se encontram e que permite a movimentação do ET.

* **Óculos de realidade aumentada Juliete - MC Kevinho, versão limitada**: Responsável por aumentar a realidade, captar a visão do drone, receber os comandos dos controles e transmitir a imagem para o telão.

* **Kamehameha abdutor**: Responsável por controlar o corpo e realizar a abdução.

O sistema MAGIA também conta com a tecnologia denominada visão computacional, que de acordo com Dana H. Ballard; Christopher M. Brown (1982), busca automatizar tarefas que o sistema visual humano pode realizar ref. A principal vantagem da utilização de visão computacional é a possibilidade de trabalhar com alvos identificados automaticamente, desta forma, o ET só pode tentar abduzir o que for identificado como um alvo passivo de abdução (e.g ser humano), prevenindo o ET de tentar abduzir uma vaca por engano.

O fluxo de trabalho padrão é composto por duas etapas: Movimentação até a saída acessível pelo raio da nave e abdução.

* **Movimentação**: O ET deve utilizar os controles para mover o corpo até a saída alcançavel pelo raio da nave.

* **Abdução**: O ET deve puxar o corpo com o raio da nave.

## 3. Análise de Usabilidade

### 3.1 Visibilidade do status do sistema

O óculos de realidade aumentada deverá apresentar informações úteis e relevantes, como a distância do humano alvo até o disco voador, o status do raio abdutivo (on/off), além de um feedback em tempo real da manobra sendo executada. O painel transmissor também fortalece este quesito.

![Visão do ET](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/default_view4.jpg)

Como ilustrado na imagem, o ET pode determinar qual visor está sendo utilizado, em qual modo de operação ele se encontra e a distância do alvo.

![Seleção do Visor](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/default_view_visor_select.jpg)

### 3.2 Controle do usuário e liberdade

Opção de voltar no tempo (por tempo limitado - 5 minutos) para permitir que o ET desfaça ações indesejadas, duas opções de pausa no processo, uma através do docking e a outra através do controle Dazr Reathadder.

![Controle Softmicro 063](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/controller.jpg){height=7cm}

O controle apresenta várias opções de controle do sistema de forma intuitiva e sucinta, dando poder de forma simples ao ET.

### 3.3 Prevenção de erros

O sistema MAGIA foi desenhado com a minimização de erros em mente. Por este motivo, algumas funcionalidades com riscos associados, como o cancelamento da abdução e o controle da escotilha da nave espacial, foram tornadas semi-automáticas; assim, o usuário deixa de se preocupar com sua operação, exceto em casos específicos, onde o mesmo pode tomar controle dos mecanismos caso prefira.

Para a abdução, estabeleceu-se um modo de *estase*, onde o ser humano que se situa em estado de abdução permanece suspenso no ar mesmo quando o usuário abandona completamente o controle do MAGIA. Caso o usuário queira de fato cancelar a abdução, basta levar o humano a uma superfície estável e cessar o uso do abdutor ou utilizar o menu do sistema, que inclui uma solicitação de confirmação.

Para a escotilha da nave, implementou-se um sensor de presença que realiza sua abertura automaticamente quando o humano se aproxima pelo lado de fora. Caso o usuário queira controlá-la manualmente, basta acessar o menu do sistema; neste, também existem diálogos para confirmação.

![Visão do ET](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/default_view4.jpg)

É possível visualizar o modo *estase* na imagem acima.

### 3.4 Estética e design minimalista

Buscou-se minimizar a quantidade de textos, ícones e controles no estado padrão do sistema, onde o usuário vê o mundo através do *drone*. Ícones dos visores seguem um padrão de design *flat*, mantendo a inteligibilidade apesar da simplicidade. Controles de seleção de visor, avanço e retrocesso no tempo e medidor de progresso da abdução são apresentados somente conforme existir necessidade. Adicionalmente, para evitar adição de mais controles para manipulação fina do posicionamento do ser humano sendo abduzido, implementou-se um materializador de uma versão holográfica do mesmo, que pode ser controlada pelo usuário como um objeto físico qualquer.

![Controle do Tempo](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/time_stop.jpg){height=4cm}
![Seleção do Visor](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/default_view_visor_select.jpg){height=4cm}

## 3.5 Compatibilidade de um sistema com o mundo real

O sistema MAGIA busca oferecer uma experiência equivalente a tarefas realizadas no dia-a-dia, maximizando assim a comodidade de seu usuário. Para tanto, buscou-se implementar uma interface controlada pelos movimentos da cabeça de seu usuário que exibe o mundo como seus próprios olhos o veriam, porém da perspectiva de um *drone*: um objeto voador miniaturizado com altíssima capacidade de locomoção.

Além disso, o processo de movimentação do humano alvo, assim como sua abdução propriamente dita, se dá por meio de um objeto físico que o usuário pode mover livremente em todas as três dimensões, tendendo a voltar a um ponto fixo no espaço através de uma força de atração. À medida que o usuário movimenta o objeto, o raio abdutor fará com que o humano alvo seja movimentado na mesma direção, com a mesma intensidade.

![Salão de Abdução](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/control_room.jpg){width=15cm}

## 4. Funcionalidades e Pontos Críticos (Imagens)

![Salão de Abdução](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/control_room.jpg)

![Drone IJD - Espião dourado, versão limitada](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/drone.jpg)

![Controle Softmicro 063](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/controller.jpg)

![Visão do ET](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/default_view_visor_select.jpg)

![Visor Termal](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/DC_thermal_surveillance_03.jpg)

![Visor de Sonda](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/scan_visor.jpg)

![Visor de Raio X](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/xray.jpg)

![Controle do Tempo](/home/concatto/ciencia-da-computacao/Engenharia da Usabilidade/Resources/time_stop.jpg)
