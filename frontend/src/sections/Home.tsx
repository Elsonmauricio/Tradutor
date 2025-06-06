import React from "react";

export default function LandingPage() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-100 to-indigo-200 flex flex-col">
      <header className="flex justify-between items-center p-6 bg-white shadow-md">
        <h1 className="text-2xl font-bold text-indigo-600">LinguaBridge</h1>
        <nav className="space-x-6">
          <a href="#features" className="text-gray-700 hover:text-indigo-600">Funcionalidades</a>
          <a href="#about" className="text-gray-700 hover:text-indigo-600">Sobre</a>
          <a href="#start" className="text-white bg-indigo-600 px-4 py-2 rounded-full hover:bg-indigo-700">Começar</a>
        </nav>
      </header>

      <main className="flex flex-1 flex-col items-center justify-center text-center px-4">
        <h2 className="text-4xl sm:text-5xl font-extrabold text-gray-800 mb-6">
          Quebrando barreiras linguísticas com tecnologia
        </h2>
        <p className="text-lg text-gray-600 mb-8 max-w-xl">
          Plataforma de Intervenção e Auxílio de Línguas que conecta pessoas e culturas com traduções em tempo real e suporte a línguas africanas.
        </p>
        <a href="#start" className="bg-indigo-600 text-white px-6 py-3 rounded-full text-lg hover:bg-indigo-700 transition">
          Experimente agora
        </a>
      </main>

      <footer className="text-center text-gray-500 py-6">
        © 2025 LinguaBridge. Todos os direitos reservados.
      </footer>
    </div>
  );
}
