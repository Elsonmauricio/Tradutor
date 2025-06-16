import React from 'react';
import 'tailwindcss/tailwind.css'; // Importando o Tailwind CSS

const About: React.FC = () => (
    <section style={{ padding: '2rem', maxWidth: 800, margin: '0 auto' }}>
        <h2>Sobre o Projeto</h2>
        <p>
            Este projeto é um Tradutor desenvolvido em React, com o objetivo de facilitar a tradução de textos entre diferentes idiomas de forma rápida e intuitiva. 
            A aplicação possui uma interface simples e amigável, permitindo que usuários insiram textos, escolham os idiomas de origem e destino, e recebam a tradução instantaneamente.
        </p>
        <p>
            O projeto utiliza tecnologias modernas de frontend, como TypeScript e React, garantindo desempenho, escalabilidade e facilidade de manutenção. 
            Além disso, integra APIs de tradução para fornecer resultados precisos e atualizados.
        </p>
        <p>
            Este Tradutor foi criado para ajudar estudantes, profissionais e qualquer pessoa que precise de traduções rápidas no dia a dia.
        </p>
    </section>
);

export default About;