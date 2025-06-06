import React, { useEffect, useState } from 'react';
import axios from 'axios';

const Favorites = () => {
  const [favorites, setFavorites] = useState([]);

  useEffect(() => {
    const fetchFavorites = async () => {
      const res = await axios.get('http://localhost:5000/api/favorites');
      setFavorites(res.data);
    };
    fetchFavorites();
  }, []);

  return (
    <div className="p-4">
      <h2 className="text-xl font-bold">Favoritos</h2>
      <ul className="mt-2">
        {favorites.map((item, index) => (
          <li key={index} className="mb-1 border p-2 bg-white rounded">
            {item}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default Favorites;
