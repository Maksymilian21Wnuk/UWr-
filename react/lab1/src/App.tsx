import React from "react";
import "./styles.css";

import Image from "./Image";
import { Infos } from "./Infos";
import { Skills } from "./Skills";

interface AppProps {
  name: string;
  job: string;
  company: string;
}

const BasicInfo: React.FC<AppProps> = ({ name, job, company }) => {
  return (
    <div className="App">
      <h1>{name}</h1>
      <h2>{job}</h2>
      <h4>{company}</h4>
    </div>
  );
};

// some components in App
const App = () => {
  return (
    <main>
      <BasicInfo
        name="Tomasz Kowalski"
        company="TomaszPOL"
        job="Frontend Developer"
      />
      <Image />
      <Infos />
      <Skills />
    </main>
  );
};

export default App;
