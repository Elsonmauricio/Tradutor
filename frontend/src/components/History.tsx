import React, { useEffect, useState } from 'react';
import axios from 'axios';
import 'tailwindcss/tailwind.css';

const History = () => {
  const [history, setHistory] = useState<string[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');
  const [clearing, setClearing] = useState(false);

  const fetchHistory = async () => {
    try {
      setLoading(true);
      setError('');
      const res = await axios.get('http://localhost:3002/api/history');
      setHistory(res.data);
    } catch (err) {
      setError('Erro ao carregar histórico. Verifique se o servidor está rodando.');
      console.error("Erro na requisição:", err);
    } finally {
      setLoading(false);
    }
  };

  
const limparHistorico = async () => {
    if (!window.confirm('Tem certeza que deseja limpar todo o histórico?')) return;
    
    try {
        const response = await axios.delete('http://localhost:3002/api/history');
        
        if (response.data.status === 'limpo') {
            setHistory([]); // Limpa o estado local imediatamente
            alert('Histórico limpo com sucesso!');
            setClearing(true);
        } else {
            alert('Falha ao limpar histórico: ' + (response.data.erro || 'Erro desconhecido'));
        }
    } catch (err) {
        console.error("Erro ao limpar histórico:", err);
        
        if (axios.isAxiosError(err)) {
            alert("Erro ao limpar histórico: " + (err.response?.data?.erro || err.message));
        } else {
            alert("Erro desconhecido ao limpar histórico");
        }
        setClearing(false);
    }
};

  useEffect(() => {
    fetchHistory();
  }, []);

  return (
    <div className="p-4 max-w-4xl mx-auto">
      <div className="flex justify-between items-center mb-6">
        <h2 className="text-2xl font-bold">Histórico de Traduções</h2>
        <button
          onClick={limparHistorico}
          className="bg-red-500 hover:bg-red-700 text-white py-2 px-4 rounded disabled:opacity-50"
          disabled={clearing} // Desabilita o botão durante a limpeza
        >
          {clearing ? 'Limpando...' : 'Limpar Histórico'} {/* Texto dinâmico */}
        </button>
      </div>

      {loading && <p className="text-center">Carregando histórico...</p>}
      
      {error && (
        <div className="bg-red-100 border border-red-400 text-red-700 px-4 py-3 rounded mb-4">
          {error}
          <button 
            onClick={fetchHistory}
            className="ml-4 bg-red-600 text-white px-3 py-1 rounded text-sm"
          >
            Tentar novamente
          </button>
        </div>
      )}

      {!loading && !error && (
        <div className="bg-white shadow-md rounded-lg overflow-hidden">
          <ul className="divide-y divide-gray-200">
            {history.length > 0 ? (
              history.map((entry, index) => (
                <li key={index} className="p-4 hover:bg-gray-50">
                  <div className="flex justify-between items-center">
                    <div>
                      {entry.split('=').length === 2 ? (
                        <>
                          <span className="font-medium">{entry.split('=')[0]}</span>
                          <span className="mx-2">→</span>
                          <span>{entry.split('=')[1]}</span>
                        </>
                      ) : (
                        <span>{entry}</span>
                      )}
                    </div>
                    <button
                      onClick={async () => {
                        if (!window.confirm('Remover esta entrada?')) return;
                        try {
                          await axios.delete('http://localhost:3002/api/history/entry', {
                            data: { entry }
                          });
                          fetchHistory();
                        } catch (err) {
                          console.error(err);
                        }
                      }}
                      className="text-red-500 hover:text-red-700"
                    >
                      Remover
                    </button>
                  </div>
                </li>
              ))
            ) : (
              <li className="p-4 text-center text-gray-500">
                Nenhuma entrada no histórico
              </li>
            )}
          </ul>
        </div>
      )}
    </div>
  );
};

export default History;