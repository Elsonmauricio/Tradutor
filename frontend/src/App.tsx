import React from 'react';
import { BrowserRouter as Router, Route, Routes, Link } from 'react-router-dom';
import Translate from './components/Translate.tsx';
import Dictionary from './components/Dictionary.tsx';
import History from './components/History.tsx';
import Favorites from './components/Favorites.tsx';
import Home from './sections/Home.tsx';
import Funcoes from './sections/Funcoes.tsx';
import About from './sections/about.tsx';
import './App.css'; 
import 'tailwindcss/tailwind.css'; // Importando o Tailwind CSS

function App() {
  return (
    <Router>
      <div className="min-h-screen bg-gray-100">
        <nav className="bg-blue-600 p-4 text-white">
          <ul className="flex space-x-4">
            <li><Link to="/">Início</Link></li>
            <li><Link to="/translate">Tradução</Link></li>
            <li><Link to="/dictionary">Dicionário</Link></li>
            <li><Link to="/history">Histórico</Link></li>
            <li><Link to="/favorites">Favoritos</Link></li>
          </ul>
        </nav>
        
        <Routes>

          <Route path="/" element={<Home />} />
          <Route path="/funcoes" element={<Funcoes />} />
          <Route path="/about" element={<About />} />
          <Route path="/translate" element={<Translate />} />
          <Route path="/dictionary" element={<Dictionary />} />
          <Route path="/history" element={<History />} />
          <Route path="/favorites" element={<Favorites />} />
        </Routes>
      </div>
    </Router>
    

  );
}

export default App;