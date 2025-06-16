import React from "react";
import 'tailwindcss/tailwind.css'; // Importando o Tailwind CSS

const Funcoes = () => {
  return (
    <div className="max-w-2xl mx-auto p-6 bg-white rounded shadow">
      <h1 className="text-3xl font-bold mb-6 text-indigo-700">Funcionalidades do Tradutor</h1>
      
      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">1. Tradução de Palavras e Frases</h2>
        <p>
          Use a página <strong>Traduzir</strong> para inserir uma palavra ou frase em português ou umbundo e obter a tradução instantânea.
          <br />
          <strong>Como usar:</strong> Digite o texto no campo apropriado e clique em <em>Traduzir</em>. O resultado aparecerá logo abaixo.
        </p>
      </section>

      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">2. Histórico de Traduções</h2>
        <p>
          Acesse a página <strong>Histórico</strong> para visualizar todas as traduções realizadas durante o uso do sistema.
          <br />
          <strong>Como usar:</strong> O histórico é carregado automaticamente ao acessar a página. Você pode consultar traduções anteriores facilmente.
        </p>
      </section>

      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">3. Favoritos</h2>
        <p>
          Salve traduções importantes na página <strong>Favoritos</strong>.
          <br />
          <strong>Como usar:</strong> Para adicionar, digite a palavra e clique em <em>Adicionar</em>. Para remover, clique em <em>Remover</em> ao lado do item desejado.
        </p>
      </section>

      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">4. Dicionário Personalizado</h2>
        <p>
          Expanda o dicionário do sistema na página <strong>Dicionário</strong>.
          <br />
          <strong>Como usar:</strong> Preencha os campos de português e umbundo e clique em <em>Adicionar</em> para inserir uma nova tradução personalizada.
        </p>
      </section>

      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">5. Navegação</h2>
        <p>
          Use o menu superior para navegar entre as páginas: <strong>Traduzir</strong>, <strong>Histórico</strong>, <strong>Favoritos</strong> e <strong>Dicionário</strong>.
        </p>
      </section>

      <section className="mb-6">
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">6. Integração Backend/Frontend</h2>
        <p>
          O frontend (React) se comunica com o backend (C++/httplib) via endpoints HTTP. Todas as ações são processadas no backend e exibidas no frontend em tempo real.
        </p>
      </section>

      <section>
        <h2 className="text-xl font-semibold mb-2 text-indigo-600">Dicas Gerais</h2>
        <ul className="list-disc ml-6">
          <li>Certifique-se de que o backend está rodando antes de usar o frontend.</li>
          <li>Se aparecer erro de rede, verifique se o backend está ativo e ouvindo na porta correta.</li>
          <li>Use os favoritos para guardar traduções importantes.</li>
          <li>Mantenha o dicionário atualizado para melhores resultados.</li>
        </ul>
      </section>
    </div>
  );
};

export default Funcoes;