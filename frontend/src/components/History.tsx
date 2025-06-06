import React, { useEffect, useState } from 'react';
import axios from 'axios';

const History = () => {
  const [history, setHistory] = useState([]);

  useEffect(() => {
    const fetchHistory = async () => {
      const res = await axios.get('http://localhost:5000/api/history');
      setHistory(res.data);
    };
    fetchHistory();
  }, []);

  return (
    <div className="p-4">
      <h2 className="text-xl font-bold">Histórico</h2>
      <ul className="mt-2">
        {history.map((item, index) => (
          <li key={index} className="mb-1 border p-2 bg-white rounded">
            {item}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default History;