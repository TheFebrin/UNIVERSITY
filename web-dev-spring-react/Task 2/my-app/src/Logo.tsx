import React from 'react';
import logo from './logo.svg';
import './Logo.css';

function Logo() {
  return (
    <div className="Logo">
        <img src={logo} className="Logo-logo" alt="logo" />
    </div>
  );
}

export default Logo;
