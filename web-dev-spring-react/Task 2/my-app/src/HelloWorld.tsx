import React from 'react';
import './HelloWorld.css'

class HelloWord extends React.Component {
    render() {
      return (
        <div className="HelloWord">
            <p className="HelloWordParagraph">Hello&nbsp;</p>
            <p className="HelloWordParagraph">World!</p>
        </div>
      );
    }
}

export default HelloWord;