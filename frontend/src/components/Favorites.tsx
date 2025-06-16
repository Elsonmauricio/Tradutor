import React, { useEffect, useState } from 'react';
import axios from 'axios';
import 'tailwindcss/tailwind.css';

const Favorites = () => {
  const [favorites, setFavorites] = useState<string[]>([]);
  const [portugues, setPortugues] = useState('');
  const [umbundo, setUmbundo] = useState('');

  // Carrega favoritos do backend
  const fetchFavorites = async () => {
    try {
      const res = await axios.get('http://localhost:3002/api/favorites');
      setFavorites(res.data);
    } catch (error) {
      console.error("Erro ao buscar favoritos:", error);
    }
  };

  // Adiciona nova palavra ao dicionário
  const adicionarPalavra = async () => {
    try {
      if (!portugues.trim() || !umbundo.trim()) {
        alert("Preencha ambos os campos!");
        return;
      }
      
      await axios.post('http://localhost:3002/api/dictionary', { 
        portugues, 
        umbundo 
      });
      
      // Limpa campos e mostra mensagem
      setPortugues('');
      setUmbundo('');
      alert("Palavra adicionada com sucesso!");
      
    } catch (error) {
      console.error("Erro ao adicionar palavra:", error);
      alert("Erro ao adicionar palavra!");
    }
  };

  // Remove favorito
  const removerFavorito = async (favorito: string) => {
    try {
      await axios.delete('http://localhost:3002/api/favorites', { 
        data: { favorito } 
      });
      // Atualiza lista após remover
      fetchFavorites();
    } catch (error) {
      console.error("Erro ao remover favorito:", error);
    }
  };

  // Carrega favoritos ao iniciar
  useEffect(() => {
    fetchFavorites();
  }, []);

  return (
    <div className="p-4 max-w-md mx-auto">
      <h2 className="text-xl font-bold mb-4">Favoritos</h2>
      
      {/* Formulário para adicionar palavras */}
      <div className="mb-6 p-4 bg-gray-50 rounded-lg">
        <h3 className="font-medium mb-2">Adicionar nova palavra</h3>
        <div className="space-y-2">
          <input
            className="w-full p-2 border rounded"
            placeholder="Português"
            value={portugues}
            onChange={e => setPortugues(e.target.value)}
          />
          <input
            className="w-full p-2 border rounded"
            placeholder="Umbundo"
            value={umbundo}
            onChange={e => setUmbundo(e.target.value)}
          />
          <button 
            className="w-full bg-blue-500 text-white py-2 rounded hover:bg-blue-600"
            onClick={adicionarPalavra}
          >
            Adicionar ao Dicionário
          </button>
        </div>
      </div>
      
      {/* Lista de favoritos */}
      <div className="border rounded-lg overflow-hidden">
        <h3 className="bg-gray-100 p-2 font-medium">Palavras favoritas</h3>
        <ul className="divide-y">
          {favorites.length > 0 ? (
            favorites.map((item, idx) => (
              <li key={idx} className="p-3 flex justify-between items-center">
                <span>{item}</span>
                <button 
                  className="text-red-500 hover:text-red-700"
                  onClick={() => removerFavorito(item)}
                >
                  Remover
                </button>
              </li>
            ))
          ) : (
            <li className="p-3 text-center text-gray-500">
              Nenhum favorito encontrado
            </li>
          )}
        </ul>
      </div>
    </div>
  );
};

export default Favorites;