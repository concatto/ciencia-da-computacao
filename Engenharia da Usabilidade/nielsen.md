# Heurísticas de Nielsen

## Visibilidade do status do sistema

Demonstrar claramente o que o sistema está fazendo, caso o mesmo esteja ocupado, e fornecer feedback à medida com que o usuário modifica o estado do sistema, e.g. utilizando indicadores de carregamento/processamento, barras de status (geralmente na parte inferior), indicadores de modificação de arquivo em editores de texto.

## Compatibilidade de um sistema com o mundo real

Desenvolvedores tipicamente fazem uso de jargões diferenciados que não condizem com o vocabulário de usuários em geral. Tal comportamento dificulta o entendimento acerca do uso do sistema. Portanto, ao desenvolver textos indicativos e explicativos, deve-se pensar mais como usuário do que como programador.

## Controle do usuário e liberdade

Permitir que o usuário consiga facilmente desfazer ações realizadas sem querer, minimizando frustrações com erros cometidos por ele próprio. Implementar botões de desfazer, refazer e outras ações de navegação. Contra-exemplo: formulário multiestágio que não tem um botão de voltar para o passo anterior, apenas para o início; outro exemplo é um botão de voltar que elimina o conteúdo dos campos.

## Consistência e padrões

Não utilizar palavras diferentes para dizer a mesma coisa. Seguir padrões estabelecidos por outros sistemas, pois assim o usuário já terá uma ideia de onde encontrar a informação que ele precisa, e.g. menus na parte superior, barra de status na parte inferior, navegação em uma barra lateral ou superior.

## **Prevenção** de erros

Minimizar ocorrências em que o usuário realiza uma ação que ele não deseja realizar, por exemplo deletar algum registro sem querer. Uma tática usual é utilizar diálogos de confirmação em pontos propensos a erro. Contra-exemplo: sqlitebrowser se não existisse um commit no final.

## Ajuda os usuários a reconhecer, diagnosticar e recuperar-se de erros

Dado que o erro não pôde ser prevenido, deve-se auxiliar ao máximo o usuário para que ele sofra pouco. Por exemplo, apresentar mensagens de erro claras e com opções de rumos de ação. Contra-exemplo: site da GOL.

## Reconhecimento em vez de memorização

Evitar situações onde é necessário relembrar conteúdos que apareceram outrora para efetuar uma ação no presente momento, i.e. o que preciso está visível **agora**. Contra-exemplo: um formulário multiestágio que não te lembra de informações importantes inseridas nos estágios anteriores.

## Estética e design minimalista

Utilizar uma densidade de informação mínima, sem conteúdo inútil/desnecessário, reduzindo também a variabilidade de cores em uma mesma página. Deixar as coisas facilmente inteligíveis e claras. Contra-exemplo: Visual Studio.

## Ajuda e documentação

Ter tópicos de ajuda facilmente acessíveis (em todo lugar do sistema) e com informações direto ao ponto. Sugere-se incluir um FAQ. Contra-exemplo: busca na documentação do Java SE; documentação do Bipide.

## Flexibilidade e eficiência de uso

Fazer com que o sistema seja facilmente utilizável tanto por indivíduos que acabaram de iniciar no seu uso quanto por aqueles que já apresentam considerável experiência. Exemplo: itens usados recentemente, como o Windows faz com acesso a arquivos e como o Chrome faz na página padrão de nova aba.
