import React from 'react';
import 'tailwindcss/tailwind.css';

const About: React.FC = () => (
  <section className="flex flex-col items-center justify-center min-h-screen py-12 px-4 sm:px-6 lg:px-8 bg-gray-50">
    <div className="max-w-2xl mx-auto bg-white p-8 rounded-lg shadow-lg">
      <h2 className="text-3xl font-bold text-center text-indigo-600 mb-6">
        Sobre o Projeto
      </h2>
      
      <div className="space-y-4 text-gray-700">
        <p className="text-lg leading-relaxed">
          Este projeto é um Tradutor desenvolvido em React, com o objetivo de facilitar a tradução de textos num idioma de forma rápida e intuitiva. 
          A plataforma possui uma interface simples e amigável, permitindo que usuários insiram textos, escolham os idiomas de origem e destino, e recebam a tradução instantaneamente.
        </p>
        
        <p className="text-lg leading-relaxed">
          O projeto utiliza tecnologias modernas de frontend, como TypeScript e React, garantindo desempenho, escalabilidade e facilidade de manutenção. 
          Além disso, integra Microserviços de tradução para fornecer resultados precisos e atualizados.
        </p>
        
        <p className="text-lg leading-relaxed">
          Este Tradutor foi criado para ajudar estudantes, profissionais e qualquer pessoa que precise de traduções rápidas no dia a dia.
        </p>
      </div>
      
    </div>
  </section>
);

export default About;