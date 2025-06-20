# 📚 Documentação do Projeto Tradutor Português ↔ Umbundo

## Índice

- Visão Geral
- Arquitetura
- Tecnologias Utilizadas
- Estrutura de Pastas
- Funcionalidades
- Fluxo de Dados
- Endpoints da API
- Como Executar o Projeto
- Como Adicionar Novas Traduções
- Como Contribuir
- Autores

---

## Visão Geral

O Tradutor Português ↔ Umbundo é uma aplicação web que permite traduzir palavras e frases entre os dois idiomas, gerenciar um dicionário personalizado, visualizar histórico de traduções e salvar favoritos. O sistema é composto por um backend em C++ (com SQLite) e um frontend em React.

---

## Arquitetura

- **Frontend:** React + TypeScript, estilizado com Tailwind CSS.
- **Backend:** C++ usando [cpp-httplib](https://github.com/yhirose/cpp-httplib) para HTTP e [SQLite](https://www.sqlite.org/) para persistência.
- **Comunicação:** O frontend faz requisições HTTP para o backend, que responde em JSON.

---

## Tecnologias Utilizadas

- **Frontend:** React, TypeScript, Tailwind CSS, Axios, React Router
- **Backend:** C++, cpp-httplib, SQLite, nlohmann/json
- **Banco de Dados:** SQLite (`tradutor.db`)

---

## Estrutura de Pastas

```
Tradutor/
├── backend/
│   ├── main.cpp
│   ├── util.cpp
│   ├── funcoes.hpp
│   ├── httplib.h
│   ├── json.hpp
│   ├── tradutor.db
│   └── ...
├── frontend/
│   ├── src/
│   │   ├── App.tsx
│   │   ├── components/
│   │   │   ├── Translate.tsx
│   │   │   ├── Dictionary.tsx
│   │   │   ├── History.tsx
│   │   │   └── Favorites.tsx
│   │   └── sections/
│   │       ├── Home.tsx
│   │       ├── Funcoes.tsx
│   │       └── about.tsx
│   └── ...
└── ...
```

---

## Funcionalidades

### 1. Tradução de Palavras e Frases
- Traduza palavras ou frases entre Português e Umbundo.
- Tradução instantânea via frontend.

### 2. Histórico de Traduções
- Visualize todas as traduções realizadas.
- Limpe o histórico ou remova entradas específicas.

### 3. Favoritos
- Salve traduções importantes como favoritas.
- Adicione ou remova favoritos facilmente.

### 4. Dicionário Personalizado
- Adicione, edite ou remova traduções do dicionário.
- Busque palavras no dicionário.

### 5. Navegação Intuitiva
- Menu superior para acesso rápido a todas as páginas.

### 6. Integração Backend/Frontend
- Toda ação no frontend é refletida no backend via API REST.

---

## Fluxo de Dados

1. **Usuário interage com o frontend** (React).
2. **Frontend faz requisições HTTP** para o backend (C++).
3. **Backend processa a requisição**, acessa o banco SQLite e retorna resposta em JSON.
4. **Frontend exibe os resultados** ao usuário.

---

## Endpoints da API

| Método | Endpoint                | Descrição                                 |
|--------|------------------------ |-------------------------------------------|
| POST   | /api/translate          | Traduz palavra ou frase                   |
| GET    | /api/dictionary         | Lista todas as traduções do dicionário    |
| POST   | /api/dictionary         | Adiciona nova tradução                    |
| PUT    | /api/dictionary         | Edita tradução existente                  |
| DELETE | /api/dictionary         | Remove tradução                           |
| GET    | /api/history            | Lista histórico de traduções              |
| DELETE | /api/history            | Limpa todo o histórico                    |
| DELETE | /api/history/entry      | Remove uma entrada específica do histórico|
| GET    | /api/favorites          | Lista favoritos                           |
| POST   | /api/favorites          | Adiciona favorito                         |
| DELETE | /api/favorites          | Remove favorito                           |

---

## Como Executar o Projeto

### 1. **Backend**

- Compile o backend:
  ```sh
  gcc -c sqlite3.c -o sqlite3.o
  g++ main.cpp util.cpp sqlite3.o -o tradutor -lws2_32 -std=c++11 -I.
  ```
- Execute o backend:
  ```sh
  ./tradutor
  ```
  O servidor estará disponível em `http://localhost:3002`.

### 2. **Frontend**

- Instale as dependências:
  ```sh
  npm install
  ```
- Rode o frontend:
  ```sh
  npm start
  ```
  Acesse em `http://localhost:3000`.

---

## Como Adicionar Novas Traduções

- **Via Interface Web:**  
  Acesse a página "Dicionário", preencha os campos e clique em "Adicionar".
- **Via Banco de Dados:**  
  Insira diretamente na tabela `dicionario` do SQLite:
  ```sql
  INSERT INTO dicionario (portugues, umbundo) VALUES ('exemplo', 'tradução');
  ```

---

## Como Contribuir

1. Faça um fork do projeto.
2. Crie uma branch para sua feature ou correção.
3. Envie um pull request com uma descrição clara das mudanças.

---

## Autores

- Projeto desenvolvido por [Seu Nome] e colaboradores.

---

## Observações Finais

- O backend utiliza SQLite para persistência dos dados.
- O frontend é responsivo e fácil de usar.
- O projeto pode ser expandido para outros idiomas ou funcionalidades.

---

**Dúvidas ou sugestões?**  
Abra uma issue ou entre em contato com os autores!