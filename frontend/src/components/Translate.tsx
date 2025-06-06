import React, { useState } from 'react';
import axios from 'axios';

const Translate = () => {
  
  <div className="p-4">
    <h2 className="text-2xl font-bold mb-2">Tradução</h2>
    <p>Componente de tradução funcionando!</p>
  </div>

  const [input, setInput] = useState('');
  const [translation, setTranslation] = useState('');

  const handleTranslate = async () => {
    const response = await axios.post('http://localhost:5000/api/translate', { text: input });
    setTranslation(response.data.translation);
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