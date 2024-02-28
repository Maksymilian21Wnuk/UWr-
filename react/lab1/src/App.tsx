import React from "react";
import "./styles.css";

interface AppProps {
  name: string;
  job: string;
  company: string;
}

const App: React.FC<AppProps> = ({ name, job, company }) => {
  return (
    <div className="App">
      <h1>{name}</h1>
      <h2>{job}</h2>
      <h4>{company}</h4>
    </div>
  );
};

export default App;
