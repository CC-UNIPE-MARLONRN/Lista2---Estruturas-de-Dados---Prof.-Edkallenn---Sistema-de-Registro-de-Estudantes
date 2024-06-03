# Lista2 - Estruturas de Dados - Prof. Edkallenn - Sistema de Registro de Estudantes

## Descrição
Este sistema implementa o registro e a gestão de estudantes em uma instituição de ensino, utilizando diferentes estruturas de dados para gerenciar listas de estudantes, histórico de notas, filas de matrícula em disciplinas e deque de espera para atendimento. O sistema possui um menu interativo com várias opções de gerenciamento.

## Funcionalidades
### Menu Principal
1. **Gerenciar Lista de Estudantes**
    - Adicionar Estudante
    - Remover Estudante
    - Buscar Estudante
    - Exibir Todos os Estudantes
2. **Gerenciar Pilha de Histórico de Notas**
    - Atualizar Notas do Estudante
    - Exibir Notas do Estudante
3. **Gerenciar Fila de Matrícula em Disciplinas**
    - Definir Disciplina e Capacidade
    - Adicionar Estudante na Fila de Matrícula
    - Matricular Estudante da Fila
    - Exibir Fila de Matrícula
4. **Gerenciar Deque de Espera para Atendimento**
    - Adicionar Estudante no Início do Deque
    - Adicionar Estudante no Fim do Deque
    - Remover Estudante do Início do Deque
    - Remover Estudante do Fim do Deque
    - Exibir Deque de Espera
    - Buscar Estudante no Deque
5. **Salvar tudo em um arquivo.txt**
0. **Sair**

### Estrutura do Sistema
- **Lista de Estudantes:** Gerencia o cadastro e informações dos estudantes.
- **Pilha de Histórico de Notas:** Armazena e gerencia o histórico de notas dos estudantes.
- **Fila de Matrícula em Disciplinas:** Organiza os estudantes em fila para matrícula nas disciplinas.
- **Deque de Espera para Atendimento:** Gerencia a fila de espera para atendimento administrativo.

## Regras de Operação
- Não é possível adicionar notas sem que o estudante esteja cadastrado.
- Não é possível adicionar um estudante na fila de matrícula ou no deque sem que as disciplinas ou o deque estejam criados.
- As matrículas dos estudantes são geradas aleatoriamente.

## Implementação
### Compilação e Execução
Para compilar o sistema, é necessário um compilador de arquivos .c. Após a compilação, execute o arquivo executável gerado para iniciar o sistema.

### Menu Interativo
O sistema possui um menu interativo que permite o gerenciamento completo do registro de estudantes, histórico de notas, filas de matrícula e deque de espera.

## Objetivo
Este projeto tem como objetivo demonstrar o uso de estruturas de dados em C para implementar um sistema completo de gerenciamento de estudantes. Ele visa proporcionar uma experiência prática de como as listas, pilhas, filas e deques podem ser utilizados para resolver problemas reais de gerenciamento de informações em um contexto educacional.
