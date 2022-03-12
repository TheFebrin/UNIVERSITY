import React from 'react';
import HelloWord from './HelloWorld';
import Logo from './Logo';
import './App.css'

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <Logo></Logo>
        <HelloWord></HelloWord>
      </header>
    </div>
  );
}

export default App;
