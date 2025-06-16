import React, { useState } from 'react';
import axios from 'axios';

// Exemplo de função para traduzir texto
async function traduzir(texto: string) {
  const resposta = await axios.post("http://localhost:3002/api/translate", { text: texto });
  return resposta.data.translation;
}

const Translate = () => {
  const [input, setInput] = useState('');
  const [translation, setTranslation] = useState('');

  const handleTranslate = async () => {
    const translatedText = await traduzir(input);
    setTranslation(translatedText);
  };

  return (
    <div className="p-4">
      <h2 className="text-xl font-bold mb-2">Tradução</h2>
      <textarea
        value={input}
        onChange={e => setInput(e.target.value)}
        className="w-full p-2 border border-gray-300 rounded"
        rows={4}
      ></textarea>
      <button onClick={handleTranslate} className="mt-2 px-4 py-2 bg-blue-600 text-white rounded">
        Traduzir
      </button>
      <div className="mt-4 p-2 bg-white border rounded">
        <strong>Tradução:</strong>
        <p>{translation}</p>
      </div>
    </div>
  );
};

export default Translate;