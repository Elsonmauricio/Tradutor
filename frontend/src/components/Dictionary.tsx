import React, { useEffect, useState } from 'react';
import axios from 'axios';
import 'tailwindcss/tailwind.css';

interface Palavra {
  portugues: string;
  umbundo: string;
}

const Dictionary = () => {
  const [palavras, setPalavras] = useState<Palavra[]>([]);
  const [portugues, setPortugues] = useState('');
  const [umbundo, setUmbundo] = useState('');
  const [editando, setEditando] = useState<Palavra | null>(null);
  const [busca, setBusca] = useState('');

  // Carregar palavras do dicionário
  const carregarPalavras = async () => {
    try {
      // Substitua pela sua rota real de listagem se existir
      // Se não existir, precisará criar no backend
      const res = await axios.get('http://localhost:3002/api/dictionary');
      setPalavras(res.data);
    } catch (error) {
  if (axios.isAxiosError(error)) {
    console.error("Erro detalhado:", error.response?.data);
    alert(`Erro: ${error.response?.data?.erro || 'Desconhecido'}`);
  } else {
    console.error("Erro:", error);
    alert("Erro desconhecido");
  }
}
 };

  // Adicionar palavra
  const adicionarPalavra = async () => { // <-- Adicione async aqui
  try {
    if (!portugues.trim() || !umbundo.trim()) {
      alert("Preencha ambos os campos!");
      return;
    }

    if (editando) {
      // Atualizar palavra existente
      await axios.put('http://localhost:3002/api/dictionary', {
        portuguesOriginal: editando.portugues,
        portugues,
        umbundo
      });
    } else {
      // Adicionar nova palavra
      await axios.post('http://localhost:3002/api/dictionary', {
        portugues,
        umbundo
      });
    }

    // Recarregar palavras e resetar form
    carregarPalavras();
    setPortugues('');
    setUmbundo('');
    setEditando(null);
  } catch (error) {
    console.error("Erro ao salvar palavra:", error);
    alert("Erro ao salvar palavra!");
  }
};

  // Editar palavra
  const editarPalavra = (palavra: Palavra) => {
    setPortugues(palavra.portugues);
    setUmbundo(palavra.umbundo);
    setEditando(palavra);
  };

  // Remover palavra
  const removerPalavra = async (portugues: string) => {
    if (!window.confirm(`Tem certeza que deseja remover "${portugues}"?`)) return;
    
    try {
      await axios.delete('http://localhost:3002/api/dictionary', {
        data: { portugues }
      });
      carregarPalavras();
    } catch (error) {
      console.error("Erro ao remover palavra:", error);
      alert("Erro ao remover palavra!");
    }
  };

  // Filtrar palavras pela busca
  const palavrasFiltradas = palavras.filter(palavra => 
    palavra.portugues.toLowerCase().includes(busca.toLowerCase()) ||
    palavra.umbundo.toLowerCase().includes(busca.toLowerCase())
  );

  // Carregar palavras ao iniciar
  useEffect(() => {
    carregarPalavras();
  }, []);

  return (
    <div className="p-4 max-w-4xl mx-auto">
      <h2 className="text-2xl font-bold mb-6 text-center">Gerenciamento de Dicionário</h2>
      
      {/* Formulário de adição/edição */}
      <div className="bg-white shadow-md rounded-lg p-6 mb-8">
        <h3 className="text-xl font-semibold mb-4">
          {editando ? 'Editar Palavra' : 'Adicionar Nova Palavra'}
        </h3>
        
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4 mb-4">
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-1">
              Português
            </label>
            <input
              className="w-full p-2 border border-gray-300 rounded-md focus:ring-blue-500 focus:border-blue-500"
              placeholder="Palavra em português"
              value={portugues}
              onChange={e => setPortugues(e.target.value)}
            />
          </div>
          
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-1">
              Umbundo
            </label>
            <input
              className="w-full p-2 border border-gray-300 rounded-md focus:ring-blue-500 focus:border-blue-500"
              placeholder="Tradução em umbundo"
              value={umbundo}
              onChange={e => setUmbundo(e.target.value)}
            />
          </div>
        </div>
        
        <div className="flex justify-end space-x-3">
          {editando && (
            <button
              className="px-4 py-2 bg-gray-500 text-white rounded-md hover:bg-gray-600"
              onClick={() => {
                setPortugues('');
                setUmbundo('');
                setEditando(null);
              }}
            >
              Cancelar
            </button>
          )}
          <button
            className="px-4 py-2 bg-blue-600 text-white rounded-md hover:bg-blue-700"
            onClick={adicionarPalavra}
          >
            {editando ? 'Atualizar' : 'Adicionar'}
          </button>
        </div>
      </div>
      
      {/* Busca e lista de palavras */}
      <div className="bg-white shadow-md rounded-lg overflow-hidden">
        <div className="p-4 border-b">
          <input
            className="w-full p-2 border border-gray-300 rounded-md"
            placeholder="Buscar palavras..."
            value={busca}
            onChange={e => setBusca(e.target.value)}
          />
        </div>
        
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                  Português
                </th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                  Umbundo
                </th>
                <th className="px-6 py-3 text-right text-xs font-medium text-gray-500 uppercase tracking-wider">
                  Ações
                </th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {palavrasFiltradas.length > 0 ? (
                palavrasFiltradas.map((palavra, index) => (
                  <tr key={index} className={index % 2 === 0 ? 'bg-white' : 'bg-gray-50'}>
                    <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">
                      {palavra.portugues}
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                      {palavra.umbundo}
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap text-right text-sm font-medium">
                      <button
                        className="text-blue-600 hover:text-blue-900 mr-3"
                        onClick={() => editarPalavra(palavra)}
                      >
                        Editar
                      </button>
                      <button
                        className="text-red-600 hover:text-red-900"
                        onClick={() => removerPalavra(palavra.portugues)}
                      >
                        Remover
                      </button>
                    </td>
                  </tr>
                ))
              ) : (
                <tr>
                  <td colSpan={3} className="px-6 py-4 text-center text-sm text-gray-500">
                    {palavras.length === 0 
                      ? 'Nenhuma palavra cadastrada ainda.' 
                      : 'Nenhuma palavra encontrada com esse termo.'}
                  </td>
                </tr>
              )}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
};

export default Dictionary;