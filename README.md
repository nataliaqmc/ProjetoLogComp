# Projeto Lógica da Computação:
#### Feito por: Natália Queiroz Menezes Carreras
## Introdução:
### Objetivos:
  1. Criar uma Linguagem de Programação.
  2. A linguagem deve ter todas as estruturas básicas de uma linguagem de programação: variáveis, condicionais e loops.

### Tarefas:
  1. Estruturar a linguagem seguindo o padrão EBNF.
  2. Utilizar as ferramentas Flex e Bison para realizar as etapas de Análise Léxica e Sintática. A saída deve ser um arquivo C ou CPP compilado pelo Flex/ Bison.
  3. Utilizar alguma VM (LLVM, JVM, .net, etc) para interpretar um programa da sua linguagem.
  4. Criar um exemplo de testes que demonstre as características da sua linguagem.
  5. Montar uma apresentação com slides apresentando sua linguagem (Motivação, Características, Curiosidades e Exemplos). Colocar no Git.

### Entregas:
  - Linguagem estruturada segundo a EBNF (tarefa 1).
  - Análise Léxica e Sintática (sem análise semântica e compilação) (tarefa 2).
  - Realizar as tarefas 3 e 4.

## Implementação:
### Estrutura da Linguagem segundo o padrão EBNF:
    BLOCK = { STATEMENT };
    STATEMENT = ( λ | ASSIGNMENT | PRINT | WHILELOOP | IFSTATEMENT ), "\n" ;
    
    ASSIGNMENT = IDENTIFIER, "=", EXPRESSION ;
    PRINT = "print", "(", EXPRESSION, ")" ;
    WHILELOOP = "while", "(", EXPRESSION, ")", "{", STATEMENT, "}" ;
    IFSTATEMENT = "if", EXPRESSION, "{", STATEMENT, "}" | "if", EXPRESSION, "{", STATEMENT, "}", "ifnot", "{", STATEMENT, "}" ;
    CONDITION = EXPRESSION, (">" | "<" | ">=" | "<=" | "==" | "!="), EXPRESSION ; 
    EXPRESSION = TERM, { ("+" | "-"), TERM } ;
    TERM = FACTOR, { ("*" | "/"), FACTOR } ;
    FACTOR = (("+" | "-"), FACTOR) | NUMBER | "(", EXPRESSION, ")" | IDENTIFIER ;
    IDENTIFIER = LETTER, { LETTER | DIGIT | "_" } ;

    NUMBER = DIGIT, { DIGIT } ;
    LETTER = ( a | ... | z | A | ... | Z ) ;
    DIGIT = ( 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 ) ;

## Referências:
  - https://www.capsl.udel.edu/courses/cpeg421/2012/slides/Tutorial-Flex_Bison.pdf
  - https://begriffs.com/posts/2021-11-28-practical-parsing.html
  - https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
  - http://www.wilfred.me.uk/blog/2014/08/27/baby-steps-to-a-c-compiler/
  - https://www.llvmpy.org/

